## 意图识别


### 服务布署

```text

# 创建容器
docker run --name BasicIntentServer -itd -p 13070:13070 daocloud.io/centos:7 /bin/bash

# 安装环境
# ./install.sh
yum install -y bzip2 gdb git lrzsz wget vim

mkdir -p /data/tianxing/CLionProjects/
cd /data/tianxing/CLionProjects/ || exit 1;


# 拉代码
git clone https://gitee.com/qgyd2021/BasicIntentServer.git


# 更新代码
git reset --hard origin/master
git pull origin master


# cmake, gcc 安装
cd BasicIntentServer
nohup sh install.sh &


# cmake 编译
mkdir cmake-build-debug/
cmake -B cmake-build-debug/

cmake --build ./cmake-build-debug --target BasicIntentServer -j "$(grep -c ^processor /proc/cpuinfo)"

./cmake-build-debug/BasicIntentServer


# bug 调试

gdb -c ./cmake-build-debug/BasicIntentServer


安装 gdb
yum install -y gdb

查看 core 文件
gdb -c core.32193 ./cmake-build-debug/BasicIntentServer

where

备注: 
通过 CMakeLists.txt 控制 Debug 或 Release 模式, 
Debug 模式, 使用 gdb 可以看到异常的详细信息. 
set(CMAKE_BUILD_TYPE Debug)
#set(CMAKE_BUILD_TYPE Release)



```
