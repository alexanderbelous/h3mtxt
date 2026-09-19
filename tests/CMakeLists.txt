add_library(h3mtxt_TestUtils INTERFACE
    "Utils.h"
)
add_library(h3mtxt::TestUtils ALIAS h3mtxt_TestUtils)
target_link_libraries(h3mtxt_TestUtils INTERFACE h3mtxt::H3JsonReaderBase)
target_link_libraries(h3mtxt_TestUtils INTERFACE h3mtxt::Medea)

add_subdirectory(thirdparty/Catch2 EXCLUDE_FROM_ALL)
add_subdirectory(Map)
add_subdirectory(Campaign)
add_subdirectory(SavedGame)
