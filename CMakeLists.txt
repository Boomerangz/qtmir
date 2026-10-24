cmake_minimum_required(VERSION 3.24)

project(qtmir VERSION 0.7.2 LANGUAGES C CXX)

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

set(QT_VERSION_MAJOR 5)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS
    Core DBus Gui Qml Quick Sensors Test
    # For the QPA
    EglSupport
    EventDispatcherSupport
    FontDatabaseSupport
    ServiceSupport
    ThemeSupport
)

if(WITH_MIR2)
    pkg_check_modules(MIRSERVER REQUIRED IMPORTED_TARGET mirserver>=2.25)
    pkg_check_modules(MIRAL REQUIRED IMPORTED_TARGET miral>=5.6)
    pkg_check_modules(MIRCOMMON REQUIRED IMPORTED_TARGET mircommon)
    pkg_check_modules(MIRCORE REQUIRED IMPORTED_TARGET mircore)
    pkg_check_modules(MIROIL REQUIRED IMPORTED_TARGET miroil>=8.0)
    pkg_check_modules(MIRWAYLAND REQUIRED IMPORTED_TARGET mirwayland>=1.2)

    set(MIR_VERSION_MAJOR 2)
else()
    pkg_search_module(MIRSERVER REQUIRED IMPORTED_TARGET mir1server>=0.26 mirserver>=0.26)
    pkg_search_module(MIRRENDERERGLDEV REQUIRED IMPORTED_TARGET mir1-renderer-gl-dev>=0.26 mir-renderer-gl-dev>=0.26)
    pkg_search_module(MIRAL REQUIRED IMPORTED_TARGET mir1al>=1.1.0 miral>=1.1.0)
    pkg_check_modules(MIRCOMMON REQUIRED IMPORTED_TARGET mir1common)
    pkg_check_modules(MIRCORE REQUIRED IMPORTED_TARGET mir1core)
    pkg_check_modules(MIRWAYLAND REQUIRED IMPORTED_TARGET mir1wayland>=1.2)
    pkg_check_modules(MIRTEST REQUIRED IMPORTED_TARGET mir1test>=0.26)

    # Bundled miroil for Mir1
    set(MIROIL_INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/src/platforms/mirserver/miroil/include)

    set(MIR_VERSION_MAJOR 1)
endif()

pkg_check_modules(WAYLAND_SERVER REQUIRED IMPORTED_TARGET wayland-server)
pkg_check_modules(XKBCOMMON REQUIRED IMPORTED_TARGET xkbcommon)
pkg_check_modules(GLIB REQUIRED IMPORTED_TARGET glib-2.0)
pkg_check_modules(LOMIRI_APP_LAUNCH REQUIRED IMPORTED_TARGET lomiri-app-launch-0)
pkg_check_modules(URL_DISPATCHER REQUIRED IMPORTED_TARGET lomiri-url-dispatcher)
pkg_check_modules(EGL REQUIRED IMPORTED_TARGET egl)
pkg_check_modules(LTTNG REQUIRED IMPORTED_TARGET lttng-ust)
pkg_check_modules(GSETTINGS_QT REQUIRED IMPORTED_TARGET gsettings-qt)

if(WITH_CONTENTHUB)
    pkg_check_modules(CONTENT_HUB REQUIRED IMPORTED_TARGET liblomiri-content-hub>=1.0.0)
endif()

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
    pkg_check_modules(QTDBUSTEST REQUIRED IMPORTED_TARGET libqtdbustest-1)
    pkg_check_modules(QTDBUSMOCK REQUIRED IMPORTED_TARGET libqtdbusmock-1)

    include(CTest)
    enable_testing()
    add_subdirectory(tests)
endif()

add_subdirectory(src)
add_subdirectory(demos)
add_subdirectory(data)
