# "JsonCommon" is a header-only library that consists of a single file.
add_library(JsonCommon INTERFACE "FieldName.h")
add_library(h3mtxt::JsonCommon ALIAS JsonCommon)

target_include_directories(JsonCommon INTERFACE "${PROJECT_SOURCE_DIR}/..")

# "JsonCommon" library depends on "Map" and "Campaign" libraries.
target_link_libraries(JsonCommon INTERFACE h3mtxt::Campaign)
target_link_libraries(JsonCommon INTERFACE h3mtxt::Map)
