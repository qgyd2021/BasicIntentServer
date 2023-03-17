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
gdb -c core.740 ./cmake-build-debug/BasicIntentServer
where

备注: 
通过 CMakeLists.txt 控制 Debug 或 Release 模式, 
Debug 模式, 使用 gdb 可以看到异常的详细信息. 
set(CMAKE_BUILD_TYPE Debug)
#set(CMAKE_BUILD_TYPE Release)



```




### 环境配置


#### HttpLib HTTP/HTTPS 安装

```text
HttpLib HTTP/HTTPS 库

不需要编译
只需要在代码中包含 httplib.h 文件

参考链接: 
https://github.com/yhirose/cpp-httplib
https://blog.csdn.net/houxian1103/article/details/122350944

```


```text
下载代码: 
https://github.com/yhirose/cpp-httplib/archive/refs/tags/v0.11.3.zip

```


```text
CMakeLists 配置

# 支持多进程
set(CMAKE_CXX_FLAGS -pthread)
# message 打印
message(STATUS "CMAKE_CXX_FLAGS = ${CMAKE_CXX_FLAGS}")


```


#### JSON 安装

```text
JSON库

不需要编译

参考链接: 
https://github.com/nlohmann/json


```


```text
下载代码: 
https://github.com/nlohmann/json/archive/refs/tags/v3.11.2.zip

```


```text
CMakeLists 配置

不需要配置

```


#### gflags 安装

```text
命令行工具

参考链接: 
https://github.com/gflags/gflags


```


```text
下载链接: 
https://github.com/gflags/gflags/archive/refs/tags/v2.2.2.zip

```


```text
安装: 

INSTALL 文件中提供了构建和安装说明

cd gflags
mkdir build && cd build

ccmake ..
- Press 'c' to configure the build system and 'e' to ignore warnings.
- Set CMAKE_INSTALL_PREFIX and other CMake variables and options.
- Continue pressing 'c' until the option 'g' is available.
- Then press 'g' to generate the configuration files for GNU Make.

make
make test
make install


```


```text
CMakeLists 配置


# 查看静态库是否存在
>>> ls /usr/local/lib/libgflags* -l
-rw-r--r-- 1 root root 260122 Oct  8 16:30 /usr/local/lib/libgflags.a
-rw-r--r-- 1 root root 255818 Oct  8 16:30 /usr/local/lib/libgflags_nothreads.a


# 查看动态库是否存在
root@680cb19b9e6b:/data/tianxing/CLionProjects/VoiceMailMonitor# ls /usr/local/lib/libgflags* -l
-rw-r--r--. 1 root root 282278 Oct 19 07:03 /usr/local/lib/libgflags.a
lrwxrwxrwx. 1 root root     16 Oct 19 07:24 /usr/local/lib/libgflags.so -> libgflags.so.2.2
lrwxrwxrwx. 1 root root     18 Oct 19 07:24 /usr/local/lib/libgflags.so.2.2 -> libgflags.so.2.2.2
-rw-r--r--. 1 root root 200832 Oct 19 07:23 /usr/local/lib/libgflags.so.2.2.2
-rw-r--r--. 1 root root 278294 Oct 19 07:02 /usr/local/lib/libgflags_nothreads.a
lrwxrwxrwx. 1 root root     26 Oct 19 07:24 /usr/local/lib/libgflags_nothreads.so -> libgflags_nothreads.so.2.2
lrwxrwxrwx. 1 root root     28 Oct 19 07:24 /usr/local/lib/libgflags_nothreads.so.2.2 -> libgflags_nothreads.so.2.2.2
-rw-r--r--. 1 root root 203456 Oct 19 07:23 /usr/local/lib/libgflags_nothreads.so.2.2.2


# 查看 gflags 配置(可以找到版本信息)
cat /usr/local/lib/cmake/gflags/gflags-config.cmake


# CMakeLists 配置
find_package(gflags REQUIRED)

add_executable(HttpLib main.cpp)
target_link_libraries(HttpLib gflags::gflags)


```


```text
# 代码配置
#include <gflags/gflags.h>

DEFINE_string(project_name, "LibTorchServer", "a string to indicate the name of the server");
DEFINE_uint32(http_port, 8080, "server port");

//解析命令行参数
gflags::ParseCommandLineFlags(&argc, &argv, true);

//通过 FLAGS_* 直接输出 (不执行 ParseCommandLineFlags, 也可以访问参数).
std::cout << FLAGS_project_name << std::endl;


# 使用实例
>>> ./cmake-build-debug/HttpLib --project_name test --http_port 9080 
E20221008 18:33:30.314883 1316279 libtorch_server.cpp:19] server test start at 127.0.0.1:9080


# 异常处理
>>> cmake --build /data/tianxing/HttpLib/cmake-build-debug --target HttpLib -- -j 4
编译时报错: 
Target "HttpLib" links to target "gflags::gflags" but the target was not
  found.  Perhaps a find_package() call is missing for an IMPORTED target, or
  an ALIAS target is missing?

>>> cmake --build /data/tianxing/HttpLib/cmake-build-debug --target HttpLib -- -j 4
编译时报错: 
/usr/bin/ld: cannot find -lgflags::gflags

原因: 
未知

解决方案: 
target_link_libraries(HttpLib gflags::gflags)
改为
target_link_libraries(HttpLib gflags)


```


#### glog 安装

```text
日志库

glog 依赖于 gflags, 先装 gflags. 


参考链接: 
https://github.com/google/glog

```


```text
下载代码: 
https://github.com/google/glog/archive/refs/tags/v0.5.0.zip

```


```text
安装
https://github.com/google/glog#building-glog-with-cmake


cd glog

cmake -S . -B build -G "Unix Makefiles"
cmake --build build
cmake --build build --target test
cmake --build build --target install

```


```text
CMakeLists 配置

cmake_minimum_required(VERSION 3.16)
project(HttpLib VERSION 1.0)

find_package(glog 0.6.0 REQUIRED)

add_executable(HttpLib main.cpp)
target_link_libraries(HttpLib glog::glog)

```


```text
# 代码配置
#include <glog/logging.h>

int main(int argc, char* argv[]) {
    // Initialize Google’s logging library.
    google::InitGoogleLogging(argv[0]);

    // ...
    LOG(INFO) << "Found " << num_cookies << " cookies";
}


# 编译时异常
/usr/bin/ld: /usr/local/lib/libgflags.a(gflags.cc.o): relocation R_X86_64_PC32 against symbol `stderr@@GLIBC_2.2.5' can not be used when making a shared object; recompile with -fPIC
/usr/bin/ld: /usr/local/lib/libgflags.a(gflags_reporting.cc.o): relocation R_X86_64_32 against `.rodata.str1.1' can not be used when making a shared object; recompile with -fPIC
/usr/bin/ld: /usr/local/lib/libgflags.a(gflags_completions.cc.o): relocation R_X86_64_32 against `.rodata.str1.1' can not be used when making a shared object; recompile with -fPIC
/usr/bin/ld: final link failed: nonrepresentable section on output
collect2: error: ld returned 1 exit status
make[2]: *** [CMakeFiles/glog.dir/build.make:96: libglog.so.0.7.0] Error 1
make[1]: *** [CMakeFiles/Makefile2:917: CMakeFiles/glog.dir/all] Error 2
make: *** [Makefile:166: all] Error 2

# 原因
编译动态库时不能使用静态库

# 参考链接
https://blog.csdn.net/qq_37746927/article/details/122619385
https://blog.csdn.net/qq_41035283/article/details/119614206

# 解决方案
gflags 要安装动态库.so, 所以前面安装时设置了 DBUILD_SHARED_LIBS=ON
(重新编译时, 建议连同代码一起删除, 重新 git clone, 以免有缓存或配置的影响). 



```


#### LibTorch 安装

```text
不需要编译

参考链接: 
https://pytorch.org/get-started/locally/
https://pytorch.org/cppdocs/api/library_root.html

安装 PYTORCH 的 C++ 发行版
https://pytorch.org/cppdocs/installing.html

```


```text
Windows 版本

Download here (Release version):
https://download.pytorch.org/libtorch/cpu/libtorch-win-shared-with-deps-1.10.2%2Bcpu.zip
Download here (Debug version):
https://download.pytorch.org/libtorch/cpu/libtorch-win-shared-with-deps-debug-1.10.2%2Bcpu.zip

```


```text
Linux 版本

Download here (Pre-cxx11 ABI):
https://download.pytorch.org/libtorch/cpu/libtorch-shared-with-deps-1.10.2%2Bcpu.zip
Download here (cxx11 ABI):
https://download.pytorch.org/libtorch/cpu/libtorch-cxx11-abi-shared-with-deps-1.10.2%2Bcpu.zip

```


```text
CMakeLists 配置

set(CMAKE_PREFIX_PATH /data/tianxing/HttpLib/thirdparty/libtorch/share/cmake/Torch/)
message(STATUS "CMAKE_PREFIX_PATH = ${CMAKE_PREFIX_PATH}")

find_package(Torch REQUIRED)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${TORCH_CXX_FLAGS}")

add_executable(HttpLib main.cpp)
target_link_libraries(HttpLib "${TORCH_LIBRARIES}")

```


#### 异常


```text
异常1


执行二进制文件时异常
./cmake-build-debug/VoiceMailMonitor
./cmake-build-debug/VoiceMailMonitor: error while loading shared libraries: libglog.so.1: cannot open shared object file: No such file or directory

参考链接: 
https://blog.csdn.net/zong596568821xp/article/details/90297360

原因: 
共享库没有安装到 /lib 或 /usr/lib 目录下. 

解决方案: 
将共享库所在目录添加到 /etc/ld.so.conf 中, 之后执行 ldconfig. 如下: 

>>> whereis libglog.so.1
libglog.so: /usr/local/lib/libglog.so.1 /usr/local/lib/libglog.so

>>> cat /etc/ld.so.conf
include /etc/ld.so.conf.d/*.conf

>>> echo "/usr/local/lib" >> /etc/ld.so.conf
>>> ldconfig


```


```text
异常2


./cmake-build-debug/LibTorchServer: error while loading shared libraries: libglog.so.0: cannot open shared object file: No such file or directory

解决方案: 
(1) 查看文件是否存在 (如不存在, 更换一个 glog 版本安装). 
find /usr/lib/libglog*
find /usr/local/lib/libglog*

(2) 如文件存在
将共享库所在目录添加到 /etc/ld.so.conf 中, 之后执行 ldconfig. 如下: 
echo "/usr/local/lib" >> /etc/ld.so.conf
ldconfig


```



### 异常


Segmentation fault (core dumped)
```text
https://blog.csdn.net/doubleselect/article/details/38727105

安装 gdb
apt-get install -y gdb

查看 core 文件
gdb -c core.10806 ./cmake-build-debug/LibTorchServer

where

备注: 
通过 CMakeLists.txt 控制 Debug 或 Release 模式, 
Debug 模式, 使用 gdb 可以看到异常的详细信息. 
set(CMAKE_BUILD_TYPE Debug)
#set(CMAKE_BUILD_TYPE Release)



```



