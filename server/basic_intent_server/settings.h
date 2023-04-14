//
// Created by tianx on 2022/10/8.
//
#ifndef SERVER_BASIC_INTENT_SERVER_SETTINGS_H
#define SERVER_BASIC_INTENT_SERVER_SETTINGS_H

#include <gflags/gflags.h>


DECLARE_string(project_name, "BasicIntentServer", "a string to indicate the name of the server");
DECLARE_string(http_host, "0.0.0.0", "server host");
DECLARE_uint32(http_port, 80, "server port");

DECLARE_string(model_path, "model/intent_cn_20221208", "model_path");
DECLARE_string(vocab_file, "pretrained/chinese-bert-wwm-ext/vocab.txt", "vocab_file");

DECLARE_string(models_json, "server/basic_intent_server/config/models.json", "models_json");


#endif //SERVER_BASIC_INTENT_SERVER_SETTINGS_H
