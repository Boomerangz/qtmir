include(UseLttngGenTp)

add_definitions(-DQPA_MIRSERVER_NAME=\"${QPA_MIRSERVER_NAME}\")

include_directories(
    ${CMAKE_SOURCE_DIR}/src/platforms/mirserver
    ${CMAKE_SOURCE_DIR}/src/common
)

# Generate tracepoints.c and .h from tracepoints.tp
add_lttng_gen_tp(NAME tracepoints)
add_custom_target(QtMirApplication_LTTNG
    DEPENDS tracepoints.h tracepoints.c
)

set(QMLMIRPLUGIN_SRC
    application_manager.cpp
    application.cpp
    ../../../common/abstractdbusservicemonitor.cpp
    ../../../common/debughelpers.cpp
    dbusfocusinfo.cpp
    plugin.cpp
    mirsurface.cpp
    mirsurfaceinterface.h
    mirsurfaceitem.cpp
    mirsurfacelistmodel.cpp
    mirbuffersgtexture.cpp
    proc_info.cpp
    session.cpp
    sharedwakelock.cpp
    surfacemanager.cpp
    taskcontroller.cpp
    lal/applicationinfo.cpp
    lal/taskcontroller.cpp
    timer.cpp
    timesource.cpp
    tracepoints.c
    settings.cpp
    windowmodel.cpp
# We need to run moc on these headers
    ${CMAKE_SOURCE_DIR}/include/lomiri/shell/application/ApplicationInfoInterface.h
    ${CMAKE_SOURCE_DIR}/include/lomiri/shell/application/ApplicationManagerInterface.h
    ${CMAKE_SOURCE_DIR}/include/lomiri/shell/application/Mir.h
    ${CMAKE_SOURCE_DIR}/include/lomiri/shell/application/MirSurfaceInterface.h
    ${CMAKE_SOURCE_DIR}/include/lomiri/shell/application/MirSurfaceItemInterface.h
    ${CMAKE_SOURCE_DIR}/include/lomiri/shell/application/MirSurfaceListInterface.h
    ${CMAKE_SOURCE_DIR}/include/lomiri/shell/application/SurfaceManagerInterface.h
# Feed the automoc monster
    session_interface.h
    applicationinfo.h
    taskcontroller.h
    settings_interface.h
)

add_library(qtmirapplicationplugin SHARED
    ${QMLMIRPLUGIN_SRC}
)
add_dependencies(qtmirapplicationplugin QtMirApplication_LTTNG)

target_link_libraries(
    qtmirapplicationplugin
    PkgConfig::GLIB
    PkgConfig::GSETTINGS_QT
    PkgConfig::LOMIRI_APP_LAUNCH
    PkgConfig::LTTNG
    PkgConfig::MIRSERVER
    Qt::Core
    Qt::DBus
    Qt::GuiPrivate
    Qt::Qml
    Qt::QmlPrivate
    Qt::Quick
    Qt::QuickPrivate

    qtmirserver
)

if(NOT WITH_MIR2)
    target_link_libraries(qtmirapplicationplugin PkgConfig::MIRRENDERERGLDEV)
endif()


# install
add_qml_plugin(QtMir.Application 0.1 QtMir/Application TARGETS qtmirapplicationplugin)
install(FILES com.canonical.qtmir.gschema.xml DESTINATION ${CMAKE_INSTALL_DATADIR}/glib-2.0/schemas)
