find_package(GTest REQUIRED)

if(NOT WITH_MIR2)
    # TODO: fix for Mir2
    add_subdirectory(framework)
endif()
add_subdirectory(mirserver)
add_subdirectory(modules)
