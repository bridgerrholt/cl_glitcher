add_library(file_util STATIC load_file_to_string.cpp ${ROOT_INCLUDE_DIR}/file_util/append_number.h)
target_include_directories(file_util PUBLIC
        ${ROOT_INCLUDE_DIR}
        ${RAPIDJSON_INCLUDE_DIR})