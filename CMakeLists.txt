cmake_minimum_required(VERSION 3.13)
project(BasicIntentServer)

# Fix the warnings about `DOWNLOAD_EXTRACT_TIMESTAMP` in newer CMake versions.
if (CMAKE_VERSION VERSION_GREATER_EQUAL "3.24.0")
    cmake_policy(SET CMP0135 NEW)
endif()

# 支持多进程
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_BUILD_TYPE Debug)
#set(CMAKE_BUILD_TYPE Release)

include(FetchContent)
set(FETCHCONTENT_QUIET OFF)
get_filename_component(thirdparty "${CMAKE_SOURCE_DIR}/thirdparty" REALPATH BASE_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
set(FETCHCONTENT_BASE_DIR ${thirdparty})
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

if(NOT MSVC)
    # Keep the same with openfst, -fPIC or -fpic
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -pthread -fPIC")
    # link_libraries(ws2_32)
else()
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
    add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
    link_libraries(ws2_32)
endif()

include(gflags)
include(glog)
include(libtorch)

# 以下库, 只需要 include, 不需要 link.
include(nlohmann_json)
include(httplib)

#include(utf8proc)

# 自定义库
add_subdirectory(toolbox/nlp)

# include 目录
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# 编辑
file(GLOB_RECURSE SERVER_SRC "${CMAKE_CURRENT_SOURCE_DIR}/server/**/*.cpp")
add_executable(BasicIntentServer main.cpp ${SERVER_SRC})

target_link_libraries(BasicIntentServer gflags)
target_link_libraries(BasicIntentServer glog::glog)
target_link_libraries(BasicIntentServer "${TORCH_LIBRARIES}")
target_link_libraries(BasicIntentServer nlp)
