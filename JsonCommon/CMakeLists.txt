# "JsonCommon" is a header-only library.
add_library(JsonCommon INTERFACE
    "FieldName.h"
    "FieldNamesSvg.h"
    "JsonCommonFwd.h"
)
add_library(h3mtxt::JsonCommon ALIAS JsonCommon)

target_include_directories(JsonCommon INTERFACE "${PROJECT_SOURCE_DIR}/..")

target_link_libraries(JsonCommon INTERFACE h3mtxt::Campaign)
target_link_libraries(JsonCommon INTERFACE h3mtxt::Map)
target_link_libraries(JsonCommon INTERFACE h3mtxt::SavedGame)
