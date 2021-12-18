add_library(generate_version_info STATIC generate_version_info.cpp)
target_include_directories(generate_version_info PUBLIC
        ${ROOT_INCLUDE_DIR}
        ${ROOT_INCLUDE_DIR}/generate_version_info)

add_executable(generate_version_info_bin main.cpp)
target_link_libraries(generate_version_info_bin generate_version_info)
set_target_properties(generate_version_info_bin
        PROPERTIES OUTPUT_NAME generate_version_info) # Rename output binary to generate_version_info