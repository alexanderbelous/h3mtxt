add_library(H3CJsonReader STATIC
    "H3CJsonReader.h"
    "readCampaign.cpp"
    "readH3cJson.cpp"
    "readH3cJson.h"
    "readStartingBonus.cpp"
    "readStartingOptions.cpp"
)
add_library(h3mtxt::H3CJsonReader ALIAS H3CJsonReader)

# Add the parent of the repository to the list of additional include directories,
# so that headers can be included as, for example:
#     #include <h3mtxt/Map/Map.h>
target_include_directories(H3CJsonReader PUBLIC "${H3MTXT_SRC_DIR}")

# Dependencies:
target_link_libraries(H3CJsonReader PUBLIC h3mtxt::Campaign)
target_link_libraries(H3CJsonReader PUBLIC h3mtxt::H3JsonReaderBase)
target_link_libraries(H3CJsonReader PUBLIC h3mtxt::H3MJsonReader)
target_link_libraries(H3CJsonReader PRIVATE h3mtxt::JsonCommon)
# Thirdparty libraries:
target_link_libraries(H3CJsonReader PUBLIC jsoncpp::jsoncpp_static)

# Set compiler options.
h3mtxt_add_common_compiler_options(H3CJsonReader)
