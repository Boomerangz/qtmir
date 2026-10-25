set(
  SCREEN_TEST_SOURCES
  screen_test.cpp
)

add_executable(ScreenTest ${SCREEN_TEST_SOURCES})

target_include_directories(ScreenTest PRIVATE ${CMAKE_SOURCE_DIR}/tests/framework)

target_link_libraries(
  ScreenTest
  qtmirserver
  Qt::GuiPrivate

  ${GTEST_BOTH_LIBRARIES}
  ${GMOCK_LIBRARIES}

  Qt::Sensors
)

add_test(Screen, ScreenTest)
