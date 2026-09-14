add_library(H3SVGJsonReader STATIC
    "H3SVGJsonReader.h"
    "Hero.cpp"
    "LossCondition.cpp"
    "ObjectPropertiesTable.cpp"
    "Player.cpp"
    "readH3SVGJson.cpp"
    "readH3SVGJson.h"
    "ReplayEvent.cpp"
    "SavedGame.cpp"
    "ScenarioStartingInfo.cpp"
    "Town.cpp"
    "VictoryCondition.cpp"
)
add_library(h3mtxt::H3SVGJsonReader ALIAS H3SVGJsonReader)

# Add the parent of the repository to the list of additional include directories,
# so that headers can be included as, for example:
#     #include <h3mtxt/Map/Map.h>
target_include_directories(H3SVGJsonReader PUBLIC "${H3MTXT_SRC_DIR}")

# Dependencies:
target_link_libraries(H3SVGJsonReader PRIVATE h3mtxt::JsonCommon)
target_link_libraries(H3SVGJsonReader PUBLIC h3mtxt::H3JsonReaderBase)
target_link_libraries(H3SVGJsonReader PUBLIC h3mtxt::SavedGame)
# Thirdparty libraries:
target_link_libraries(H3SVGJsonReader PUBLIC jsoncpp::jsoncpp_static)

# Set compiler options.
h3mtxt_add_common_compiler_options(H3SVGJsonReader)
