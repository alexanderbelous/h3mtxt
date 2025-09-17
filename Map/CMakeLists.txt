# All source files for "Map" library.
set(SOURCE_LIST
    # Constants
    "Constants/ArtifactType.h"
    "Constants/Constants.h"
    "Constants/CreatureType.h"
    "Constants/Disposition.h"
    "Constants/ExperienceLevels.h"
    "Constants/Formation.h"
    "Constants/Gender.h"
    "Constants/HeroPortrait.h"
    "Constants/HeroType.h"
    "Constants/LossConditionType.h"
    "Constants/MapDifficulty.h"
    "Constants/MapFormat.h"
    "Constants/ObjectClass.h"
    "Constants/ObjectGroup.h"
    "Constants/ObjectPropertiesType.h"
    "Constants/PlayerBehavior.h"
    "Constants/PlayerColor.h"
    "Constants/PrimarySkillType.h"
    "Constants/QuestType.h"
    "Constants/ResourceType.h"
    "Constants/RewardType.h"
    "Constants/RiverType.h"
    "Constants/RoadType.h"
    "Constants/ScholarRewardType.h"
    "Constants/SecondarySkillLevel.h"
    "Constants/SecondarySkillType.h"
    "Constants/SpellType.h"
    "Constants/TerrainType.h"
    "Constants/TileFlag.h"
    "Constants/TownBuildingType.h"
    "Constants/TownType.h"
    "Constants/VictoryConditionType.h"
    # Utils
    "Utils/BitSet.h"
    "Utils/EnumBitmask.h"
    "Utils/EnumSequence.h"
    "Utils/ReservedData.h"
    # etc
    "CreatureStack.h"
    "HeroArtifacts.h"
    "HeroSettings.h"
    "LossCondition.h"
    "Map.h"
    "MapAdditionalInfo.h"
    "MapBasicInfo.h"
    "MapFwd.h"
    "Object.h"
    "ObjectProperties.h"
    "ObjectPropertiesVariant.h"
    "ObjectTemplate.h"
    "PlayerSpecs.h"
    "PrimarySkills.h"
    "Quest.h"
    "Resources.h"
    "Reward.h"
    "SecondarySkill.h"
    "Tile.h"
    "TimedEvent.h"
    "VictoryCondition.h"
)

# "Map" is a header-only library.
add_library(Map INTERFACE ${SOURCE_LIST})
add_library(h3mtxt::Map ALIAS Map)

# Add the parent of the repository to the list of additional include directories,
# so that headers can be included as, for example:
#     #include <h3mtxt/Map/Map.h>
target_include_directories(Map INTERFACE "${PROJECT_SOURCE_DIR}/..")

# Create the source groups (e.g., filters in Visual Studio)
# for source tree with root at CMAKE_CURRENT_SOURCE_DIR.
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} PREFIX "Header Files" FILES ${SOURCE_LIST})
