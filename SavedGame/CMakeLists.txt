# All source files for "SavedGame" library.
set(SOURCE_LIST
    "Constants/ArtifactType32.h"
    "Constants/Constants.h"
    "Constants/KeymastersTentType.h"
    "Constants/ObjectPropertiesType.h"
    "Constants/PlayerControlType.h"
    "Constants/PlayerPersonality.h"
    "Constants/PlayerStartingBonusType.h"
    "Constants/PlayerTurnDurationType.h"
    "Constants/SeerName.h"
    "Constants/TownBuildingTypeH3SVG.h"
    "Constants/TownType32.h"
    "ArtifactMerchants.h"
    "EventBase.h"
    "Hero.h"
    "ObjectPropertiesTables.h"
    "ObjectProperties.h"
    "Object.h"
    "ObjectTemplate.h"
    "Player.h"
    "PlayerSpecs.h"
    "Quest.h"
    "Reward.h"
    "SavedGame.h"
    "SavedGameFwd.h"
    "ScenarioStartingInfo.h"
    "Tile.h"
    "TileVisibility.h"
    "Town.h"
    "Troops.h"
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
