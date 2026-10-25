add_executable(EventBuilderTest eventbuilder_test.cpp)

target_link_libraries(EventBuilderTest PRIVATE
    qtmirserver
    GTest::gmock_main
)

add_test(NAME EventBuilder COMMAND EventBuilderTest)
