cmake_minimum_required(VERSION 4.0)

# Requires C++20.
set(CMAKE_CXX_STANDARD 20 CACHE STRING "The C++ standard to use")
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(
  h3mtxt
  VERSION 0.9.1
  LANGUAGES CXX
)

# Use static (MT/MTd) Windows runtime.
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

# Check if IPO (aka Whole Program Optimization) is supported.
include(CheckIPOSupported)
check_ipo_supported(RESULT H3MTXT_IPO_SUPPORTED OUTPUT H3MTXT_IPO_SUPPORTED_OUTPUT)
if (NOT H3MTXT_IPO_SUPPORTED)
  message("IPO not supported: ${H3MTXT_IPO_SUPPORTED_OUTPUT}")
endif()

# Sets common compiler options to the specified target.
# This is to reduce boilerplate in CMakeLists.txt files in subdirectories.
# \param target - target to modify.
function(h3mtxt_add_common_compiler_options target)
  if(MSVC)
    # Use Unicode Character Set.
    target_compile_definitions(${target} PRIVATE _UNICODE)

    # Set source and execution character sets to UTF-8.
    target_compile_options(${target} PUBLIC "/utf-8")

    # Enable Function Level Linking (Release only)
    target_compile_options(${target} PUBLIC "$<$<CONFIG:Release>:/Gy>")

    # Enable Intrinsic Functions (Release only)
    target_compile_options(${target} PUBLIC "$<$<CONFIG:Release>:/Oi>")

    # For executables:
    get_target_property(target_type ${target} TYPE)
    if (target_type STREQUAL "EXECUTABLE")
      # Enable COMDAT Folding (Release only)
      target_link_options(${target} PUBLIC "$<$<CONFIG:Release>:/OPT:ICF>")

      # Do not generate Manifest
      target_link_options(${target} PUBLIC "/MANIFEST:NO")
    endif ()

    # Set warning level
    target_compile_options(${target} PRIVATE /W4 /permissive-)
  else()
    # Set warning level
    target_compile_options(${target} PRIVATE -Wall -Wextra -Wpedantic)
  endif()

  # Enable Whole Program Optimization in Release if it's supported.
  if(H3MTXT_IPO_SUPPORTED)
    set_target_properties(${target} PROPERTIES
      INTERPROCEDURAL_OPTIMIZATION TRUE
      INTERPROCEDURAL_OPTIMIZATION_DEBUG FALSE
      INTERPROCEDURAL_OPTIMIZATION_RELEASE TRUE
      INTERPROCEDURAL_OPTIMIZATION_RELWITHDEBINFO TRUE
      INTERPROCEDURAL_OPTIMIZATION_MINSIZEREL TRUE
    )
  endif()
endfunction()

# Thirdparty libraries:
# JsonCpp:
# option(JSONCPP_WITH_TESTS "Compile and (for jsoncpp_check) run JsonCpp test executables" OFF)
option(BUILD_SHARED_LIBS "Build jsoncpp_lib as a shared library." OFF)
option(BUILD_STATIC_LIBS "Build jsoncpp_lib as a static library." ON)
option(BUILD_OBJECT_LIBS "Build jsoncpp_lib as a object library." OFF)
add_subdirectory(thirdparty/jsoncpp EXCLUDE_FROM_ALL)
add_library(jsoncpp::jsoncpp_static ALIAS jsoncpp_static)
# zlib:
set(RENAME_ZCONF OFF) # don't rename zconf.h
add_subdirectory(thirdparty/zlib EXCLUDE_FROM_ALL)
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

# Target for the h3mtxt program.
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

# Set compiler options for h3mtxt.
h3mtxt_add_common_compiler_options(h3mtxt)

# Installation rule for h3mtxt.
install(TARGETS h3mtxt)
