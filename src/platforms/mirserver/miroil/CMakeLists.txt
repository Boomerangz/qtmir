install(
    FILES
        include/miroil/display_configuration_policy.h
        include/miroil/display_configuration_storage.h
        include/miroil/display_id.h
        include/miroil/edid.h
    DESTINATION ${INCLUDEDIR}/miroil
)

add_subdirectory(src)
