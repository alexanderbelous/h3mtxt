# All source files for "Campaign" library.
set(SOURCE_LIST
    "Constants/CampaignFormat.h"
    "Constants/CampaignId.h"
    "Constants/CampaignMusic.h"
    "Constants/CampaignVideo.h"
    "Constants/CrossoverFeature.h"
    "Constants/RegionColor.h"
    "Constants/StartingBonusResourceType.h"
    "Constants/StartingBonusType.h"
    "Constants/StartingOptionsType.h"
    "Campaign.h"
    "CampaignFwd.h"
    "CampaignHeader.h"
    "CampaignScenario.h"
    "StartingBonus.h"
    "StartingOptions.h"
)

# "Campaign" is a header-only library.
add_library(Campaign INTERFACE ${SOURCE_LIST})
add_library(h3mtxt::Campaign ALIAS Campaign)

# Add the parent of the repository to the list of additional include directories,
# so that headers can be included as, for example:
#     #include <h3mtxt/Map/Map.h>
target_include_directories(Campaign INTERFACE "${PROJECT_SOURCE_DIR}/..")

# "Campaign" library depends on the "Map" library.
target_link_libraries(Campaign INTERFACE h3mtxt::Map)

# Create the source groups (e.g., filters in Visual Studio)
# for source tree with root at CMAKE_CURRENT_SOURCE_DIR.
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} PREFIX "Header Files" FILES ${SOURCE_LIST})
