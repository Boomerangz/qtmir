set(DEMO_CLIENT qtmir-demo-client)
configure_file(${DEMO_CLIENT}.desktop.in ${CMAKE_CURRENT_BINARY_DIR}/${DEMO_CLIENT}.desktop @ONLY)

add_executable(${DEMO_CLIENT}
    main.cpp
)

target_include_directories(${DEMO_CLIENT} PRIVATE ${CMAKE_CURRENT_BINARY_DIR})

target_link_libraries(${DEMO_CLIENT} PRIVATE
    Qt::Core
    Qt::DBus
    Qt::Qml
    Qt::Quick
)

file(GLOB QML_JS_FILES *.qml *.js *.png)

add_custom_target(${DEMO_CLIENT}-qmlfiles SOURCES ${QML_JS_FILES})

# install binaries
install(TARGETS ${DEMO_CLIENT}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

install(FILES ${QML_JS_FILES}
    DESTINATION ${QTMIR_DATA_DIR}/${DEMO_CLIENT}
)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${DEMO_CLIENT}.desktop
    DESTINATION ${CMAKE_INSTALL_PREFIX}/share/applications
)
