set(
  SURFACE_MANAGER_TEST_SOURCES
  surface_manager_test.cpp
  ${CMAKE_SOURCE_DIR}/src/common/debughelpers.cpp
)

include_directories(
  ${CMAKE_SOURCE_DIR}/src/common
  ${CMAKE_SOURCE_DIR}/src/platforms/mirserver
  ${CMAKE_SOURCE_DIR}/src/modules
  ${CMAKE_SOURCE_DIR}/tests/framework
)

include_directories(
  SYSTEM
  ${MIROIL_INCLUDE_DIRS}
  ${MIRAL_INCLUDE_DIRS}
  ${MIRTEST_INCLUDE_DIRS}
)

add_executable(surfacemanager_test ${SURFACE_MANAGER_TEST_SOURCES})


target_link_libraries(
  surfacemanager_test

  qtmirapplicationplugin

  Qt5::Test

  qtmir-test-framework-static

  ${MIRTEST_LDFLAGS}
  ${GTEST_BOTH_LIBRARIES}
  ${GMOCK_LIBRARIES}
)

add_test(SurfaceManager, surfacemanager_test)
