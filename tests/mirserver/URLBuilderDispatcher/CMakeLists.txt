set(
  URLBUILDERDISPATCHER_TEST_RESOURCES
  urlbuilderdispatcher_test.cpp
)

add_executable(URLBuilderDispatcherTest ${URLBUILDERDISPATCHER_TEST_RESOURCES})

target_link_libraries(
  URLBuilderDispatcherTest
  qtmirserver
  Qt::GuiPrivate
  GTest::gmock_main
)

add_test(URLBuilderDispatcher, URLBuilderDispatcherTest)
