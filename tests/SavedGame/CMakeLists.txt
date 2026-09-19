add_executable(h3mtxt_tests_SavedGame
    "CoordinatesPacked.cpp"
    "FixedLengthString.cpp"
    "MapBasicInfo.cpp"
    "SavedGame.cpp"
    "TestingUtils_H3SVG.h"
    "Town.cpp"
)

# Dependencies:
target_link_libraries(h3mtxt_tests_SavedGame PRIVATE h3mtxt::H3SVGReader)
target_link_libraries(h3mtxt_tests_SavedGame PRIVATE h3mtxt::H3SVGWriter)
target_link_libraries(h3mtxt_tests_SavedGame PRIVATE h3mtxt::H3SVGJsonReader)
target_link_libraries(h3mtxt_tests_SavedGame PRIVATE h3mtxt::H3SVGJsonWriter)
target_link_libraries(h3mtxt_tests_SavedGame PRIVATE h3mtxt::SavedGame)
target_link_libraries(h3mtxt_tests_Map PRIVATE h3mtxt::TestUtils)
# Thirdparty libraries:
target_link_libraries(h3mtxt_tests_SavedGame PRIVATE Catch2::Catch2WithMain)

# Set compiler options.
h3mtxt_add_common_compiler_options(h3mtxt_tests_SavedGame)

# Support for CTest
add_test(NAME h3mtxt_tests_SavedGame COMMAND h3mtxt_tests_SavedGame)
