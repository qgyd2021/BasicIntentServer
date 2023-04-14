//
// Created by tianx on 2023/4/14.
//
#include <iostream>

#include <gflags/gflags.h>

DEFINE_string(project_name, "BasicIntentServer", "a string to indicate the name of the server");
DEFINE_string(http_host, "0.0.0.0", "server host");
DEFINE_uint32(http_port, 80, "server port");

DEFINE_string(models_json, "server/basic_intent_server/config/models.json", "models_json");


std::cout << "FLAGS_models_json" << std::endl;
std::cout << FLAGS_models_json << std::endl;
