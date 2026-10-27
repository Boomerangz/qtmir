add_executable(applicationmanager_test application_manager_test.cpp)

target_link_libraries(applicationmanager_test PRIVATE
    qtmirapplicationplugin
    qtmir-test-framework-static
    Qt::Test
    GTest::gmock_main
)

add_test(NAME ApplicationManager COMMAND applicationmanager_test)
