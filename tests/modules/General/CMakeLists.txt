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
  GTest::gmock_main
)

add_test(NAME General COMMAND general_test)
