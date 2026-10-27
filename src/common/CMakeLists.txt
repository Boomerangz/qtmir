file(GLOB QTMIR_COMMON_SRC CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/*.h
)

add_library(qtmir-common OBJECT
    ${QTMIR_COMMON_SRC}
)

target_include_directories(qtmir-common PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(qtmir-common PUBLIC
    lomiri-shell-application
    PkgConfig::MIRAL
    PkgConfig::MIRCOMMON
    PkgConfig::MIRCORE
    PkgConfig::MIRSERVER
    Qt::Core
    Qt::DBus
    Qt::Gui
)
