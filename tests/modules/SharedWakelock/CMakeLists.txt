set(
  SHARED_WAKELOCK_TEST_SOURCES
  sharedwakelock_test.cpp
)

add_executable(sharedwakelock_test ${SHARED_WAKELOCK_TEST_SOURCES})

target_link_libraries(
  sharedwakelock_test

  qtmirapplicationplugin
  PkgConfig::QTDBUSMOCK
  PkgConfig::QTDBUSTEST
  Qt::Test
  GTest::gmock
)

add_test(SharedWakelock, sharedwakelock_test)
