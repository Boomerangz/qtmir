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
  Qt::Sensors
  GTest::gmock_main
)

add_test(Screen, ScreenTest)
