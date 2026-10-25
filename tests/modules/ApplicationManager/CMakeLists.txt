set(
  APPLICATION_MANAGER_TEST_SOURCES
  application_manager_test.cpp
)

add_executable(applicationmanager_test ${APPLICATION_MANAGER_TEST_SOURCES})


target_link_libraries(
  applicationmanager_test

  Qt::Test

  qtmirapplicationplugin

  qtmir-test-framework-static

  GTest::gmock_main
)

add_test(ApplicationManager applicationmanager_test)
