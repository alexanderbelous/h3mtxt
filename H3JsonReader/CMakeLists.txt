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

# For Visual Studio: Use Unicode Character Set.
target_compile_definitions(H3JsonReader PRIVATE _UNICODE)

# Enable Whole Program Optimization in Release if it's supported.
include(CheckIPOSupported)
check_ipo_supported(RESULT IPO_SUPPORTED)
if(IPO_SUPPORTED)
  set_target_properties(H3JsonReader PROPERTIES
    INTERPROCEDURAL_OPTIMIZATION TRUE
    INTERPROCEDURAL_OPTIMIZATION_DEBUG FALSE
    INTERPROCEDURAL_OPTIMIZATION_RELEASE TRUE
    INTERPROCEDURAL_OPTIMIZATION_RELWITHDEBINFO TRUE
    INTERPROCEDURAL_OPTIMIZATION_MINSIZEREL TRUE
  )
endif()

# Set warning level
if(MSVC)
  target_compile_options(H3JsonReader PRIVATE /W4)
else()
  target_compile_options(H3JsonReader PRIVATE -Wall -Wextra -Wpedantic)
endif()
