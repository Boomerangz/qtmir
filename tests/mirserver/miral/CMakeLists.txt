set(
  MIRAL_TEST_SOURCES
  edid_test.cpp
)

add_executable(MirALTests ${MIRAL_TEST_SOURCES})

target_link_libraries(MirALTests
  qtmirserver
  ${GTEST_BOTH_LIBRARIES}
  ${GMOCK_LIBRARIES}
)

add_test(MirAL, MirALTests)
