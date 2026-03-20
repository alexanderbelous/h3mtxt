add_library(H3WriterBase STATIC
    "H3WriterBase.h"
    "H3WriterBase.cpp"
)
add_library(h3mtxt::H3WriterBase ALIAS H3WriterBase)

# Add the parent of the repository to the list of additional include directories,
# so that headers can be included as, for example:
#     #include <h3mtxt/Map/Map.h>
target_include_directories(H3WriterBase PUBLIC "${H3MTXT_SRC_DIR}")

# Dependencies:
target_link_libraries(H3WriterBase PUBLIC Map)

# Set compiler options.
h3mtxt_add_common_compiler_options(H3WriterBase)
