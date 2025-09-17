add_library(H3Reader STATIC
    "H3Reader.h"
    "IntegerWidth.h"
    "parseh3.cpp"
    "parseh3.h"
    "parseh3c.cpp"
    "parseh3c.h"
    "parseh3m.cpp"
    "parseh3m.h"
    "readCampaignHeader.cpp"
    "readCampaignScenario.cpp"
    "readCreatureStack.cpp"
    "readHeroArtifacts.cpp"
    "readMap.cpp"
    "readObject.cpp"
    "readPrimarySkills.cpp"
    "readQuest.cpp"
    "readResources.cpp"
    "readReward.cpp"
    "readSecondarySkill.cpp"
    "readSecondarySkillsVector.cpp"
    "readSecondarySkillsVector.h"
    "readStartingBonus.cpp"
    "readStartingOptions.cpp"
    "readTimedEvent.cpp"
    "readVictoryCondition.cpp"
    "Utils.cpp"
    "Utils.h"
)
add_library(h3mtxt::H3Reader ALIAS H3Reader)

target_include_directories(H3Reader PUBLIC "${PROJECT_SOURCE_DIR}/..")

# Dependencies:
target_link_libraries(H3Reader PUBLIC h3mtxt::Campaign)
target_link_libraries(H3Reader PUBLIC h3mtxt::Map)
# Thirdparty libraries:
target_link_libraries(H3Reader PRIVATE zlib::zlibstatic)

# For Visual Studio: Use Unicode Character Set.
target_compile_definitions(H3Reader PRIVATE _UNICODE)

# Enable Whole Program Optimization in Release if it's supported.
include(CheckIPOSupported)
check_ipo_supported(RESULT IPO_SUPPORTED)
if(IPO_SUPPORTED)
  set_target_properties(H3Reader PROPERTIES
    INTERPROCEDURAL_OPTIMIZATION TRUE
    INTERPROCEDURAL_OPTIMIZATION_DEBUG FALSE
    INTERPROCEDURAL_OPTIMIZATION_RELEASE TRUE
    INTERPROCEDURAL_OPTIMIZATION_RELWITHDEBINFO TRUE
    INTERPROCEDURAL_OPTIMIZATION_MINSIZEREL TRUE
  )
endif()
