add_library(stringify_to_header STATIC stringify_to_header.cpp)
target_include_directories(stringify_to_header PUBLIC
        ${ROOT_INCLUDE_DIR}
        ${ROOT_INCLUDE_DIR}/stringify_to_header)
target_link_libraries(stringify_to_header PUBLIC file_util)

add_executable(stringify_to_header_bin main.cpp)
target_link_libraries(stringify_to_header_bin stringify_to_header)
set_target_properties(stringify_to_header_bin
        PROPERTIES OUTPUT_NAME stringify_to_header) # Rename output binary to stringify_to_header