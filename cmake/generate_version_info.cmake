function(cmd_generate_version_info var_namespace version_var_name git_commit_var_name output_file depends)
    if(ARGN GREATER 0)
        SET(CMD_GENERATE_VERSION_INFO_GIT_VERSION ARGV6)
    else()
        SET(CMD_GENERATE_VERSION_INFO_GIT_VERSION)
    endif()

    add_custom_command(
        OUTPUT ${output_file}
        COMMAND $<TARGET_FILE:generate_version_info_bin>
        ${var_namespace} ${version_var_name} ${git_commit_var_name} ${output_file} ${CMAKE_PROJECT_VERSION} ${CMD_GENERATE_VERSION_INFO_GIT_VERSION}
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        DEPENDS generate_version_info_bin ${depends}
    )
endfunction()