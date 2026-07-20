add_library(H3SVGWriter STATIC
    "H3SVGWriter.cpp"
    "H3SVGWriter.h"
    "LossCondition.cpp"
    "MapBasicInfo.cpp"
    "PlayerSpecs.cpp"
    "SavedGame.cpp"
    "Utils.h"
    "VictoryCondition.cpp"
    "writeh3svg.cpp"
    "writeh3svg.h"
)
add_library(h3mtxt::H3SVGWriter ALIAS H3SVGWriter)

# Add the parent of the repository to the list of additional include directories,
# so that headers can be included as, for example:
#     #include <h3mtxt/Map/Map.h>
target_include_directories(H3SVGWriter PUBLIC "${H3MTXT_SRC_DIR}")

# Dependencies:
target_link_libraries(H3SVGWriter PUBLIC h3mtxt::Map)
target_link_libraries(H3SVGReader PUBLIC h3mtxt::SavedGame)
target_link_libraries(H3SVGWriter PUBLIC h3mtxt::H3WriterBase)
target_link_libraries(H3SVGWriter PUBLIC h3mtxt::H3MWriter)

# Thirdparty libraries:
target_link_libraries(H3SVGWriter PRIVATE ZLIB::ZLIBSTATIC)

# Set compiler options.
h3mtxt_add_common_compiler_options(H3SVGWriter)
