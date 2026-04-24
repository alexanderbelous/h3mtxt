add_library(H3MJsonReader STATIC
    "H3MJsonReader.h"
    "readCoordinates.cpp"
    "readCreatureStack.cpp"
    "readH3mJson.cpp"
    "readH3mJson.h"
    "readHeroArtifacts.cpp"
    "readHeroSettings.cpp"
    "readLossCondition.cpp"
    "readMap.cpp"
    "readMapAdditionalInfo.cpp"
    "readMapBasicInfo.cpp"
    "readObjectProperties.cpp"
    "readObjectTemplate.cpp"
    "readPlayerSpecs.cpp"
    "readQuest.cpp"
    "readReward.cpp"
    "readSecondarySkill.cpp"
    "readTerrainsBitmask.cpp"
    "readTile.cpp"
    "readTimedEvent.cpp"
    "readVictoryCondition.cpp"
)
add_library(h3mtxt::H3MJsonReader ALIAS H3MJsonReader)

# Add the parent of the repository to the list of additional include directories,
# so that headers can be included as, for example:
#     #include <h3mtxt/Map/Map.h>
target_include_directories(H3MJsonReader PUBLIC "${H3MTXT_SRC_DIR}")

# Dependencies:
target_link_libraries(H3MJsonReader PRIVATE h3mtxt::JsonCommon)
target_link_libraries(H3MJsonReader PUBLIC h3mtxt::H3JsonReaderBase)
target_link_libraries(H3MJsonReader PUBLIC h3mtxt::Map)
# Thirdparty libraries:
target_link_libraries(H3MJsonReader PUBLIC jsoncpp::jsoncpp_static)

# Set compiler options.
h3mtxt_add_common_compiler_options(H3MJsonReader)
