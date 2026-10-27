find_program(LTTNG_GEN_TP lttng-gen-tp REQUIRED)

function(add_lttng_tracepoints TARGET TP_FILE)
    get_filename_component(tp_file "${TP_FILE}" ABSOLUTE)
    get_filename_component(tp_name "${TP_FILE}" NAME_WE)
    add_custom_command(
        OUTPUT ${tp_name}.h ${tp_name}.c
        COMMAND ${LTTNG_GEN_TP} -o ${tp_name}.h -o ${tp_name}.c ${tp_file}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        DEPENDS ${tp_file}
        VERBATIM
    )
    target_sources(${TARGET} PRIVATE
        ${CMAKE_CURRENT_BINARY_DIR}/${tp_name}.c
        ${CMAKE_CURRENT_BINARY_DIR}/${tp_name}.h
    )
    target_include_directories(${TARGET} PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
    target_link_libraries(${TARGET} PRIVATE PkgConfig::LTTNG)
endfunction()
