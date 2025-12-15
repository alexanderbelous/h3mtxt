add_library(H3JsonReader STATIC
    "H3JsonReader.h"
    "readCampaign.cpp"
    "readCreatureStack.cpp"
    "readH3cJson.cpp"
    "readH3cJson.h"
    "readH3Json.cpp"
    "readH3Json.h"
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
    "readPrimarySkills.cpp"
    "readQuest.cpp"
    "readResources.cpp"
    "readReward.cpp"
    "readSecondarySkill.cpp"
    "readStartingBonus.cpp"
    "readStartingOptions.cpp"
    "readTerrainsBitmask.cpp"
    "readTile.cpp"
    "readTimedEvent.cpp"
    "readVictoryCondition.cpp"
    "Utils.cpp"
    "Utils.h"
    "VariantJsonReader.h"
)
add_library(h3mtxt::H3JsonReader ALIAS H3JsonReader)

# Add the parent of the repository to the list of additional include directories,
# so that headers can be included as, for example:
#     #include <h3mtxt/Map/Map.h>
target_include_directories(H3JsonReader PUBLIC "${PROJECT_SOURCE_DIR}/..")

# Dependencies:
target_link_libraries(H3JsonReader PUBLIC h3mtxt::Campaign)
target_link_libraries(H3JsonReader PRIVATE h3mtxt::JsonCommon)
target_link_libraries(H3JsonReader PUBLIC h3mtxt::Map)
# Thirdparty libraries:
target_link_libraries(H3JsonReader PUBLIC jsoncpp::jsoncpp_static)

# Set compiler options.
h3mtxt_add_common_compiler_options(H3JsonReader)
