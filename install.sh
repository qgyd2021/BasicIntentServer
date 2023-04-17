#!/usr/bin/env bash

# docker run --name BasicIntentServer -itd -p 13070:13070 daocloud.io/centos:7 /bin/bash

yum install -y bzip2 gdb git lrzsz wget vim

mkdir -p /data/tianxing/CLionProjects/BasicIntentServer
cd /data/tianxing/CLionProjects/BasicIntentServer || exit 1;

sh ./script/install_cmake.sh
sh ./script/install_gcc.sh
