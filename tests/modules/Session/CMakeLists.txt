add_executable(session_test
    session_test.cpp
    taskcontroller_test.cpp
)

target_link_libraries(session_test PRIVATE
    qtmirapplicationplugin
    qtmir-test-framework-static
    Qt::Test
    GTest::gmock_main
)

add_test(NAME Session COMMAND session_test)
