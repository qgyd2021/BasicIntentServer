//
// Created by tianx on 2022/12/8.
//

#ifndef SERVICE_BASIC_INTENT_H
#define SERVICE_BASIC_INTENT_H

#include <map>
#include <tuple>

#include <glog/logging.h>
#include <torch/script.h>
#include <torch/torch.h>

#include "toolbox/nlp/data/tokenizer/bert_tokenizer/tokenization.h"

#include "../settings.h"


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


class BasicIntent {
public:
  //模型
  std::map<std::string, ModelGroup *> key_to_model_group_map_;

  //构造函数
  BasicIntent();

  //析构函数
  ~BasicIntent();

  //
  std::pair<std::string, float> predict(const std::string & key, const std::string & text);

};


#endif //SERVICE_BASIC_INTENT_H
