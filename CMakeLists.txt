cmake_minimum_required(VERSION 4.0)

# Requires C++20.
set(CMAKE_CXX_STANDARD 20 CACHE STRING "The C++ standard to use")
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(
  h3mtxt
  VERSION 0.9.4
  LANGUAGES CXX
)

# Use static (MT/MTd) Windows runtime.
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

# Organize targets into folders (if supported by IDE).
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

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

# Add subdirectories with source code.
add_subdirectory(src)

# Tests are disabled by default.
# This can be overridden from the command line, e.g., "cmake -S . -B build -DH3MTXT_BUILD_TESTS=ON"
option(H3MTXT_BUILD_TESTS "Build tests for h3mtxt." OFF)
# Add the subdirectory with tests, if needed.
if(H3MTXT_BUILD_TESTS)
  set(CMAKE_FOLDER tests)
  add_subdirectory(tests)
  unset(CMAKE_FOLDER)
endif()

# Installation rule for h3mtxt binary.
install(TARGETS h3mtxt)
