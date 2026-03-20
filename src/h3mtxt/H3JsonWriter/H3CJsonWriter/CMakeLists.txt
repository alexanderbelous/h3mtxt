add_library(H3CJsonWriter STATIC
    "getEnumString.cpp"
    "getEnumString.h"
    "H3CJsonWriter.h"
    "writeCampaign.cpp"
    "writeH3cJson.cpp"
    "writeH3cJson.h"
    "writeStartingBonus.cpp"
    "writeStartingOptions.cpp"
)
add_library(h3mtxt::H3CJsonWriter ALIAS H3CJsonWriter)

target_include_directories(H3CJsonWriter PUBLIC "${H3MTXT_SRC_DIR}")

# Dependencies:
target_link_libraries(H3CJsonWriter PUBLIC h3mtxt::Campaign)
target_link_libraries(H3CJsonWriter PUBLIC h3mtxt::H3MJsonWriter)
target_link_libraries(H3CJsonWriter PRIVATE h3mtxt::JsonCommon)
target_link_libraries(H3CJsonWriter PUBLIC h3mtxt::Medea)

# Set compiler options.
h3mtxt_add_common_compiler_options(H3CJsonWriter)
