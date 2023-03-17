cmake_minimum_required(VERSION 3.1)

project(nlp)

set(CMAKE_CXX_STANDARD 11)

# 支持 utf8proc
#set(utf8proc_LIBRARY /usr/local/lib/libutf8proc.a)
#set(utf8proc_INCLUDE_DIR /data/tianxing/CLionProjects/LibTorchServer/thirdparty/utf8proc)
#include_directories(${utf8proc_INCLUDE_DIR})

include(FetchContent)
set(FETCHCONTENT_QUIET OFF)
get_filename_component(fc_base "fc_base" REALPATH BASE_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
set(FETCHCONTENT_BASE_DIR ${fc_base})
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

include(utf8proc)

FILE(GLOB_RECURSE DIR_SRCS ./*.cpp)
add_library(nlp STATIC ${DIR_SRCS})
target_link_libraries(nlp utf8proc)
