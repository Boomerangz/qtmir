add_executable(URLBuilderDispatcherTest urlbuilderdispatcher_test.cpp)

target_link_libraries(URLBuilderDispatcherTest PRIVATE
    qtmirserver
    Qt::GuiPrivate
    GTest::gmock_main
)

add_test(NAME URLBuilderDispatcher COMMAND URLBuilderDispatcherTest)
