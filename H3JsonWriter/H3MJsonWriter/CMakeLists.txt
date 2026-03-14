add_library(H3MJsonWriter STATIC
    "CommentBuilder.h"
    "getEnumString.cpp"
    "getEnumString.h"
    "getSecondarySkillLevelString.cpp"
    "getSecondarySkillLevelString.h"
    "H3MJsonWriter.h"
    "Utils.cpp"
    "Utils.h"
    "writeCoordinates.cpp"
    "writeCreatureStack.cpp"
    "writeH3mJson.cpp"
    "writeH3mJson.h"
    "writeHeroArtifacts.cpp"
    "writeLossCondition.cpp"
    "writeMap.cpp"
    "writeMapAdditionalInfo.cpp"
    "writeMapBasicInfo.cpp"
    "writeObject.cpp"
    "writeObjectTemplate.cpp"
    "writePlayerSpecs.cpp"
    "writePrimarySkills.cpp"
    "writeQuest.cpp"
    "writeReward.cpp"
    "writeSecondarySkill.cpp"
    "writeTile.cpp"
    "writeTimedEvent.cpp"
    "writeVictoryCondition.cpp"
)
add_library(h3mtxt::H3MJsonWriter ALIAS H3MJsonWriter)

target_include_directories(H3MJsonWriter PUBLIC "${PROJECT_SOURCE_DIR}/..")

# Dependencies:
target_link_libraries(H3MJsonWriter PRIVATE h3mtxt::JsonCommon)
target_link_libraries(H3MJsonWriter PUBLIC h3mtxt::Map)
target_link_libraries(H3MJsonWriter PUBLIC h3mtxt::Medea)

# Set compiler options.
h3mtxt_add_common_compiler_options(H3MJsonWriter)
