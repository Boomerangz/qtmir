set(
  APPLICATION_MANAGER_TEST_SOURCES
  application_manager_test.cpp
)

include_directories(
  ${CMAKE_SOURCE_DIR}/src/platforms/mirserver
  ${CMAKE_SOURCE_DIR}/src/modules
  ${CMAKE_SOURCE_DIR}/tests/framework
)

add_executable(applicationmanager_test ${APPLICATION_MANAGER_TEST_SOURCES})


target_link_libraries(
  applicationmanager_test

  Qt::Test

  qtmirapplicationplugin

  qtmir-test-framework-static

  ${GTEST_BOTH_LIBRARIES}
  ${GMOCK_LIBRARIES}
)

add_test(ApplicationManager applicationmanager_test)
