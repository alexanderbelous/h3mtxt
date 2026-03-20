# Path to the parent directory.
# This will be added to the list of additional include directories for each
# target, so that headers can be included as, for example:
#     #include <h3mtxt/Map/Map.h>
set(H3MTXT_SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/..")

# Thirdparty libraries:
set(CMAKE_FOLDER thirdparty)
# JsonCpp:
option(BUILD_SHARED_LIBS "Build jsoncpp_lib as a shared library." OFF)
option(BUILD_STATIC_LIBS "Build jsoncpp_lib as a static library." ON)
option(BUILD_OBJECT_LIBS "Build jsoncpp_lib as a object library." OFF)
add_subdirectory(thirdparty/jsoncpp EXCLUDE_FROM_ALL)
add_library(jsoncpp::jsoncpp_static ALIAS jsoncpp_static)
# zlib:
set(RENAME_ZCONF OFF) # don't rename zconf.h
add_subdirectory(thirdparty/zlib EXCLUDE_FROM_ALL)
add_library(zlib::zlibstatic ALIAS zlibstatic)
unset(CMAKE_FOLDER)

# All subdirectories with source code.
add_subdirectory(Map)
add_subdirectory(Campaign)
add_subdirectory(JsonCommon)
add_subdirectory(Medea)
set(CMAKE_FOLDER H3JsonReader)
add_subdirectory(H3JsonReader)
unset(CMAKE_FOLDER)
set(CMAKE_FOLDER H3JsonWriter)
add_subdirectory(H3JsonWriter)
unset(CMAKE_FOLDER)
set(CMAKE_FOLDER H3Reader)
add_subdirectory(H3Reader)
unset(CMAKE_FOLDER)
set(CMAKE_FOLDER H3Writer)
add_subdirectory(H3Writer)
unset(CMAKE_FOLDER)

# Target for the h3mtxt program.
add_executable(h3mtxt h3mtxt.cpp)
add_executable(h3mtxt::h3mtxt ALIAS h3mtxt)

# Add the parent of the repository to the list of additional include directories,
# so that headers can be included as, for example:
#     #include <h3mtxt/Map/Map.h>
target_include_directories(h3mtxt PRIVATE "${H3MTXT_SRC_DIR}")

# Libraries that h3mtxt depends on.
target_link_libraries(h3mtxt PRIVATE h3mtxt::Map)
target_link_libraries(h3mtxt PRIVATE h3mtxt::Campaign)
target_link_libraries(h3mtxt PRIVATE h3mtxt::H3Reader)
target_link_libraries(h3mtxt PRIVATE h3mtxt::H3MWriter)
target_link_libraries(h3mtxt PRIVATE h3mtxt::H3CWriter)
target_link_libraries(h3mtxt PRIVATE h3mtxt::H3JsonReader)
target_link_libraries(h3mtxt PRIVATE h3mtxt::H3MJsonWriter)
target_link_libraries(h3mtxt PRIVATE h3mtxt::H3CJsonWriter)

# Set compiler options for h3mtxt.
h3mtxt_add_common_compiler_options(h3mtxt)
