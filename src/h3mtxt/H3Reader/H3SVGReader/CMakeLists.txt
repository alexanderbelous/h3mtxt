add_library(H3SVGReader STATIC
    "H3SVGReader.cpp"
    "H3SVGReader.h"
    "parseh3svg.h"
    "parseh3svg.cpp"
    "readEventBase.cpp"
    "readHero.cpp"
    "readLossCondition.cpp"
    "readMapBasicInfo.cpp"
    "readObjectPropertiesTables.cpp"
    "readObject.cpp"
    "readObjectTemplate.cpp"
    "readPlayerSpecs.cpp"
    "readQuest.cpp"
    "readReward.cpp"
    "readSavedGame.cpp"
    "readTile.cpp"
    "zstr_patch.cpp"
    "zstr_patch.h"
)
add_library(h3mtxt::H3SVGReader ALIAS H3SVGReader)

target_include_directories(H3SVGReader PUBLIC "${PROJECT_SOURCE_DIR}/..")

# Dependencies:
target_link_libraries(H3SVGReader PUBLIC h3mtxt::SavedGame)
target_link_libraries(H3SVGReader PUBLIC h3mtxt::H3MReader)
target_link_libraries(H3SVGReader PUBLIC h3mtxt::H3ReaderBase)
# Thirdparty libraries:
target_link_libraries(H3SVGReader PRIVATE zlib::zlibstatic)

# Set compiler options.
h3mtxt_add_common_compiler_options(H3SVGReader)
