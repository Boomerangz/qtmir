include(UseLttngGenTp)

file(GLOB QMLMIRPLUGIN_SRC CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/lal/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/lal/*.h
)

qt_add_qml_module(qtmirapplicationplugin
    URI QtMir.Application
    VERSION 0.1
    PLUGIN_TARGET qtmirapplicationplugin
    CLASS_NAME QtMirApplicationPlugin
    NO_GENERATE_PLUGIN_SOURCE
    SOURCES ${QMLMIRPLUGIN_SRC}
)

add_lttng_tracepoints(qtmirapplicationplugin tracepoints.tp)

target_include_directories(qtmirapplicationplugin PUBLIC ${CMAKE_SOURCE_DIR}/src/modules)

target_link_libraries(qtmirapplicationplugin PUBLIC
    qtmirserver
    PkgConfig::GLIB
    PkgConfig::GSETTINGS_QT
    PkgConfig::LOMIRI_APP_LAUNCH
    PkgConfig::MIRSERVER
    Qt::Core
    Qt::DBus
    Qt::GuiPrivate
    Qt::Qml
    Qt::QmlPrivate
    Qt::Quick
    Qt::QuickPrivate
)

if(NOT WITH_MIR2)
    target_link_libraries(qtmirapplicationplugin PRIVATE PkgConfig::MIRRENDERERGLDEV)
endif()

install(TARGETS qtmirapplicationplugin DESTINATION ${QML_MODULE_INSTALL_DIR}/QtMir/Application)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/qmldir DESTINATION ${QML_MODULE_INSTALL_DIR}/QtMir/Application)
install(FILES com.canonical.qtmir.gschema.xml DESTINATION ${CMAKE_INSTALL_DATADIR}/glib-2.0/schemas)
