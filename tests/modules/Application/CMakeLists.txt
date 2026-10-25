set(
  APPLICATION_TEST_SOURCES
  application_test.cpp
)

include_directories(
  ${CMAKE_SOURCE_DIR}/src/modules
  ${CMAKE_SOURCE_DIR}/tests/framework
)

add_executable(application_test ${APPLICATION_TEST_SOURCES})


target_link_libraries(
  application_test

  Qt::Test

  qtmirapplicationplugin

  qtmir-test-framework-static

  ${GTEST_BOTH_LIBRARIES}
  ${GMOCK_LIBRARIES}
)

add_test(Application, application_test)
