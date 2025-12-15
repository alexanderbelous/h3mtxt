add_library(H3JsonWriter STATIC
    "CommentBuilder.h"
    "getEnumString.cpp"
    "getEnumString.h"
    "getSecondarySkillLevelString.cpp"
    "getSecondarySkillLevelString.h"
    "H3JsonWriter.h"
    "Utils.cpp"
    "Utils.h"
    "writeCampaign.cpp"
    "writeCreatureStack.cpp"
    "writeH3cJson.cpp"
    "writeH3cJson.h"
    "writeH3mJson.cpp"
    "writeH3mJson.h"
    "writeHeroArtifacts.cpp"
    "writeLossCondition.cpp"
    "writeMap.cpp"
    "writeMapAdditionalInfo.cpp"
    "writeMapBasicInfo.cpp"
    "writeObject.cpp"
    "writeObjectProperties.h"
    "writeObjectTemplate.cpp"
    "writePlayerSpecs.cpp"
    "writePrimarySkills.cpp"
    "writeQuest.cpp"
    "writeQuestDetails.h"
    "writeResources.cpp"
    "writeReward.cpp"
    "writeRewardDetails.h"
    "writeSecondarySkill.cpp"
    "writeStartingBonus.cpp"
    "writeStartingBonusDetails.h"
    "writeStartingOptions.cpp"
    "writeStartingOptionsDetails.h"
    "writeTile.cpp"
    "writeTimedEvent.cpp"
    "writeVictoryCondition.cpp"
)
add_library(h3mtxt::H3JsonWriter ALIAS H3JsonWriter)

target_include_directories(H3JsonWriter PUBLIC "${PROJECT_SOURCE_DIR}/..")

# Dependencies:
target_link_libraries(H3JsonWriter PUBLIC h3mtxt::Campaign)
target_link_libraries(H3JsonWriter PRIVATE h3mtxt::JsonCommon)
target_link_libraries(H3JsonWriter PUBLIC h3mtxt::Map)
target_link_libraries(H3JsonWriter PUBLIC h3mtxt::Medea)

# Set compiler options.
h3mtxt_add_common_compiler_options(H3JsonWriter)
