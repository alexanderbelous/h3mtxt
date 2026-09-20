add_executable(h3mtxt_tests_Campaign
    "CampaignScenario.cpp"
    "CrossoverOptions.cpp"
    "CutScene.cpp"
    "StartingBonus.cpp"
    "StartingOptions.cpp"
    "TestUtils_H3C.h"
)

# Dependencies:
target_link_libraries(h3mtxt_tests_Campaign PRIVATE h3mtxt::Campaign)
target_link_libraries(h3mtxt_tests_Campaign PRIVATE h3mtxt::H3CJsonReader)
target_link_libraries(h3mtxt_tests_Campaign PRIVATE h3mtxt::H3CJsonWriter)
target_link_libraries(h3mtxt_tests_Campaign PRIVATE h3mtxt::H3CReader)
target_link_libraries(h3mtxt_tests_Campaign PRIVATE h3mtxt::H3CWriter)
target_link_libraries(h3mtxt_tests_Campaign PRIVATE h3mtxt::TestUtils)
# Thirdparty libraries:
target_link_libraries(h3mtxt_tests_Campaign PRIVATE Catch2::Catch2WithMain)

# Set compiler options.
h3mtxt_add_common_compiler_options(h3mtxt_tests_Campaign)

# Support for CTest
add_test(NAME h3mtxt_tests_Campaign COMMAND h3mtxt_tests_Campaign)
