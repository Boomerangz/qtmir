set(
  SHARED_WAKELOCK_TEST_SOURCES
  sharedwakelock_test.cpp
)

include_directories(
  ${CMAKE_SOURCE_DIR}/src/modules
)

add_executable(sharedwakelock_test ${SHARED_WAKELOCK_TEST_SOURCES})

target_link_libraries(
  sharedwakelock_test

  qtmirapplicationplugin
  PkgConfig::QTDBUSMOCK
  PkgConfig::QTDBUSTEST
  Qt::Test
  ${GTEST_BOTH_LIBRARIES}
  ${GMOCK_LIBRARIES}
)

add_test(SharedWakelock, sharedwakelock_test)
