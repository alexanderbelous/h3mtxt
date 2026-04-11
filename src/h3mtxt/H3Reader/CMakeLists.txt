# H3Reader is a library that combines libraries for reading specific HoMM3 file formats.

add_subdirectory(H3ReaderBase)
add_subdirectory(H3MReader)
add_subdirectory(H3CReader)

add_library(H3Reader STATIC
    "parseh3.cpp"
    "parseh3.h"
)
add_library(h3mtxt::H3Reader ALIAS H3Reader)

target_include_directories(H3Reader PUBLIC "${H3MTXT_SRC_DIR}")

# Dependencies:
target_link_libraries(H3Reader PUBLIC h3mtxt::H3MReader)
target_link_libraries(H3Reader PUBLIC h3mtxt::H3CReader)
# Thirdparty libraries:
target_link_libraries(H3Reader PRIVATE ZLIB::ZLIBSTATIC)

# Set compiler options.
h3mtxt_add_common_compiler_options(H3Reader)
