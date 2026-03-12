# "JsonCommon" is a header-only library.
add_library(JsonCommon INTERFACE
    "getEnumFieldNames.h"
    "JsonCommonFwd.h"
    "FieldName.h"
    "FieldNamesH3C.h"
    "FieldNamesH3SVG.h"
)
add_library(h3mtxt::JsonCommon ALIAS JsonCommon)

target_include_directories(JsonCommon INTERFACE "${PROJECT_SOURCE_DIR}/..")

target_link_libraries(JsonCommon INTERFACE h3mtxt::Campaign)
target_link_libraries(JsonCommon INTERFACE h3mtxt::Map)
target_link_libraries(JsonCommon INTERFACE h3mtxt::SavedGame)
