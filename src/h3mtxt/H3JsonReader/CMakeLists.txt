add_subdirectory(H3JsonReaderBase)
add_subdirectory(H3MJsonReader)
add_subdirectory(H3CJsonReader)

add_library(H3JsonReader STATIC
    "readH3Json.cpp"
    "readH3Json.h"
)
add_library(h3mtxt::H3JsonReader ALIAS H3JsonReader)

# Add the parent of the repository to the list of additional include directories,
# so that headers can be included as, for example:
#     #include <h3mtxt/Map/Map.h>
target_include_directories(H3JsonReader PUBLIC "${H3MTXT_SRC_DIR}")

# Dependencies:
target_link_libraries(H3JsonReader PUBLIC h3mtxt::Campaign)
target_link_libraries(H3JsonReader PUBLIC h3mtxt::H3MJsonReader)
target_link_libraries(H3JsonReader PUBLIC h3mtxt::H3CJsonReader)
target_link_libraries(H3JsonReader PRIVATE h3mtxt::JsonCommon)
target_link_libraries(H3JsonReader PUBLIC h3mtxt::Map)
# Thirdparty libraries:
target_link_libraries(H3JsonReader PUBLIC jsoncpp::jsoncpp_static)

# Set compiler options.
h3mtxt_add_common_compiler_options(H3JsonReader)
