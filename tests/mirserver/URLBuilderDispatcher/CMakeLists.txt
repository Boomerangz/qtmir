set(
  URLBUILDERDISPATCHER_TEST_RESOURCES
  urlbuilderdispatcher_test.cpp
)

include_directories(
  ${CMAKE_SOURCE_DIR}/tests/framework
  ${CMAKE_SOURCE_DIR}/src/platforms/mirserver
  ${CMAKE_SOURCE_DIR}/src/common
)

include_directories(
  SYSTEM
  ${MIRSERVER_INCLUDE_DIRS}
)

add_executable(URLBuilderDispatcherTest ${URLBUILDERDISPATCHER_TEST_RESOURCES})

target_link_libraries(
  URLBuilderDispatcherTest
  qtmirserver
  Qt::GuiPrivate

  ${GTEST_BOTH_LIBRARIES}
  ${GMOCK_LIBRARIES}
)

add_test(URLBuilderDispatcher, URLBuilderDispatcherTest)
