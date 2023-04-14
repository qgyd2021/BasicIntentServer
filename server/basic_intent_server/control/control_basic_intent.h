//
// Created by tianx on 2022/12/8.
//

#ifndef CONTROL_BASIC_INTENT_H
#define CONTROL_BASIC_INTENT_H

#include "../service/service_basic_intent.h"

BasicIntentService basicIntentService;

//curl -X POST http://127.0.0.1:80/BasicIntent -d '{"key": "zh-CN", "text": "C++的BERT分词器实现"}'
//curl -X POST http://127.0.0.1:80/BasicIntent -d '{"key": "zh-CN2", "text": "C++的BERT分词器实现"}'
std::function<void(const httplib::Request &, httplib::Response &)> BasicIntent();


#endif //CONTROL_BASIC_INTENT_H
