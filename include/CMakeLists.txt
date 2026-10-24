file(GLOB LOMIRI_SHELL_APPLICATION_HEADERS CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/lomiri/shell/application/*.h
)

# Make this an object library for internal use, so moc runs on the headers
add_library(lomiri-shell-application OBJECT ${LOMIRI_SHELL_APPLICATION_HEADERS})

target_include_directories(lomiri-shell-application PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(lomiri-shell-application PUBLIC
    Qt::Core
    Qt::Gui
    Qt::Quick
)

configure_file(lomiri-shell-application.pc.in
    ${CMAKE_CURRENT_BINARY_DIR}/lomiri-shell-application.pc
    @ONLY
)

install(
    DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lomiri
    DESTINATION ${CMAKE_INSTALL_FULL_INCLUDEDIR}/lomiri-shell-api
)

install(
    FILES ${CMAKE_CURRENT_BINARY_DIR}/lomiri-shell-application.pc
    DESTINATION ${CMAKE_INSTALL_DATADIR}/pkgconfig
)
