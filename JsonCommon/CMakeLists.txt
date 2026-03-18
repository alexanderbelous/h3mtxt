# "JsonCommon" is a header-only library.
add_library(JsonCommon INTERFACE
    "getEnumFieldNames.h"
    "JsonCommonFwd.h"
    "FieldNamesH3M.h"
    "FieldNamesH3C.h"
)
add_library(h3mtxt::JsonCommon ALIAS JsonCommon)

target_include_directories(JsonCommon INTERFACE "${PROJECT_SOURCE_DIR}/..")

# "JsonCommon" library depends on "Map" and "Campaign" libraries.
target_link_libraries(JsonCommon INTERFACE h3mtxt::Campaign)
target_link_libraries(JsonCommon INTERFACE h3mtxt::Map)
