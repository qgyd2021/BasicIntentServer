//
// Created by tianx on 2022/12/8.
//

#ifndef SERVER_BASIC_INTENT_SERVER_SERVICE_BASIC_INTENT_H
#define SERVER_BASIC_INTENT_SERVER_SERVICE_BASIC_INTENT_H

#include <map>
#include <tuple>

#include <glog/logging.h>
#include <nlohmann/json.hpp>
#include <torch/script.h>
#include <torch/torch.h>

#include "toolbox/nlp/data/tokenizer/bert_tokenizer/tokenization.h"

#include "../settings.h"

#include "service_basic_intent.h"


class ModelGroup {
public:
  torch::jit::script::Module model_;
  nlohmann::json labels_;
  nlp::FullTokenizer * tokenizer_;

  ModelGroup(
      torch::jit::script::Module model,
      nlohmann::json labels,
      nlp::FullTokenizer * tokenizer
  ): model_(model), labels_(labels), tokenizer_(tokenizer) {}

  ModelGroup(std::string model_file, std::string labels_file, std::string vocab_file) {
    //model
    try{
      model_ = torch::jit::load(model_file);
      model_.eval();
    }
    catch (const c10::Error &e){
      std::cout << "error loading the model:\n " << e.what();
    };

    //labels
    std::ifstream i_labels(labels_file);
    i_labels >> labels_;

    //tokenizer
    tokenizer_ = new nlp::FullTokenizer(vocab_file.c_str(), true);

  };

  ~ModelGroup() {
    delete tokenizer_;
    tokenizer_ = nullptr;
  }
};


BasicIntentService::BasicIntentService()
{
  nlohmann::json models_json;
  std::ifstream i_models_json(FLAGS_models_json);
  i_models_json >> models_json;
  for (const auto & model_json:models_json) {
    std::string key = model_json["key"];
    std::string model_path = model_json["model_path"];
    std::string vocab_file = model_json["vocab_file"];

    std::string model_file = model_path + "/model.pth";
    std::string labels_file = model_path + "/labels.json";

    this->key_to_model_group_map_[key] = new ModelGroup(model_file, labels_file, vocab_file);
  }
};


BasicIntentService::~BasicIntentService() {
  for (auto it = key_to_model_group_map_.begin(); it != key_to_model_group_map_.end(); ++it) {
    delete it->second;
    it->second = nullptr;
  }
}


std::pair<std::string, float> BasicIntentService::predict(const std::string & key, const std::string &text)
{
  std::pair<std::string, float> result;

  auto key_to_model_group_item = this->key_to_model_group_map_.find(key);
  if (key_to_model_group_item == this->key_to_model_group_map_.end()) {
    result.first = "key not found.";
    result.second = 0.0;
    return std::move(result);
  } else {
    std::vector<std::string> tokens;
    key_to_model_group_item->second->tokenizer_->tokenize(text.c_str(), &tokens, 128);

    uint64_t ids[tokens.size()];
    //auto ids = new uint64_t[tokens.size()];
    key_to_model_group_item->second->tokenizer_->convert_tokens_to_ids(tokens, ids);

    std::vector<uint64_t> input_ids;
    input_ids.push_back(102);

    for (std::size_t i = 0; i < tokens.size(); ++i) {
      input_ids.push_back(ids[i]);
    };
    //delete ids;
    while (input_ids.size() < 4) {
      input_ids.push_back(0);
    };
    input_ids.push_back(103);

    auto size = (long int) input_ids.size();
    torch::Tensor inputs1 = torch::from_blob(input_ids.data(), {size}, torch::kLong);
    torch::Tensor inputs2 = torch::unsqueeze(inputs1, 0);

    torch::IValue outputsIValue = key_to_model_group_item->second->model_({inputs2});
    c10::Dict<c10::IValue, c10::IValue> outputs = outputsIValue.toGenericDict();
    torch::Tensor probs = outputs.at(c10::IValue("probs")).toTensor();
    torch::Tensor indexes = torch::argmax(probs, -1);
    std::vector<long> indexesVector(indexes.data_ptr<long>(), indexes.data_ptr<long>() + indexes.numel());
    long index = indexesVector[0];

    torch::Tensor probsFirst = probs.index({torch::indexing::Slice(0),});
    std::vector<float> probsVector(probsFirst.data_ptr<float>(), probsFirst.data_ptr<float>() + probsFirst.numel());
    float predProb = probsVector[index];

    //保存标签
    std::string predLabel = key_to_model_group_item->second->labels_[index];

    result.first = predLabel;
    result.second = predProb;
    return std::move(result);
  }
};


#endif //SERVER_BASIC_INTENT_SERVER_SERVICE_BASIC_INTENT_H
