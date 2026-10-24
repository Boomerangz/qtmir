cmake_minimum_required(VERSION 3.24)

project(qtmir)

set(QTMIR_VERSION_MAJOR 0)
set(QTMIR_VERSION_MINOR 7)
set(QTMIR_VERSION_PATCH 2)

set(QTMIR_VERSION ${QTMIR_VERSION_MAJOR}.${QTMIR_VERSION_MINOR}.${QTMIR_VERSION_PATCH})

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# add custom cmake modules
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules)

# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -Wall -fno-strict-aliasing -Wextra")
set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,--no-undefined")

set (CMAKE_C_STANDARD 17)
set (CMAKE_CXX_STANDARD 20)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_CXX_EXTENSIONS OFF)
# gtest receives only CMAKE_CXX_FLAGS and its C++ version must match
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++${CMAKE_CXX_STANDARD}")

option(WITH_CONTENTHUB "Build with content-hub" OFF)
option(WITH_MIR2 "Build with Mir 2" OFF)
option(Werror "Treat warnings as errors" ON)

include(FindPkgConfig)
find_package(Qt5Core 5.9 REQUIRED)
find_package(Qt5DBus 5.9 REQUIRED)
find_package(Qt5Gui 5.9 REQUIRED)
find_package(Qt5Qml 5.9 REQUIRED)
find_package(Qt5Quick 5.9 REQUIRED)
find_package(Qt5Sensors 5.9 REQUIRED)
find_package(Qt5Test 5.9 REQUIRED)
# TODO: when we support Qt 6, set QT_VERSION_MAJOR accordingly.
set(QT_VERSION_MAJOR 5)

find_package(Threads REQUIRED)

if(WITH_MIR2)
    pkg_check_modules(MIRSERVER mirserver>=2.25 REQUIRED)
    pkg_check_modules(MIRAL miral>=5.6 REQUIRED)
    pkg_search_module(MIRCOMMON mircommon REQUIRED)
    pkg_search_module(MIRCORE mircore REQUIRED)

    # Mir 2-specific
    pkg_check_modules(MIROIL miroil>=8.0 REQUIRED)

    # Wayland extension qt-windowmanager support
    pkg_search_module(MIRWAYLAND mirwayland>=1.2 REQUIRED)

    set(MIR_VERSION_MAJOR 2)
else()
    pkg_search_module(MIRSERVER REQUIRED mir1server>=0.26 mirserver>=0.26)
    pkg_search_module(MIRRENDERERGLDEV REQUIRED mir1-renderer-gl-dev>=0.26 mir-renderer-gl-dev>=0.26)
    pkg_search_module(MIRAL REQUIRED mir1al>=1.1.0 miral>=1.1.0)
    pkg_search_module(MIRCOMMON mir1common REQUIRED)
    pkg_search_module(MIRCORE mir1core REQUIRED)

    # Wayland extension qt-windowmanager support
    pkg_search_module(MIRWAYLAND mir1wayland>=1.2 REQUIRED)

    pkg_check_modules(MIRTEST mir1test>=0.26 REQUIRED)

    # Bundled miroil for Mir1
    set(MIROIL_INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/src/platforms/mirserver/miroil/include)

    set(MIR_VERSION_MAJOR 1)
endif()

pkg_check_modules(WAYLAND_SERVER REQUIRED wayland-server)

pkg_check_modules(XKBCOMMON xkbcommon REQUIRED)
pkg_check_modules(GLIB glib-2.0 REQUIRED)
pkg_check_modules(LOMIRI_APP_LAUNCH lomiri-app-launch-0 REQUIRED)
pkg_check_modules(URL_DISPATCHER lomiri-url-dispatcher REQUIRED)
pkg_check_modules(EGL egl)
pkg_check_modules(LTTNG lttng-ust)
pkg_check_modules(GSETTINGS_QT REQUIRED gsettings-qt)

if(WITH_CONTENTHUB)
pkg_check_modules(CONTENT_HUB liblomiri-content-hub>=1.0.0 REQUIRED)
message(STATUS "Bulding with content-hub")
endif()

include_directories(SYSTEM ${Qt5Core_INCLUDE_DIRS})

# Lomiri shell Application API headers (lomiri/shell/application/*.h, formerly
# from liblomiri-shell-api-dev) now live in this tree; make them globally
# available like the pkg-config module used to.
include_directories(${CMAKE_SOURCE_DIR}/include)

# Use the fast string builder
add_definitions(-DQT_USE_QSTRINGBUILDER)

# Standard install paths
include(GNUInstallDirs)


# Set QML module install path
set(QML_MODULE_INSTALL_DIR "${CMAKE_INSTALL_FULL_LIBDIR}/qt5/qml")
set(QTMIR_DATA_DIR ${CMAKE_INSTALL_FULL_DATADIR}/qtmir)
set(QPA_PLUGIN_INSTALL_DIR "${CMAKE_INSTALL_FULL_LIBDIR}/qt5/plugins/platforms")

if (Werror)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Werror")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror")
endif()


# Mir uses boost, which does not like Qt defining macros named "signals" and "slots"
add_definitions(-DQT_NO_KEYWORDS)

if (NO_TESTS)
    message(STATUS "Tests disabled")
else()
    pkg_check_modules(QTDBUSTEST libqtdbustest-1 REQUIRED)
    pkg_check_modules(QTDBUSMOCK libqtdbusmock-1 REQUIRED)

    include(CTest)
    enable_testing()
    add_subdirectory(tests)
endif()

add_subdirectory(src)
add_subdirectory(demos)
add_subdirectory(data)
