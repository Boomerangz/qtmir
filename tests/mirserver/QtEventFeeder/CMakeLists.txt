add_executable(QtEventFeederTest
    qteventfeeder_test.cpp
    mock_qtwindowsystem.h
)

target_link_libraries(QtEventFeederTest PRIVATE
    qtmirserver
    Qt::GuiPrivate
    GTest::gmock_main
)

add_test(NAME QtEventFeeder COMMAND QtEventFeederTest)
