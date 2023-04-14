//
// Created by tianx on 2022/10/8.
//
// 第三方头文件
// 设置宏控制 torch 使用 glog 来打日志
//#define C10_USE_GLOG
//#define CPPHTTPLIB_THREAD_POOL_COUNT 24

#include <string>

#include <gflags/gflags.h>
#include <glog/logging.h>
#include <torch/script.h>
#include <httplib.h>

#include "control/control_basic_intent.h"
#include "control/control_heart_beat.h"

#include "settings.h"

#include "basic_intent_server.h"


int BasicIntentServer(int argc, char *argv[])
{
  //初始化日志和启动参数组件
  gflags::ParseCommandLineFlags(&argc, &argv, true);
  google::InitGoogleLogging(argv[0]);

  // HTTP
  httplib::Server svr;

  svr.Post("/HeartBeat", HeartBeat());
  svr.Post("/BasicIntent", BasicIntent());

  LOG(INFO) << "server " << FLAGS_project_name << " start at " << FLAGS_http_host << ":" << FLAGS_http_port;
  svr.listen(FLAGS_http_host, FLAGS_http_port);
  return 0;

}
