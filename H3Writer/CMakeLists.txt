add_library(H3Writer STATIC
    "H3Writer.h"
    "Utils.cpp"
    "Utils.h"
    "writeCampaignScenario.cpp"
    "writeCreatureStack.cpp"
    "writeh3c.cpp"
    "writeh3c.h"
    "writeh3m.cpp"
    "writeh3m.h"
    "writeHeroArtifacts.cpp"
    "writeHeroSettings.cpp"
    "writeLossCondition.cpp"
    "writeMap.cpp"
    "writeMapAdditionalInfo.cpp"
    "writeMapBasicInfo.cpp"
    "writeObject.cpp"
    "writeObjectTemplate.cpp"
    "writePlayerSpecs.cpp"
    "writePrimarySkills.cpp"
    "writeQuest.cpp"
    "writeResources.cpp"
    "writeReward.cpp"
    "writeSecondarySkill.cpp"
    "writeStartingBonus.cpp"
    "writeStartingOptions.cpp"
    "writeTile.cpp"
    "writeTimedEvent.cpp"
    "writeVictoryCondition.cpp"
)
add_library(h3mtxt::H3Writer ALIAS H3Writer)

# Add the parent of the repository to the list of additional include directories,
# so that headers can be included as, for example:
#     #include <h3mtxt/Map/Map.h>
target_include_directories(H3Writer PUBLIC "${PROJECT_SOURCE_DIR}/..")

# Dependencies:
target_link_libraries(H3Writer PUBLIC Campaign)
target_link_libraries(H3Writer PUBLIC Map)
# Thirdparty libraries:
target_link_libraries(H3Writer PRIVATE zlib::zlibstatic)

# For Visual Studio: Use Unicode Character Set.
target_compile_definitions(H3Writer PRIVATE _UNICODE)

# Enable Whole Program Optimization in Release if it's supported.
include(CheckIPOSupported)
check_ipo_supported(RESULT IPO_SUPPORTED)
if(IPO_SUPPORTED)
  set_target_properties(H3Writer PROPERTIES
    INTERPROCEDURAL_OPTIMIZATION TRUE
    INTERPROCEDURAL_OPTIMIZATION_DEBUG FALSE
    INTERPROCEDURAL_OPTIMIZATION_RELEASE TRUE
    INTERPROCEDURAL_OPTIMIZATION_RELWITHDEBINFO TRUE
    INTERPROCEDURAL_OPTIMIZATION_MINSIZEREL TRUE
  )
endif()
