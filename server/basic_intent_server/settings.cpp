//
// Created by tianx on 2023/4/14.
//
#include <gflags/gflags.h>

DEFINE_string(project_name, "BasicIntentServer", "a string to indicate the name of the server");
DEFINE_string(http_host, "0.0.0.0", "server host");
DEFINE_uint32(http_port, 80, "server port");

DEFINE_string(models_json, "server/basic_intent_server/json_config/models.json", "models_json");

DEFINE_string(basic_intent_log_dir, "./logs", "basic intent log dir");
DEFINE_uint32(basic_intent_stderrthreshold, 0, "basic intent stderr threshold");
