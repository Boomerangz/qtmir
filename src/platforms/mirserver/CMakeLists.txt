include(UseLttngGenTp)

set(INCLUDE_NAME "qtmir-qt${QT_VERSION_MAJOR}-mir${MIR_VERSION_MAJOR}")
set(QTMIRSERVER_SONAME "qt${QT_VERSION_MAJOR}mir${MIR_VERSION_MAJOR}server")
set(QPA_MIRSERVER_NAME "mir${MIR_VERSION_MAJOR}server")
set(QPA_MIRSERVER_SONAME "qpa-${QPA_MIRSERVER_NAME}")

# Used by src/modules and demos/ directories.
set(QPA_MIRSERVER_NAME "${QPA_MIRSERVER_NAME}" PARENT_SCOPE)

add_definitions(-DQPA_MIRSERVER_NAME=\"${QPA_MIRSERVER_NAME}\")

# TODO: consider the miroil/miral SOVERSION with Mir2
set(QTMIRSERVER_ABI 1)

set(qtmir_include ${CMAKE_SOURCE_DIR}/include)

if(NOT WITH_MIR2)
    add_subdirectory(miroil)
endif()

add_subdirectory(wayland-generated)

if (WITH_CONTENTHUB)
    add_definitions(-DWITH_CONTENTHUB)
endif()

include_directories(
    ${CMAKE_SOURCE_DIR}/src/common
)

set(QTMIRSERVER_PUBLIC_DEPS
    PkgConfig::MIRAL
    PkgConfig::MIRSERVER
)

set(QTMIRSERVER_PRIVATE_DEPS
    PkgConfig::EGL
    PkgConfig::LTTNG
    PkgConfig::MIRCOMMON
    PkgConfig::MIRWAYLAND
    PkgConfig::URL_DISPATCHER
    PkgConfig::WAYLAND_SERVER
    PkgConfig::XKBCOMMON
)

if(WITH_MIR2)
    list(APPEND QTMIRSERVER_PUBLIC_DEPS PkgConfig::MIROIL)
else()
    list(APPEND QTMIRSERVER_PUBLIC_DEPS miroil)
    list(APPEND QTMIRSERVER_PRIVATE_DEPS PkgConfig::MIRRENDERERGLDEV)
endif()

if(WITH_CONTENTHUB)
    list(APPEND QTMIRSERVER_PRIVATE_DEPS PkgConfig::CONTENT_HUB)
endif()

set_source_files_properties(tracepoints.c PROPERTIES COMPILE_FLAGS "-fPIC")

# Generate tracepoints.c and .h from tracepoints.tp
add_lttng_gen_tp(NAME tracepoints)
add_custom_target(MirServer_LTTNG
    DEPENDS tracepoints.h tracepoints.c
)

if(WITH_CONTENTHUB)
    set(CLIPBOARD_SRC clipboard.cpp)
endif()

if(NOT WITH_MIR2)
    set(PROMPTSESSION_NOMIRSERVER_SRC promptsessionlistener.cpp)
    set(PROMPTSESSION_MIRSERVER_SRC promptsessionmanager.cpp promptsessionmanager.h promptsession.h)
endif()

# These files will compile without mirserver-dev
add_library(qtmirserver-nomirserver OBJECT
    ${CMAKE_SOURCE_DIR}/src/common/timestamp.cpp
    ${CLIPBOARD_SRC}
    logging.cpp
    shelluuid.cpp
    mirsingleton.cpp
    wrappedsessionauthorizer.cpp
    ${PROMPTSESSION_NOMIRSERVER_SRC}
    displayconfigurationstorage.cpp
    nativeinterface.cpp
    services.cpp
    urlbuilderdispatcher.cpp
    windowcontroller.cpp
    workspacecontroller.cpp
    tracepoints.c
    surfaceobserver.cpp
    initialsurfacesizes.cpp
    inputmethodauthorizer.cpp
    orientationsensor.cpp
    screenadaptor.cpp
    screenadaptormodel.cpp
    qtmir.cpp
)
add_dependencies(qtmirserver-nomirserver MirServer_LTTNG)
target_link_libraries(qtmirserver-nomirserver PRIVATE ${QTMIRSERVER_PUBLIC_DEPS} ${QTMIRSERVER_PRIVATE_DEPS} Qt::DBus Qt::GuiPrivate Qt::QuickPrivate Qt::Sensors)

# These files will only compile with mirserver-dev
add_library(qtmirserver-mirserver OBJECT
    screenscontroller.cpp
    qtcompositor.cpp
    displayconfigurationpolicy.cpp
    wrappedwindowmanagementpolicy.cpp
    ${PROMPTSESSION_MIRSERVER_SRC}
)
add_dependencies(qtmirserver-mirserver MirServer_LTTNG)
target_link_libraries(qtmirserver-mirserver PRIVATE ${QTMIRSERVER_PUBLIC_DEPS} ${QTMIRSERVER_PRIVATE_DEPS} Qt::DBus Qt::GuiPrivate Qt::QuickPrivate Qt::Sensors)

# These files get entangled by automoc so they need to go together. And some depend on mirserver-dev
set(QMIRSERVER_PLUGIN_SRC
    ${CMAKE_SOURCE_DIR}/src/common/debughelpers.cpp
    cursor.cpp
    eventbuilder.cpp
    qtwindowmanager.cpp
    qteventfeeder.cpp
    qmirserver.cpp
    qmirserver_p.cpp
    platformscreen.cpp
    screenplatformwindow.cpp
    screensmodel.cpp
    miropenglcontext.cpp
    offscreensurface.cpp
    inputdeviceobserver.cpp
    mirserverapplication.cpp
    windowmodelnotifier.cpp

# We need to run moc on these headers
    ${CMAKE_SOURCE_DIR}/include/lomiri/shell/application/MirMousePointerInterface.h
    ${CMAKE_SOURCE_DIR}/include/lomiri/shell/application/Mir.h

    ${CMAKE_SOURCE_DIR}/include/qtmir/mirserverapplication.h
    ${CMAKE_SOURCE_DIR}/include/qtmir/displayconfigurationpolicy.h
    ${CMAKE_SOURCE_DIR}/include/qtmir/sessionauthorizer.h
    ${CMAKE_SOURCE_DIR}/include/qtmir/windowmanagementpolicy.h
    ${CMAKE_SOURCE_DIR}/include/qtmir/displayconfigurationstorage.h
    ${CMAKE_SOURCE_DIR}/include/qtmir/screen.h
    ${CMAKE_SOURCE_DIR}/include/qtmir/screens.h
    ${CMAKE_SOURCE_DIR}/include/qtmir/types.h
    ${CMAKE_SOURCE_DIR}/include/qtmir/qtmir.h

    ${CMAKE_SOURCE_DIR}/src/common/windowcontrollerinterface.h
    ${CMAKE_SOURCE_DIR}/src/common/workspacecontrollerinterface.h
    ${CMAKE_SOURCE_DIR}/src/common/windowmodelnotifier.h
    ${CMAKE_SOURCE_DIR}/src/common/appnotifier.h
)

add_library(qtmirserver SHARED
    ${QMIRSERVER_PLUGIN_SRC}
    $<TARGET_OBJECTS:qtmirserver-nomirserver>
    $<TARGET_OBJECTS:qtmirserver-mirserver>
    $<TARGET_OBJECTS:wayland-protocols>
)

target_link_libraries(qtmirserver
    PUBLIC
        ${QTMIRSERVER_PUBLIC_DEPS}
        Qt::Core
        Qt::Gui

    PRIVATE
        ${QTMIRSERVER_PRIVATE_DEPS}
        Qt::DBus
        Qt::GuiPrivate
        Qt::Quick
        Qt::QuickPrivate
        Qt::Sensors
        Qt::EglSupportPrivate
)

set_target_properties(qtmirserver
  PROPERTIES
  OUTPUT_NAME ${QTMIRSERVER_SONAME}
  SOVERSION ${QTMIRSERVER_ABI}
)

set(LIBDIR "${CMAKE_INSTALL_FULL_LIBDIR}")
set(INCLUDEDIR "${CMAKE_INSTALL_FULL_INCLUDEDIR}/${INCLUDE_NAME}")
if(WITH_MIR2)
    set(QTMIRSERVER_PCREQUIRES "miral >= 5.6, miroil >= 8.0, mirserver >= 2.25")
else()
    set(QTMIRSERVER_PCREQUIRES "${MIRAL_MODULE_NAME} >= 1.1, ${MIRSERVER_MODULE_NAME} >= 0.26")
    set(QTMIRSERVER_PCCONFLICTS "miral >= 3.0")
endif()

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/qtXmirYserver.pc.in
    ${CMAKE_CURRENT_BINARY_DIR}/${QTMIRSERVER_SONAME}.pc
    @ONLY
)

install(
  TARGETS qtmirserver
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

install(
  DIRECTORY ${CMAKE_SOURCE_DIR}/include/qtmir
  DESTINATION ${INCLUDEDIR}
)

if(NOT WITH_MIR2)
    install(
      FILES
        ${MIROIL_INCLUDE_DIRS}/miroil/display_configuration_policy.h
        ${MIROIL_INCLUDE_DIRS}/miroil/display_configuration_storage.h
        ${MIROIL_INCLUDE_DIRS}/miroil/display_id.h
        ${MIROIL_INCLUDE_DIRS}/miroil/edid.h
      DESTINATION ${INCLUDEDIR}/miroil
    )
endif()

install(
  FILES ${CMAKE_CURRENT_BINARY_DIR}/${QTMIRSERVER_SONAME}.pc
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig
)

# Lomiri shell Application API: header-only interfaces that qtmir implements.
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/lomiri-shell-application.pc.in
    ${CMAKE_CURRENT_BINARY_DIR}/lomiri-shell-application.pc
    @ONLY
)

install(
  DIRECTORY ${CMAKE_SOURCE_DIR}/include/lomiri
  DESTINATION ${CMAKE_INSTALL_FULL_INCLUDEDIR}/lomiri-shell-api
)

install(
  FILES ${CMAKE_CURRENT_BINARY_DIR}/lomiri-shell-application.pc
  DESTINATION ${CMAKE_INSTALL_DATADIR}/pkgconfig
)

configure_file(mirserver.json.in mirserver.json)

add_library(qpa-mirserver SHARED
    mirserverintegration.cpp
    plugin.cpp
)

set_target_properties(qpa-mirserver
  PROPERTIES
  OUTPUT_NAME ${QPA_MIRSERVER_SONAME})

target_link_libraries(qpa-mirserver PRIVATE
    qtmirserver
    ${QTMIRSERVER_PRIVATE_DEPS}
    Qt::Core
    Qt::DBus
    Qt::GuiPrivate
    Qt::Quick
    Qt::QuickPrivate
    Qt::Sensors
    Qt::Qml
    Qt::EventDispatcherSupportPrivate
    Qt::FontDatabaseSupportPrivate
    Qt::ServiceSupportPrivate
    Qt::ThemeSupportPrivate
)

install(TARGETS qpa-mirserver LIBRARY DESTINATION "${QPA_PLUGIN_INSTALL_DIR}")
