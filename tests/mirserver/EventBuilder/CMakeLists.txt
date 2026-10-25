set(
  EVENT_BUILDER_TEST_SOURCES
  eventbuilder_test.cpp
)

add_executable(EventBuilderTest ${EVENT_BUILDER_TEST_SOURCES})

target_link_libraries(
  EventBuilderTest
  qtmirserver
  GTest::gmock_main
)

add_test(EventBuilder, EventBuilderTest)
