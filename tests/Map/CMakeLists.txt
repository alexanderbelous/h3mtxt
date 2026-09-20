add_executable(h3mtxt_tests_Map
    "HeroArtifacts.cpp"
    "HeroSettings.cpp"
    "LossCondition.cpp"
    "Map.cpp"
    "MapAdditionalInfo.cpp"
    "MapBasicInfo.cpp"
    "Object.cpp"
    "ObjectProperties.cpp"
    "ObjectTemplate.cpp"
    "PlayerSpecs.cpp"
    "Quest.cpp"
    "ReservedData.cpp"
    "Reward.cpp"
    "SwitchStatement.cpp"
    "TeamsInfo.cpp"
    "TestUtils_H3M.h"
    "Tile.cpp"
    "TimedEvent.cpp"
    "VictoryCondition.cpp"
)

# Dependencies:
target_link_libraries(h3mtxt_tests_Map PRIVATE h3mtxt::H3MJsonReader)
target_link_libraries(h3mtxt_tests_Map PRIVATE h3mtxt::H3MJsonWriter)
target_link_libraries(h3mtxt_tests_Map PRIVATE h3mtxt::H3MReader)
target_link_libraries(h3mtxt_tests_Map PRIVATE h3mtxt::H3MWriter)
target_link_libraries(h3mtxt_tests_Map PRIVATE h3mtxt::Map)
target_link_libraries(h3mtxt_tests_Map PRIVATE h3mtxt::TestUtils)
# Thirdparty libraries:
target_link_libraries(h3mtxt_tests_Map PRIVATE Catch2::Catch2WithMain)

# Set compiler options.
h3mtxt_add_common_compiler_options(h3mtxt_tests_Map)

# Support for CTest
add_test(NAME h3mtxt_tests_Map COMMAND h3mtxt_tests_Map)
