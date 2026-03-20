add_library(H3CWriter STATIC
    "H3CWriter.cpp"
    "H3CWriter.h"
    "writeCampaignScenario.cpp"
    "writeStartingBonus.cpp"
    "writeStartingOptions.cpp"
    "writeh3c.cpp"
    "writeh3c.h"
)
add_library(h3mtxt::H3CWriter ALIAS H3CWriter)

# Add the parent of the repository to the list of additional include directories,
# so that headers can be included as, for example:
#     #include <h3mtxt/Map/Map.h>
target_include_directories(H3CWriter PUBLIC "${H3MTXT_SRC_DIR}")

# Dependencies:
target_link_libraries(H3CWriter PUBLIC Campaign)
target_link_libraries(H3CWriter PRIVATE H3MWriter)
target_link_libraries(H3CWriter PUBLIC H3WriterBase)
# Thirdparty libraries:
target_link_libraries(H3CWriter PRIVATE zlib::zlibstatic)

# Set compiler options.
h3mtxt_add_common_compiler_options(H3CWriter)
