add_subdirectory(cli)
add_subdirectory(cmd_execution)
add_subdirectory(gpu_util)
add_subdirectory(gpu_programs)
add_subdirectory(image_util)
add_subdirectory(mod_environment)
add_subdirectory(mod_sys)
add_subdirectory(static_mods)

#get_target_property(test_cl_glitcher_cli_sources test_cl_glitcher_cli SOURCES)
#get_target_property(test_cl_glitcher_cli_libs test_cl_glitcher_cli LINK_LIBRARIES)

#add_executable(test_cl_glitcher ${test_cl_glitcher_cli_sources} ${test_cl_glitcher_mod_sys_sources})
#target_link_libraries(test_cl_glitcher PUBLIC ${test_cl_glitcher_cli_libs} ${test_cl_glitcher_mod_sys_libs})
