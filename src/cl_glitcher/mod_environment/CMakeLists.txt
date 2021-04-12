add_library(cl_glitcher_mod_environment STATIC mod_environment.cpp load_mod_environment.cpp)
target_include_directories(cl_glitcher_mod_environment PUBLIC
        ${ROOT_INCLUDE_DIR}
        ${CL_GLITCHER_INCLUDE_DIR})
target_link_libraries(cl_glitcher_mod_environment PUBLIC json_util)

# add_library(cl_glitcher_mod_environment_interface INTERFACE)
# target_include_directories(cl_glitcher_mod_environment_interface INTERFACE
#         "$<TARGET_PROPERTY:json_util,INCLUDE_DIRECTORIES>")