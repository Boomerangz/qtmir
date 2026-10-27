add_executable(MirALTests edid_test.cpp)

target_link_libraries(MirALTests PRIVATE
    qtmirserver
    GTest::gmock_main
)

add_test(NAME MirAL COMMAND MirALTests)
