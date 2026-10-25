include(UseLttngGenTp)

set(QMLMIRPLUGIN_SRC
    application_manager.cpp
    application.cpp
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
    settings.cpp
    windowmodel.cpp
# Feed the automoc monster
    session_interface.h
    applicationinfo.h
    taskcontroller.h
    settings_interface.h
)

add_library(qtmirapplicationplugin SHARED
    ${QMLMIRPLUGIN_SRC}
)

add_lttng_tracepoints(qtmirapplicationplugin tracepoints.tp)

target_link_libraries(
    qtmirapplicationplugin
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

    qtmirserver
)

if(NOT WITH_MIR2)
    target_link_libraries(qtmirapplicationplugin PkgConfig::MIRRENDERERGLDEV)
endif()


# install
add_qml_plugin(QtMir.Application 0.1 QtMir/Application TARGETS qtmirapplicationplugin)
install(FILES com.canonical.qtmir.gschema.xml DESTINATION ${CMAKE_INSTALL_DATADIR}/glib-2.0/schemas)
