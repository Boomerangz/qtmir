include(UseLttngGenTp)

set(INCLUDE_NAME "qtmir-qt${QT_VERSION_MAJOR}-mir${MIR_VERSION_MAJOR}")
set(QTMIRSERVER_SONAME "qt${QT_VERSION_MAJOR}mir${MIR_VERSION_MAJOR}server")

# TODO: consider the miroil/miral SOVERSION with Mir2
set(QTMIRSERVER_ABI 1)

if(NOT WITH_MIR2)
    add_subdirectory(miroil)
endif()
add_subdirectory(qpa)
add_subdirectory(wayland-generated)

if (WITH_CONTENTHUB)
    add_definitions(-DWITH_CONTENTHUB)
endif()

set(QTMIRSERVER_PUBLIC_DEPS
    qtmir-common
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
    ${CMAKE_SOURCE_DIR}/include/qtmir/mirserverapplication.h
    ${CMAKE_SOURCE_DIR}/include/qtmir/displayconfigurationpolicy.h
    ${CMAKE_SOURCE_DIR}/include/qtmir/sessionauthorizer.h
    ${CMAKE_SOURCE_DIR}/include/qtmir/windowmanagementpolicy.h
    ${CMAKE_SOURCE_DIR}/include/qtmir/displayconfigurationstorage.h
    ${CMAKE_SOURCE_DIR}/include/qtmir/screen.h
    ${CMAKE_SOURCE_DIR}/include/qtmir/screens.h
    ${CMAKE_SOURCE_DIR}/include/qtmir/types.h
    ${CMAKE_SOURCE_DIR}/include/qtmir/qtmir.h
)

add_library(qtmirserver SHARED
    ${QMIRSERVER_PLUGIN_SRC}
    $<TARGET_OBJECTS:qtmirserver-nomirserver>
    $<TARGET_OBJECTS:qtmirserver-mirserver>
    $<TARGET_OBJECTS:wayland-protocols>
)

target_link_libraries(qtmirserver
    PUBLIC
        lomiri-shell-application
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

# WORKAROUND: tests and qpa need private header files
target_include_directories(qtmirserver PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_compile_definitions(qtmirserver PUBLIC QPA_MIRSERVER_NAME=\"${QPA_MIRSERVER_NAME}\")

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
        miroil/include/miroil/display_configuration_policy.h
        miroil/include/miroil/display_configuration_storage.h
        miroil/include/miroil/display_id.h
        miroil/include/miroil/edid.h
      DESTINATION ${INCLUDEDIR}/miroil
    )
endif()

install(
  FILES ${CMAKE_CURRENT_BINARY_DIR}/${QTMIRSERVER_SONAME}.pc
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig
)
