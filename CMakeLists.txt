cmake_minimum_required(VERSION 4.0)

# Requires C++20.
set(CMAKE_CXX_STANDARD 20 CACHE STRING "The C++ standard to use")
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(
  h3mtxt
  VERSION 0.8.0
  LANGUAGES CXX
)

# Use static (MT/MTd) Windows runtime.
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

# Thirdparty libraries:
# JsonCpp:
option(JSONCPP_WITH_TESTS "Compile and (for jsoncpp_check) run JsonCpp test executables" OFF)
option(BUILD_SHARED_LIBS "Build jsoncpp_lib as a shared library." OFF)
option(BUILD_STATIC_LIBS "Build jsoncpp_lib as a static library." ON)
option(BUILD_OBJECT_LIBS "Build jsoncpp_lib as a object library." OFF)
add_subdirectory(thirdparty/jsoncpp)
add_library(jsoncpp::jsoncpp_static ALIAS jsoncpp_static)
# zlib:
option(ZLIB_BUILD_EXAMPLES "Enable Zlib Examples" OFF)
set(RENAME_ZCONF OFF) # don't rename zconf.h
add_subdirectory(thirdparty/zlib)
add_library(zlib::zlibstatic ALIAS zlibstatic)

# All subdirectories with source code.
add_subdirectory(Map)
add_subdirectory(Campaign)
add_subdirectory(JsonCommon)
add_subdirectory(Medea)
add_subdirectory(H3JsonReader)
add_subdirectory(H3JsonWriter)
add_subdirectory(H3Reader)
add_subdirectory(H3Writer)

# The only target is the h3mtxt application.
add_executable(h3mtxt h3mtxt.cpp)

# Add the parent of the repository to the list of additional include directories,
# so that headers can be included as, for example:
#     #include <h3mtxt/Map/Map.h>
target_include_directories(h3mtxt PRIVATE "${PROJECT_SOURCE_DIR}/..")

# Libraries that h3mtxt depends on.
target_link_libraries(h3mtxt PRIVATE h3mtxt::Map)
target_link_libraries(h3mtxt PRIVATE h3mtxt::Campaign)
target_link_libraries(h3mtxt PRIVATE h3mtxt::H3Reader)
target_link_libraries(h3mtxt PRIVATE h3mtxt::H3Writer)
target_link_libraries(h3mtxt PRIVATE h3mtxt::H3JsonReader)
target_link_libraries(h3mtxt PRIVATE h3mtxt::H3JsonWriter)

# For Visual Studio: Use Unicode Character Set.
target_compile_definitions(h3mtxt PRIVATE _UNICODE)

# Enable Whole Program Optimization in Release if it's supported.
include(CheckIPOSupported)
check_ipo_supported(RESULT IPO_SUPPORTED)
if(IPO_SUPPORTED)
  set_target_properties(h3mtxt PROPERTIES
    INTERPROCEDURAL_OPTIMIZATION TRUE
    INTERPROCEDURAL_OPTIMIZATION_DEBUG FALSE
    INTERPROCEDURAL_OPTIMIZATION_RELEASE TRUE
    INTERPROCEDURAL_OPTIMIZATION_RELWITHDEBINFO TRUE
    INTERPROCEDURAL_OPTIMIZATION_MINSIZEREL TRUE
  )
endif()
