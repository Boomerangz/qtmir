add_executable(application_test application_test.cpp)

target_link_libraries(application_test PRIVATE
    qtmirapplicationplugin
    qtmir-test-framework-static
    Qt::Test
    GTest::gmock_main
)

add_test(NAME Application COMMAND application_test)
