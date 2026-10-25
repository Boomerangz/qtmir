set(
  MIR_WINDOW_MANAGER_TEST_SOURCES
#  mirsurfaceitem_test.cpp #FIXME - reinstate these tests when functionality there
  mirsurface_test.cpp
  mirsurfaceitemgeometry_test.cpp
  windowmodel_test.cpp
)

add_executable(windowmanager_test ${MIR_WINDOW_MANAGER_TEST_SOURCES})

target_link_libraries(
  windowmanager_test

  qtmirapplicationplugin

  Qt::Test
  Qt::QuickPrivate

  qtmir-test-framework-static

  PkgConfig::MIRAL
  PkgConfig::MIRTEST
  GTest::gmock_main
)

add_test(WindowManager windowmanager_test)
