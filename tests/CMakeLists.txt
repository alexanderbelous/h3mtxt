add_subdirectory(thirdparty/Catch2 EXCLUDE_FROM_ALL)

add_executable(h3mtxt_tests
    "parseJsonFromString.h"
    "parseJsonFromString.cpp"
    "HeroArtifacts.cpp"
    "HeroSettings.cpp"
    "LossCondition.cpp"
    "MapAdditionalInfo.cpp"
    "MapBasicInfo.cpp"
    "ObjectTemplate.cpp"
    "PlayerSpecs.cpp"
    "Quest.cpp"
    "Reward.cpp"
    "TeamsInfo.cpp"
    "Tile.cpp"
    "TimedEvent.cpp"
    "VictoryCondition.cpp"
)

# Dependencies:
target_link_libraries(h3mtxt_tests PRIVATE h3mtxt::H3MJsonReader)
target_link_libraries(h3mtxt_tests PRIVATE h3mtxt::H3MJsonWriter)
target_link_libraries(h3mtxt_tests PRIVATE h3mtxt::H3MReader)
target_link_libraries(h3mtxt_tests PRIVATE h3mtxt::H3MWriter)
target_link_libraries(h3mtxt_tests PRIVATE h3mtxt::Map)
# Thirdparty libraries:
target_link_libraries(h3mtxt_tests PRIVATE Catch2::Catch2WithMain)

# Set compiler options.
h3mtxt_add_common_compiler_options(h3mtxt_tests)

# Support for CTest
add_test(NAME h3mtxt_tests COMMAND h3mtxt_tests)
