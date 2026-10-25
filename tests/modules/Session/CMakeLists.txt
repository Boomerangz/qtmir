set(
  SESSION_TEST_SOURCES
  taskcontroller_test.cpp
  session_test.cpp
)

include_directories(
  ${CMAKE_SOURCE_DIR}/src/modules
  ${CMAKE_SOURCE_DIR}/tests/framework
)

add_executable(session_test ${SESSION_TEST_SOURCES})


target_link_libraries(
  session_test

  qtmirapplicationplugin

  Qt::Test

  qtmir-test-framework-static

  ${GTEST_BOTH_LIBRARIES}
  ${GMOCK_LIBRARIES}
)

add_test(Session, session_test)
