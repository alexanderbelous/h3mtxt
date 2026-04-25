add_subdirectory(thirdparty/Catch2 EXCLUDE_FROM_ALL)

set(H3MTXT_TESTS_HEADERS_LIST
    "Utils.h"
)

set(H3MTXT_TESTS_SOURCES_LIST
    "Campaign/CampaignScenario.cpp"
    "Campaign/CrossoverOptions.cpp"
    "Campaign/CutScene.cpp"
    "Campaign/StartingBonus.cpp"
    "Campaign/StartingOptions.cpp"
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
    "TeamsInfo.cpp"
    "Tile.cpp"
    "TimedEvent.cpp"
    "VictoryCondition.cpp"
)

add_executable(h3mtxt_tests ${H3MTXT_TESTS_HEADERS_LIST} ${H3MTXT_TESTS_SOURCES_LIST})

# Create source groups (e.g., filters in Visual Studio)
# for the source tree with root at CMAKE_CURRENT_SOURCE_DIR.
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} PREFIX "Header Files" FILES ${H3MTXT_TESTS_HEADERS_LIST})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} PREFIX "Source Files" FILES ${H3MTXT_TESTS_SOURCES_LIST})

# Dependencies:
target_link_libraries(h3mtxt_tests PRIVATE h3mtxt::Campaign)
target_link_libraries(h3mtxt_tests PRIVATE h3mtxt::H3CJsonReader)
target_link_libraries(h3mtxt_tests PRIVATE h3mtxt::H3CJsonWriter)
target_link_libraries(h3mtxt_tests PRIVATE h3mtxt::H3CReader)
target_link_libraries(h3mtxt_tests PRIVATE h3mtxt::H3CWriter)
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
