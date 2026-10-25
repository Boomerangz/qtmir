set(
  SURFACE_MANAGER_TEST_SOURCES
  surface_manager_test.cpp
)

include_directories(
  ${CMAKE_SOURCE_DIR}/src/modules
  ${CMAKE_SOURCE_DIR}/tests/framework
)

add_executable(surfacemanager_test ${SURFACE_MANAGER_TEST_SOURCES})


target_link_libraries(
  surfacemanager_test

  qtmirapplicationplugin

  Qt::Test

  qtmir-test-framework-static

  PkgConfig::MIRTEST
  ${GTEST_BOTH_LIBRARIES}
  ${GMOCK_LIBRARIES}
)

add_test(SurfaceManager, surfacemanager_test)
