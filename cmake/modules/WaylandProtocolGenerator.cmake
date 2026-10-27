if(WITH_MIR2)
    find_program(MIR_WAYLAND_GENERATOR mir_wayland_generator REQUIRED)
else()
    find_program(MIR_WAYLAND_GENERATOR mir1_wayland_generator REQUIRED)
endif()

function(add_wayland_protocol TARGET PREFIX PROTOCOL_FILE)
    get_filename_component(protocol_file "${PROTOCOL_FILE}" ABSOLUTE)
    get_filename_component(protocol_name "${PROTOCOL_FILE}" NAME_WE)

    set(output_dir "${CMAKE_CURRENT_BINARY_DIR}/wayland-generated")
    set(generated_file "${output_dir}/${protocol_name}_wrapper")
    file(MAKE_DIRECTORY "${output_dir}")

    add_custom_command(
        OUTPUT ${generated_file}.h ${generated_file}.cpp
        COMMAND sh -c "${MIR_WAYLAND_GENERATOR} ${PREFIX} ${protocol_file} header > ${generated_file}.h"
        COMMAND sh -c "${MIR_WAYLAND_GENERATOR} ${PREFIX} ${protocol_file} source > ${generated_file}.cpp"
        DEPENDS ${MIR_WAYLAND_GENERATOR} ${protocol_file}
        VERBATIM
    )
    target_sources(${TARGET} PRIVATE
        ${generated_file}.h
        ${generated_file}.cpp
    )
    target_include_directories(${TARGET} PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
    target_link_libraries(${TARGET} PRIVATE PkgConfig::MIRWAYLAND)
endfunction()
