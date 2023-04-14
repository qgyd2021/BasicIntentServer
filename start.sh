#!/usr/bin/env bash

rm -rf nohup.out
rm -rf logs/
mkdir -p logs/

nohup \
./cmake-build-debug/BasicIntentServer \
--http_port 13070 \
--basic_intent_stderrthreshold=0 \
--basic_intent_log_dir=./logs/ \
> nohup.out &
