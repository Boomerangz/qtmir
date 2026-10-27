find_package(GTest REQUIRED)

pkg_check_modules(QTDBUSTEST REQUIRED IMPORTED_TARGET libqtdbustest-1)
pkg_check_modules(QTDBUSMOCK REQUIRED IMPORTED_TARGET libqtdbusmock-1)

if(NOT WITH_MIR2)
    # TODO: fix for Mir2
    add_subdirectory(framework)
endif()
add_subdirectory(mirserver)
add_subdirectory(modules)
