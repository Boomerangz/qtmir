set(
  SURFACE_MANAGER_TEST_SOURCES
  surface_manager_test.cpp
)

add_executable(surfacemanager_test ${SURFACE_MANAGER_TEST_SOURCES})


target_link_libraries(
  surfacemanager_test

  qtmirapplicationplugin

  Qt::Test

  qtmir-test-framework-static

  PkgConfig::MIRTEST
  GTest::gmock_main
)

add_test(SurfaceManager, surfacemanager_test)
