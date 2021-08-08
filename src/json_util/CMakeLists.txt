add_library(json_util STATIC load_json_file.cpp file_read_stream.cpp)
target_include_directories(json_util PUBLIC
        ${JSON_UTIL_INCLUDE_DIR}
        ${RAPIDJSON_INCLUDE_DIR})