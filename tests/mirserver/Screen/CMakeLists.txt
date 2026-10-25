add_executable(ScreenTest screen_test.cpp)

target_include_directories(ScreenTest PRIVATE ${CMAKE_SOURCE_DIR}/tests/framework)

target_link_libraries(ScreenTest PRIVATE
    qtmirserver
    Qt::GuiPrivate
    Qt::Sensors
    GTest::gmock_main
)

add_test(NAME Screen COMMAND ScreenTest)
