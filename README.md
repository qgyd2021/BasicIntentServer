## 意图识别


```text

# 拉取代码
git reset --hard origin/master
git pull origin master


git bash
mkdir build && cd build && cmake .. && cmake --build .



mkdir cmake-build-debug/
cmake -B cmake-build-debug/


cmake --build ./cmake-build-debug --target BasicIntentServer -j 4
cmake --build ./cmake-build-debug --target BasicIntentServer -j "$(grep -c ^processor /proc/cpuinfo)"

./cmake-build-debug/BasicIntentServer




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
