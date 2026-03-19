add_library(H3MWriter STATIC
    "H3MWriter.cpp"
    "H3MWriter.h"
    "writeHeroSettings.cpp"
    "writeLossCondition.cpp"
    "writeMap.cpp"
    "writeMapAdditionalInfo.cpp"
    "writeMapBasicInfo.cpp"
    "writeObject.cpp"
    "writeObjectTemplate.cpp"
    "writePlayerSpecs.cpp"
    "writeQuest.cpp"
    "writeReward.cpp"
    "writeTile.cpp"
    "writeTimedEvent.cpp"
    "writeVictoryCondition.cpp"
    "writeh3m.cpp"
    "writeh3m.h"
)
add_library(h3mtxt::H3MWriter ALIAS H3MWriter)

# Add the parent of the repository to the list of additional include directories,
# so that headers can be included as, for example:
#     #include <h3mtxt/Map/Map.h>
target_include_directories(H3MWriter PUBLIC "${PROJECT_SOURCE_DIR}/..")

# Dependencies:
target_link_libraries(H3MWriter PUBLIC H3WriterBase)
target_link_libraries(H3MWriter PUBLIC Map)
# Thirdparty libraries:
target_link_libraries(H3MWriter PRIVATE zlib::zlibstatic)

# Set compiler options.
h3mtxt_add_common_compiler_options(H3MWriter)
