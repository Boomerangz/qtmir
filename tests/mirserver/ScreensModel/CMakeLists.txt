add_executable(ScreensModelTest
    screensmodel_test.cpp
    stub_screen.h
    testable_screensmodel.h
)

target_link_libraries(ScreensModelTest PRIVATE
    qtmirserver
    qtmir-test-framework-static
    PkgConfig::MIRRENDERERGLDEV
    PkgConfig::MIRTEST
    Qt::GuiPrivate
    GTest::gmock_main
)

add_test(NAME ScreensModel COMMAND ScreensModelTest)
