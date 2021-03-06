function(cmd_stringify_to_header var_namespace var_name input_file output_file)
    add_custom_command(
            OUTPUT ${output_file}
            COMMAND $<TARGET_FILE:stringify_to_header_bin> ${var_namespace} ${var_name} ${input_file} ${output_file}
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
            DEPENDS stringify_to_header_bin ${CMAKE_CURRENT_SOURCE_DIR}/${input_file}
    )
endfunction(cmd_stringify_to_header)
