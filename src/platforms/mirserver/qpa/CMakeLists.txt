configure_file(mirserver.json.in mirserver.json)

add_library(qpa-mirserver SHARED
    mirserverintegration.cpp
    plugin.cpp
)

target_include_directories(qpa-mirserver PRIVATE ${CMAKE_CURRENT_BINARY_DIR})

set_target_properties(qpa-mirserver PROPERTIES
    OUTPUT_NAME "qpa-${QPA_MIRSERVER_NAME}"
)

target_link_libraries(qpa-mirserver PRIVATE
    qtmirserver
    PkgConfig::EGL
    PkgConfig::LTTNG
    PkgConfig::MIRCOMMON
    PkgConfig::MIRWAYLAND
    PkgConfig::URL_DISPATCHER
    PkgConfig::WAYLAND_SERVER
    PkgConfig::XKBCOMMON
    Qt::Core
    Qt::DBus
    Qt::GuiPrivate
    Qt::Qml
    Qt::Quick
    Qt::QuickPrivate
    Qt::Sensors
    Qt::EventDispatcherSupportPrivate
    Qt::FontDatabaseSupportPrivate
    Qt::ServiceSupportPrivate
    Qt::ThemeSupportPrivate
)

if(NOT WITH_MIR2)
    target_link_libraries(qpa-mirserver PRIVATE PkgConfig::MIRRENDERERGLDEV)
endif()

if(WITH_CONTENTHUB)
    target_compile_definitions(qpa-mirserver PRIVATE WITH_CONTENTHUB)
    target_link_libraries(qpa-mirserver PRIVATE PkgConfig::CONTENT_HUB)
endif()

install(TARGETS qpa-mirserver LIBRARY DESTINATION "${QPA_PLUGIN_INSTALL_DIR}")
