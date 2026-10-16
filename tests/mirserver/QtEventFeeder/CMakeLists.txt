set(
  EVENT_FEEDER_TEST_SOURCES
  qteventfeeder_test.cpp
  mock_qtwindowsystem.h
  ${CMAKE_SOURCE_DIR}/src/common/debughelpers.cpp
)

include_directories(
  ${CMAKE_SOURCE_DIR}/src/platforms/mirserver
  ${CMAKE_SOURCE_DIR}/src/common
)

include_directories(
  SYSTEM
  ${MIRSERVER_INCLUDE_DIRS}
  ${MIRAL_INCLUDE_DIRS}
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
