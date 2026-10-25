set(
  MIRAL_TEST_SOURCES
  edid_test.cpp
)

add_executable(MirALTests ${MIRAL_TEST_SOURCES})

target_link_libraries(MirALTests
  qtmirserver
  GTest::gmock_main
)

add_test(MirAL, MirALTests)
