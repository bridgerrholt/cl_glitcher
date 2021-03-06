function(cmd_stringify_to_header var_namespace var_name input_file output_file)
    add_custom_command(
            OUTPUT ${output_file}
            COMMAND $<TARGET_FILE:stringify_to_header_bin> ${var_namespace} ${var_name} ${input_file} ${output_file}
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
            DEPENDS stringify_to_header_bin ${CMAKE_CURRENT_SOURCE_DIR}/${input_file}
    )
endfunction(cmd_stringify_to_header)

macro(cmd_stringify_to_header_no_prefix var_namespace var_name input_file output_file)
    message(${input_file})
    message(${output_file})
    add_custom_command(
            OUTPUT ${output_file}
            COMMAND $<TARGET_FILE:stringify_to_header_bin> ${var_namespace} ${var_name} ${input_file} ${output_file}
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
            DEPENDS stringify_to_header_bin ${input_file}
    )
endmacro(cmd_stringify_to_header_no_prefix)

macro(str_stringify_to_header var var_namespace var_name input_file output_file)
    set(${var} COMMAND $<TARGET_FILE:stringify_to_header_bin> ${var_namespace} ${var_name} ${input_file} ${output_file})
endmacro(str_stringify_to_header)