set(
  EVENT_FEEDER_TEST_SOURCES
  qteventfeeder_test.cpp
  mock_qtwindowsystem.h
)

add_executable(QtEventFeederTest ${EVENT_FEEDER_TEST_SOURCES})

target_link_libraries(
  QtEventFeederTest
  qtmirserver
  Qt::GuiPrivate
  ${GTEST_BOTH_LIBRARIES}
  ${GMOCK_LIBRARIES}
)

add_test(QtEventFeeder, QtEventFeederTest)
