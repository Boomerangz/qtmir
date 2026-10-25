set(
  GENERAL_TEST_SOURCES
  objectlistmodel_test.cpp
  timestamp_test.cpp
)

add_executable(general_test ${GENERAL_TEST_SOURCES})

target_include_directories(general_test PRIVATE ${CMAKE_SOURCE_DIR}/src/modules)

target_link_libraries(
  general_test

  qtmir-common
  Qt::Gui

  ${GTEST_BOTH_LIBRARIES}
  ${GMOCK_LIBRARIES}
)

add_test(General general_test)
