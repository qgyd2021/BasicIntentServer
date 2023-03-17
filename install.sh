#!/usr/bin/env bash

yum install -y bzip2 gdb git lrzsz wget vim

mkdir -p /data/tianxing/CLionProjects/BasicIntentServer/
cd /data/tianxing/CLionProjects/BasicIntentServer/ || exit 1;

sh ./script/install_cmake.sh
sh ./script/install_gcc.sh
