# All source files for "SavedGame" library.
set(SOURCE_LIST
    "Constants/ArtifactType32.h"
    "Constants/Constants.h"
    "Constants/ObjectPropertiesSvgType.h"
    "Constants/PlayerControlType.h"
    "Constants/PlayerStartingBonusType.h"
    "Constants/PlayerTurnDurationType.h"
    "Constants/TownType32.h"
    "EnumIndexedArray.h"
    "EventBaseSvg.h"
    "HeroSvg.h"
    "ObjectPropertiesTables.h"
    "ObjectPropertiesSvg.h"
    "ObjectSvg.h"
    "ObjectTemplateSvg.h"
    "PlayerSpecsSvg.h"
    "QuestSvg.h"
    "RewardSvg.h"
    "SavedGame.h"
    "SavedGameFwd.h"
    "ScenarioStartingInfo.h"
    "TileSvg.h"
    "TownSvg.h"
    "TroopsSvg.h"
)

# "SavedGame" is a header-only library.
add_library(SavedGame INTERFACE ${SOURCE_LIST})
add_library(h3mtxt::SavedGame ALIAS SavedGame)

# Add the parent of the repository to the list of additional include directories,
# so that headers can be included as, for example:
#     #include <h3mtxt/Map/Map.h>
target_include_directories(SavedGame INTERFACE "${PROJECT_SOURCE_DIR}/..")

# "SavedGame" library depends on the "Map" library.
target_link_libraries(SavedGame INTERFACE h3mtxt::Map)

# Create the source groups (e.g., filters in Visual Studio)
# for source tree with root at CMAKE_CURRENT_SOURCE_DIR.
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} PREFIX "Header Files" FILES ${SOURCE_LIST})
