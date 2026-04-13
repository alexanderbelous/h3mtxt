add_library(H3SVGJsonWriter STATIC
    "getEnumString.cpp"
    "getEnumString.h"
    "H3SVGJsonWriter.h"
    "writeH3SvgJson.cpp"
    "writeH3SvgJson.h"
    "writeHero.cpp"
    "writeLossCondition.cpp"
    "writeObjectPropertiesTables.cpp"
    "writeQuest.cpp"
    "writeReward.cpp"
    "writeSavedGame.cpp"
    "writeVictoryCondition.cpp"
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
