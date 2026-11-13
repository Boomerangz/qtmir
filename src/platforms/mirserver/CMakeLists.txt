include(UseLttngGenTp)
include(WaylandProtocolGenerator)

set(QTMIRSERVER_SONAME "qt${QT_VERSION_MAJOR}mir${MIR_VERSION_MAJOR}server")

# TODO: consider the miroil/miral SOVERSION with Mir2
set(QTMIRSERVER_ABI 1)

file(GLOB QTMIRSERVER_SRC CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
    ${CMAKE_SOURCE_DIR}/include/qtmir/*.h
)

if(NOT WITH_CONTENTHUB)
    list(REMOVE_ITEM QTMIRSERVER_SRC ${CMAKE_CURRENT_SOURCE_DIR}/clipboard.cpp)
endif()

if(WITH_MIR2)
    list(REMOVE_ITEM QTMIRSERVER_SRC
        ${CMAKE_CURRENT_SOURCE_DIR}/promptsessionlistener.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/promptsessionmanager.cpp
    )
endif()

add_library(qtmirserver SHARED
    ${QTMIRSERVER_SRC}
)

add_lttng_tracepoints(qtmirserver tracepoints.tp)
add_wayland_protocol(qtmirserver "qt_" wayland-protocols/qt-windowmanager.xml)

target_link_libraries(qtmirserver
    PUBLIC
        lomiri-shell-application
        qtmir-common
        PkgConfig::MIRAL
        PkgConfig::MIRSERVER
        Qt::Core
        Qt::Gui

    PRIVATE
        PkgConfig::EGL
        PkgConfig::MIRCOMMON
        PkgConfig::MIRWAYLAND
        PkgConfig::URL_DISPATCHER
        PkgConfig::WAYLAND_SERVER
        PkgConfig::XKBCOMMON
        PkgConfig::DEVICEINFO
        Qt::DBus
        Qt::GuiPrivate
        Qt::Quick
        Qt::QuickPrivate
        Qt::Sensors
        Qt::EglSupportPrivate
)

if(WITH_MIR2)
    target_link_libraries(qtmirserver PUBLIC PkgConfig::MIROIL)
else()
    target_link_libraries(qtmirserver PUBLIC miroil PRIVATE PkgConfig::MIRRENDERERGLDEV)
endif()

if(WITH_CONTENTHUB)
    target_link_libraries(qtmirserver PRIVATE PkgConfig::CONTENT_HUB)
endif()

# WORKAROUND: tests and qpa need private header files
target_include_directories(qtmirserver PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_compile_definitions(qtmirserver PUBLIC QPA_MIRSERVER_NAME=\"${QPA_MIRSERVER_NAME}\")

set_target_properties(qtmirserver PROPERTIES
    OUTPUT_NAME ${QTMIRSERVER_SONAME}
    SOVERSION ${QTMIRSERVER_ABI}
)

# Variables to be substituted in the .pc file
set(LIBDIR "${CMAKE_INSTALL_FULL_LIBDIR}")
set(INCLUDE_NAME "qtmir-qt${QT_VERSION_MAJOR}-mir${MIR_VERSION_MAJOR}")
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

install(
  FILES ${CMAKE_CURRENT_BINARY_DIR}/${QTMIRSERVER_SONAME}.pc
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig
)

if(NOT WITH_MIR2)
    add_subdirectory(miroil)
endif()
add_subdirectory(qpa)
