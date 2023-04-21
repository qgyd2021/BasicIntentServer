//
// Created by tianx on 2022/12/8.
//
#include <chrono>

#include <httplib.h>
#include <nlohmann/json.hpp>

#include "../service/service_basic_intent.h"
#include "control_basic_intent.h"

using json = nlohmann::json;


//请求体
class BasicIntentRequest
{
public:
  std::string key;
  std::string text;

public:
  NLOHMANN_DEFINE_TYPE_INTRUSIVE(BasicIntentRequest, key, text)
};


//响应体
class BasicIntentResponse
{
public:
  int statusCode = 0;
  std::string message;
  std::string label;
  float prob;
  float timeCost = 0;

public:
  NLOHMANN_DEFINE_TYPE_INTRUSIVE(BasicIntentResponse, statusCode, message, label, prob, timeCost)
};


//curl -X POST http://127.0.0.1:13070/BasicIntent -d '{"key": "chinese", "text": "C++的BERT分词器实现"}'
//curl -X POST http://127.0.0.1:13070/BasicIntent -d '{"key": "english", "text": "who are you"}'

//curl -X POST http://127.0.0.1:80/BasicIntent -d '{"key": "chinese", "text": "C++的BERT分词器实现"}'
//curl -X POST http://127.0.0.1:80/BasicIntent -d '{"key": "zh-CN2", "text": "C++的BERT分词器实现"}'
std::function<void(const httplib::Request &, httplib::Response &)> BasicIntent(){
  return [](const httplib::Request &request, httplib::Response &response) {
    auto startMsClock = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
    long long int startTime = startMsClock.count();

    BasicIntentRequest requestObject;
    BasicIntentResponse responseObject;

    //请求体创建
    try
    {
      json requestJson = json::parse(request.body); //将字符串转为json对象
      requestObject = requestJson.get<BasicIntentRequest>(); //将json对象转为定义好的请求体
    }
    catch (json::exception &e)
    {
      LOG(ERROR) << "request body json::parse failed: " << e.what();
      responseObject.statusCode = 1;
      responseObject.message = e.what();
      json respJson = responseObject;
      response.set_content(respJson.dump(), "application/json");
      return;
    };

    //逻辑
    BasicIntentService * basicIntentService = getBasicIntentService();
    std::pair<std::string, float> item = basicIntentService->predict(requestObject.key, requestObject.text);
    std::string label = item.first;
    float prob = item.second;

    auto finishMsClock = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
    long long int finishTime = finishMsClock.count();

    //响应
    responseObject.statusCode = 0;
    responseObject.message = "success";
    responseObject.label = label;
    responseObject.prob = prob;
    responseObject.timeCost = (float) (finishTime - startTime) / 1000;

    json responseJson = responseObject;
    std::string responseText = responseJson.dump();

    LOG(INFO) << "request body: " << request.body << ", response body: " << responseText;
    response.set_content(responseText, "application/json");
  };
};
