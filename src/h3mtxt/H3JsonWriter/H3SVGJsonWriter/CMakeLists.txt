add_library(H3SVGJsonWriter STATIC
    "CampaignInfo.cpp"
    "EnumCommentGetter.cpp"
    "FixedLengthString.h"
    "H3SVGJsonWriter.h"
    "Hero.cpp"
    "LossCondition.cpp"
    "ObjectPropertiesTables.cpp"
    "Player.cpp"
    "Quest.cpp"
    "ReplayEvent.cpp"
    "Reward.cpp"
    "SavedGame.cpp"
    "ScenarioStartingInfo.cpp"
    "Town.cpp"
    "VictoryCondition.cpp"
    "writeH3SvgJson.cpp"
    "writeH3SvgJson.h"
)
add_library(h3mtxt::H3SVGJsonWriter ALIAS H3SVGJsonWriter)

target_include_directories(H3SVGJsonWriter PUBLIC "${H3MTXT_SRC_DIR}")

# Dependencies:
target_link_libraries(H3SVGJsonWriter PRIVATE h3mtxt::JsonCommon)
target_link_libraries(H3SVGJsonWriter PUBLIC h3mtxt::SavedGame)
target_link_libraries(H3SVGJsonWriter PRIVATE h3mtxt::H3MJsonWriter)
target_link_libraries(H3SVGJsonWriter PUBLIC h3mtxt::Medea)

# Set compiler options.
h3mtxt_add_common_compiler_options(H3SVGJsonWriter)
