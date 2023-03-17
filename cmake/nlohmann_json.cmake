# certutil -hashfile json-3.10.5.zip SHA256
FetchContent_Declare(nlohmann_json
  URL      https://github.com/nlohmann/json/archive/refs/tags/v3.10.5.zip
  URL_HASH SHA256=ea4b0084709fb934f92ca0a68669daa0fe6f2a2c6400bf353454993a834bb0bb
)
FetchContent_MakeAvailable(nlohmann_json)
include_directories(${nlohmann_json_SOURCE_DIR}/include)
