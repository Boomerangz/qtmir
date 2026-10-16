set(DEMO_SHELL qtmir-demo-shell)

add_definitions(-DQPA_MIRSERVER_NAME=\"${QPA_MIRSERVER_NAME}\")

include_directories(
    SYSTEM
    ${MIRSERVER_INCLUDE_DIRS}
    ${MIROIL_INCLUDE_DIRS}
    ${MIRAL_INCLUDE_DIRS}
)

add_executable(${DEMO_SHELL}
    pointerposition.cpp
    screenwindow.cpp
    screens.cpp
    main.cpp
)

target_link_libraries(
    ${DEMO_SHELL}

    qtmirserver

    Qt::Core
    Qt::DBus
    Qt::Qml
    Qt::Quick
)

file(GLOB QML_JS_FILES *.qml *.js *.png)

add_custom_target(${DEMO_SHELL}-qmlfiles
                  SOURCES ${QML_JS_FILES})

# install binaries
install(TARGETS ${DEMO_SHELL}
     RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
 )

install(FILES
    ${QML_JS_FILES}
    DESTINATION ${QTMIR_DATA_DIR}/${DEMO_SHELL}
)
