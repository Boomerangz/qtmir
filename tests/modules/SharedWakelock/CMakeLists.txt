add_executable(sharedwakelock_test sharedwakelock_test.cpp)

target_link_libraries(sharedwakelock_test PRIVATE
    qtmirapplicationplugin
    PkgConfig::QTDBUSMOCK
    PkgConfig::QTDBUSTEST
    Qt::Test
    GTest::gmock
)

add_test(NAME SharedWakelock COMMAND sharedwakelock_test)
