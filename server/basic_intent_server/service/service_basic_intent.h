//
// Created by tianx on 2022/12/8.
//

#ifndef SERVICE_BASIC_INTENT_H
#define SERVICE_BASIC_INTENT_H

#include <map>
#include <tuple>

#include <glog/logging.h>
#include <nlohmann/json.hpp>
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
      );

  ModelGroup(std::string model_file, std::string labels_file, std::string vocab_file);

  ~ModelGroup();
};


class BasicIntentService {
public:
  //模型
  std::map<std::string, ModelGroup *> key_to_model_group_map_;

  //构造函数
  BasicIntentService();

  //析构函数
  ~BasicIntentService();

  //
  std::pair<std::string, float> predict(const std::string & key, const std::string & text);

};


BasicIntentService * getBasicIntentService();


#endif //SERVICE_BASIC_INTENT_H
