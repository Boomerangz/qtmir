set(
  APPLICATION_TEST_SOURCES
  application_test.cpp
)

add_executable(application_test ${APPLICATION_TEST_SOURCES})


target_link_libraries(
  application_test

  Qt::Test

  qtmirapplicationplugin

  qtmir-test-framework-static

  GTest::gmock_main
)

add_test(Application, application_test)
