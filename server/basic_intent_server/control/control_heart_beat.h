//
// Created by tianx on 2022/10/8.
//
#ifndef CONTROL_BASIC_INTENT_H
#define CONTROL_BASIC_INTENT_H

#include <httplib.h>


//curl -X POST http://127.0.0.1:4070/HeartBeat -d '{"valStr": "tianxing", "valInt": 20221008}'
std::function<void(const httplib::Request &, httplib::Response &)> HeartBeat();

#endif //CONTROL_BASIC_INTENT_H