add_executable(surfacemanager_test surface_manager_test.cpp)

target_link_libraries(surfacemanager_test PRIVATE
    qtmirapplicationplugin
    qtmir-test-framework-static
    PkgConfig::MIRTEST
    Qt::Test
    GTest::gmock_main
)

add_test(NAME SurfaceManager COMMAND surfacemanager_test)
