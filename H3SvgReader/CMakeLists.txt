add_library(H3SvgReader STATIC
    "H3ReaderBase.cpp"
    "H3ReaderBase.h"
    "H3SvgReader.h"
    "parseh3svg.h"
    "parseh3svg.cpp"
    "readEventBaseSvg.cpp"
    "readMapBasicInfo.cpp"
    "readObjectSvg.cpp"
    "readObjectTemplateSvg.cpp"
    "readPlayerSpecsSvg.cpp"
    "readSavedGame.cpp"
    "readTileSvg.cpp"
)
add_library(h3mtxt::H3SvgReader ALIAS H3SvgReader)

target_include_directories(H3SvgReader PUBLIC "${PROJECT_SOURCE_DIR}/..")

# Dependencies:
target_link_libraries(H3SvgReader PUBLIC h3mtxt::SavedGame)
target_link_libraries(H3SvgReader PUBLIC h3mtxt::H3Reader)
# Thirdparty libraries:
target_link_libraries(H3SvgReader PRIVATE zlib::zlibstatic)

# Set compiler options.
h3mtxt_add_common_compiler_options(H3SvgReader)
