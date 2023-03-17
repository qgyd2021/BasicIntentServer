FetchContent_Declare(httplib
    URL      https://github.com/yhirose/cpp-httplib/archive/refs/tags/v0.11.2.zip
    URL_HASH SHA256=afa64d0fbf3912943ed127b4f654d9c977eff7ecf13240341aca879b2e3f981d
    )
FetchContent_MakeAvailable(httplib)
include_directories(${httplib_SOURCE_DIR})
