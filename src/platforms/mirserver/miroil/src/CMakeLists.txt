file(GLOB MIROIL_SRC CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

add_library(miroil OBJECT
    ${MIROIL_SRC}
)

target_include_directories(miroil PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../include")

target_link_libraries(miroil PRIVATE
    PkgConfig::EGL
    PkgConfig::MIRAL
    PkgConfig::MIRCOMMON
    PkgConfig::MIRRENDERERGLDEV
    PkgConfig::MIRSERVER
    Qt::Core
)
