add_executable(h3mtxt_SavedGame_tests
    "CoordinatesPacked.cpp"
    "FixedLengthString.cpp"
    "MapBasicInfo.cpp"
    "Town.cpp"
)

# Dependencies:
target_link_libraries(h3mtxt_SavedGame_tests PRIVATE h3mtxt::H3SVGReader)
target_link_libraries(h3mtxt_SavedGame_tests PRIVATE h3mtxt::H3SVGWriter)
target_link_libraries(h3mtxt_SavedGame_tests PRIVATE h3mtxt::H3SVGJsonReader)
target_link_libraries(h3mtxt_SavedGame_tests PRIVATE h3mtxt::H3SVGJsonWriter)
target_link_libraries(h3mtxt_SavedGame_tests PRIVATE h3mtxt::SavedGame)
# Thirdparty libraries:
target_link_libraries(h3mtxt_SavedGame_tests PRIVATE Catch2::Catch2WithMain)

# Set compiler options.
h3mtxt_add_common_compiler_options(h3mtxt_SavedGame_tests)

# Support for CTest
add_test(NAME h3mtxt_SavedGame_tests COMMAND h3mtxt_SavedGame_tests)
