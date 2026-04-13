# Library for constructing minimap images for HoMM3 maps.
add_library(h3mtxt_Minimap STATIC
    "include/Minimap/Image.h"
    "include/Minimap/Minimap.h"
    "src/Image.cpp"
    "src/Minimap.cpp"
    "src/thirdparty/lodepng/lodepng.h"
    "src/thirdparty/lodepng/lodepng.cpp"
)
add_library(h3mtxt::Minimap ALIAS h3mtxt_Minimap)
target_include_directories(Map INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/include")
# Dependencies:
target_link_libraries(h3mtxt_Minimap PUBLIC h3mtxt::Map)
# Set compiler options.
h3mtxt_add_common_compiler_options(h3mtxt_Minimap)
