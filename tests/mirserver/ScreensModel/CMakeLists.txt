set(
  SCREENCONTROLLER_TEST_SOURCES
  screensmodel_test.cpp
  # to be moc-ed
  stub_screen.h
  testable_screensmodel.h
)

include_directories(
  ${CMAKE_SOURCE_DIR}/tests/framework
)

add_executable(ScreensModelTest ${SCREENCONTROLLER_TEST_SOURCES})

target_link_libraries(
  ScreensModelTest
  qtmirserver
  Qt::GuiPrivate

  qtmir-test-framework-static
  PkgConfig::MIRRENDERERGLDEV
  PkgConfig::MIRTEST
  ${GTEST_BOTH_LIBRARIES}
  ${GMOCK_LIBRARIES}
)

add_test(ScreensModel, ScreensModelTest)
