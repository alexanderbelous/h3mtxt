add_library(H3JsonReaderBase STATIC
    "H3JsonReaderBase.cpp"
    "H3JsonReaderBase.h"
    "H3JsonReaderBaseFwd.h"
    "VariantJsonReader.h"
)
add_library(h3mtxt::H3JsonReaderBase ALIAS H3JsonReaderBase)

# Add the parent of the repository to the list of additional include directories,
# so that headers can be included as, for example:
#     #include <h3mtxt/Map/Map.h>
target_include_directories(H3JsonReaderBase PUBLIC "${PROJECT_SOURCE_DIR}/..")

# Dependencies:
target_link_libraries(H3JsonReaderBase PRIVATE h3mtxt::JsonCommon)
target_link_libraries(H3JsonReaderBase PUBLIC h3mtxt::Map)
# Thirdparty libraries:
target_link_libraries(H3JsonReaderBase PUBLIC jsoncpp::jsoncpp_static)

# Set compiler options.
h3mtxt_add_common_compiler_options(H3JsonReaderBase)
