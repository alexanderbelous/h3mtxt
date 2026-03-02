add_library(H3SvgJsonWriter STATIC
    "getEnumString.cpp"
    "getEnumString.h"
    "H3SvgJsonWriter.h"
    "writeEnumIndexedArray.h"
    "writeH3SvgJson.cpp"
    "writeH3SvgJson.h"
    "writeSavedGame.cpp"
)
add_library(h3mtxt::H3SvgJsonWriter ALIAS H3SvgJsonWriter)

target_include_directories(H3SvgJsonWriter PUBLIC "${PROJECT_SOURCE_DIR}/..")

# Dependencies:
target_link_libraries(H3SvgJsonWriter PRIVATE h3mtxt::JsonCommon)
target_link_libraries(H3SvgJsonWriter PUBLIC h3mtxt::SavedGame)
target_link_libraries(H3SvgJsonWriter PUBLIC h3mtxt::H3JsonWriter)
target_link_libraries(H3SvgJsonWriter PUBLIC h3mtxt::Medea)

# Set compiler options.
h3mtxt_add_common_compiler_options(H3SvgJsonWriter)
