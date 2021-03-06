add_library(file_util STATIC load_file_to_string.cpp)
target_include_directories(file_util PUBLIC
        ${ROOT_INCLUDE_DIR}
        ${RAPIDJSON_INCLUDE_DIR})