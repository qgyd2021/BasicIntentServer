# certutil -hashfile utf8proc-2.8.0.zip SHA256
FetchContent_Declare(utf8proc
    URL      https://github.com/JuliaStrings/utf8proc/archive/refs/tags/v2.8.0.zip
    URL_HASH SHA256=b2aec990876d1a995baf96150bb351e9724a29a936aa7b24078c531228236d3a
    )
FetchContent_MakeAvailable(utf8proc)
include_directories(${utf8proc_SOURCE_DIR})
