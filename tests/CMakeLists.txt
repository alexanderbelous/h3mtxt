add_subdirectory(thirdparty/Catch2 EXCLUDE_FROM_ALL)

add_executable(h3mtxt_tests
    "parseJsonFromString.h"
    "parseJsonFromString.cpp"
    "LossCondition.cpp"
    "MapBasicInfo.cpp"
    "ObjectTemplate.cpp"
    "PlayerSpecs.cpp"
    "Quest.cpp"
    "Reward.cpp"
    "Tile.cpp"
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
