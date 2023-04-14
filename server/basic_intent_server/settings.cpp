//
// Created by tianx on 2023/4/14.
//
#include <gflags/gflags.h>

DEFINE_string(project_name, "BasicIntentServer", "a string to indicate the name of the server");
DEFINE_string(http_host, "0.0.0.0", "server host");
DEFINE_uint32(http_port, 80, "server port");


DEFINE_string(model_path, "model/intent_cn_20221208", "model_path");
DEFINE_string(vocab_file, "pretrained/chinese-bert-wwm-ext/vocab.txt", "vocab_file");

DEFINE_string(models_json, "server/basic_intent_server/config/models.json", "models_json");

