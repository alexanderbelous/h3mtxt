add_library(H3CReader STATIC
    "H3CReader.h"
    "parseh3c.cpp"
    "parseh3c.h"
    "readCampaignHeader.cpp"
    "readCampaignScenario.cpp"
    "readStartingBonus.cpp"
    "readStartingOptions.cpp"
)
add_library(h3mtxt::H3CReader ALIAS H3CReader)

target_include_directories(H3CReader PUBLIC "${H3MTXT_SRC_DIR}")

# Dependencies:
target_link_libraries(H3CReader PUBLIC h3mtxt::Campaign)
target_link_libraries(H3CReader PUBLIC h3mtxt::H3ReaderBase)
target_link_libraries(H3CReader PRIVATE h3mtxt::H3MReader)
target_link_libraries(H3CReader PUBLIC h3mtxt::Map)
# Thirdparty libraries:
target_link_libraries(H3CReader PRIVATE ZLIB::ZLIBSTATIC)

# Set compiler options.
h3mtxt_add_common_compiler_options(H3CReader)
