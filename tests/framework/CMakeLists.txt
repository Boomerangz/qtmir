set(QTMIR_TEST_PRIVATE_SRC
    fake_application_info.cpp
    fake_mirsurface.cpp
    fake_session.cpp
    mock_application_info.cpp
    mock_main_loop.cpp
    mock_mir_session.cpp
    mock_proc_info.cpp
    mock_prompt_session.cpp
    mock_prompt_session_manager.cpp
    mock_renderable.cpp
    mock_session.cpp
    mock_sessionmap.h
    mock_settings.cpp
    mock_shared_wakelock.cpp
    mock_surface.cpp
    mock_task_controller.cpp
    mock_persistent_surface_store.cpp
    fake_surface.h
    fake_displayconfigurationoutput.h
    qtmir_test.cpp
)

add_library(qtmir-test-framework-static STATIC
    ${QTMIR_TEST_PRIVATE_SRC}
)

target_include_directories(qtmir-test-framework-static PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(
    qtmir-test-framework-static

    qtmirapplicationplugin
    PkgConfig::MIRRENDERERGLDEV
    PkgConfig::MIRTEST
    GTest::gmock
)
