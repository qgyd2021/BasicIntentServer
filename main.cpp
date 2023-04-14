#include <iostream>

#include <gflags/gflags.h>
#include <glog/logging.h>

#include "server/basic_intent_server/basic_intent_server.h"


int main(int argc, char *argv[])
{
  //初始化日志和启动参数组件
  gflags::ParseCommandLineFlags(&argc, &argv, true);
  google::InitGoogleLogging(argv[0]);

  BasicIntentServer(argc, argv);
  return 0;
}
