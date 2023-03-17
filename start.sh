#!/usr/bin/env bash

rm -rf nohup.out
rm -rf logs/
mkdir -p logs/

nohup \
./cmake-build-debug/BasicIntentServer \
--http_port 13074 \
--stderrthreshold=0 \
--log_dir=./logs/ \
> nohup.out &
