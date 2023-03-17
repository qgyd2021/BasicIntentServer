## C++ 实现 BERT 分词


```text
参考链接: 
https://github.com/zhihu/cuBERT


```

#### utf8proc 安装

```text
utf8proc 是一个小型, 干净的 C 库, 它为 UTF-8 编码的数据提供 Unicode 规范化, 大小写折叠和其他操作. 

参考链接: 
https://formulae.brew.sh/formula/utf8proc

https://github.com/JuliaStrings/utf8proc

```


```text

下载链接: 
https://github.com/JuliaStrings/utf8proc/archive/refs/tags/v2.8.0.zip

```


```text
安装: 

mkdir build
cmake -S . -B build
cmake --build build



/home/cmake-3.21.1-linux-x86_64/bin/cmake -S . -B build
/home/cmake-3.21.1-linux-x86_64/bin/cmake --build build
/home/cmake-3.21.1-linux-x86_64/bin/cmake --build build --target install



```


```text
CMakeLists.txt 配置

cmake_minimum_required(VERSION 3.13)
project(LibTorchServer)

set(utf8proc_LIBRARY /usr/local/lib/libutf8proc.a)
set(utf8proc_INCLUDE_DIR /data/tianxing/CLionProjects/LibTorchServer/thirdparty/utf8proc)
include_directories(${utf8proc_INCLUDE_DIR})

add_executable(LibTorchServer main.cpp)
target_link_libraries(LibTorchServer ${utf8proc_LIBRARY})


```
