//
// Created by tianx on 2022/10/8.
//
#include <chrono>
#include <glog/logging.h>
#include <iostream>
#include <sstream>

#include <httplib.h>
#include <nlohmann/json.hpp>

#include "control_heart_beat.h"


using json = nlohmann::json;

//请求体
class HeartBeatRequest
{
public:
  std::string valStr;
  int valInt = 0;

public:
  NLOHMANN_DEFINE_TYPE_INTRUSIVE(HeartBeatRequest, valStr, valInt)
};

//响应体
class HeartBeatResponse
{
public:
  int retCode = 0;
  std::string retMsg;
  std::string valStr;
  int valInt = 0;

public:
  NLOHMANN_DEFINE_TYPE_INTRUSIVE(HeartBeatResponse, retCode, retMsg, valStr, valInt)
};


//curl -X POST http://127.0.0.1:4070/HeartBeat -d '{"valStr": "tianxing", "valInt": 20221008}'
std::function<void(const httplib::Request &, httplib::Response &)> HeartBeat(){
  //[](){} 是标准的 lambda 表达式用法
  return [](const httplib::Request &request, httplib::Response &response) {
    HeartBeatRequest requestObject;
    HeartBeatResponse responseObject;

    //请求体创建
    try
    {
      json requestJson = json::parse(request.body); //将字符串转为json对象
      requestObject = requestJson.get<HeartBeatRequest>(); //将json对象转为定义好的请求体
    }
    catch (json::exception &e)
    {
      LOG(ERROR) << "request body json::parse failed: " << e.what();
      responseObject.retCode = 1;
      responseObject.retMsg = e.what();
      json respJson = responseObject;
      response.set_content(respJson.dump(), "application/json");
      return;
    };

    //逻辑
    //std::cout << requestObject.valStr << std::endl;
    //std::cout << requestObject.valInt << std::endl;

    //响应
    responseObject.retCode = 0;
    responseObject.retMsg = "success";
    responseObject.valStr = requestObject.valStr;
    responseObject.valInt = requestObject.valInt;

    json responseJson = responseObject;
    std::string responseText = responseJson.dump();

    LOG(INFO) << "request body: " << request.body << ", response body: " << responseText;
    response.set_content(responseText, "application/json");
  };
}
