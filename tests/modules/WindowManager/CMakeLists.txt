add_executable(windowmanager_test
    # mirsurfaceitem_test.cpp #FIXME - reinstate these tests when functionality there
    mirsurface_test.cpp
    mirsurfaceitemgeometry_test.cpp
    windowmodel_test.cpp
)

target_link_libraries(windowmanager_test PRIVATE
    qtmirapplicationplugin
    qtmir-test-framework-static
    PkgConfig::MIRAL
    PkgConfig::MIRTEST
    Qt::QuickPrivate
    Qt::Test
    GTest::gmock_main
)

add_test(NAME WindowManager COMMAND windowmanager_test)
