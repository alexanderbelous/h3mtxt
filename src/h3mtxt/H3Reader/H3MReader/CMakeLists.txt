add_library(H3MReader STATIC
    "H3MReader.h"
    "parseh3m.cpp"
    "parseh3m.h"
    "readCoordinates.cpp"
    "readCreatureStack.cpp"
    "readHeroArtifacts.cpp"
    "readMap.cpp"
    "readMapAdditionalInfo.cpp"
    "readObject.cpp"
    "readPlayerSpecs.cpp"
    "readPrimarySkills.cpp"
    "readQuest.cpp"
    "readResources.cpp"
    "readReward.cpp"
    "readSecondarySkill.cpp"
    "readTimedEvent.cpp"
    "readVictoryCondition.cpp"
)
add_library(h3mtxt::H3MReader ALIAS H3MReader)

target_include_directories(H3MReader PUBLIC "${PROJECT_SOURCE_DIR}/..")

# Dependencies:
target_link_libraries(H3MReader PUBLIC h3mtxt::Map)
target_link_libraries(H3MReader PUBLIC h3mtxt::H3ReaderBase)
# Thirdparty libraries:
target_link_libraries(H3MReader PRIVATE zlib::zlibstatic)

# Set compiler options.
h3mtxt_add_common_compiler_options(H3MReader)
