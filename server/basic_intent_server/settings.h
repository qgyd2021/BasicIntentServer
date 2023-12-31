//
// Created by tianx on 2022/10/8.
//
#ifndef SERVER_BASIC_INTENT_SERVER_SETTINGS_H
#define SERVER_BASIC_INTENT_SERVER_SETTINGS_H

#include <gflags/gflags.h>


DECLARE_string(project_name);
DECLARE_string(http_host);
DECLARE_uint32(http_port);

DECLARE_string(models_json);

DECLARE_string(basic_intent_log_dir);
DECLARE_uint32(basic_intent_stderrthreshold);


#endif //SERVER_BASIC_INTENT_SERVER_SETTINGS_H
