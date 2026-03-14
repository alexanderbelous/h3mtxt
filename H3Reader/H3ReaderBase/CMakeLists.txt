add_library(H3ReaderBase STATIC
    "H3ReaderBase.h"
    "H3ReaderBase.cpp"
    "IntegerWidth.h"
)
add_library(h3mtxt::H3ReaderBase ALIAS H3ReaderBase)

target_include_directories(H3ReaderBase PUBLIC "${PROJECT_SOURCE_DIR}/..")

# Dependencies:
target_link_libraries(H3ReaderBase PUBLIC h3mtxt::Map)

# Set compiler options.
h3mtxt_add_common_compiler_options(H3ReaderBase)
