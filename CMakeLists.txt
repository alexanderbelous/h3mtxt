cmake_minimum_required(VERSION 4.0)

# Requires C++20.
set(CMAKE_CXX_STANDARD 20 CACHE STRING "The C++ standard to use")
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(
  h3mtxt
  VERSION 0.9.6
  LANGUAGES CXX
)

# Use static (MT/MTd) Windows runtime.
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

# Organize targets into folders (if supported by IDE).
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Load a CMake file with common functions used in this repository.
include(cmake/h3mtxt_common.cmake)

# Add subdirectories with source code.
add_subdirectory(src)

# Tests are disabled by default.
# This can be overridden from the command line, e.g., "cmake -S . -B build -DH3MTXT_BUILD_TESTS=ON"
option(H3MTXT_BUILD_TESTS "Build tests for h3mtxt." OFF)
# Add the subdirectory with tests, if needed.
if(H3MTXT_BUILD_TESTS)
  include(CTest)
  set(CMAKE_FOLDER tests)
  add_subdirectory(tests)
  unset(CMAKE_FOLDER)
endif()

# Examples are disabled by default.
# This can be overridden from the command line, e.g., "cmake -S . -B build -DH3MTXT_BUILD_EXAMPLES=ON"
option(H3MTXT_BUILD_EXAMPLES "Build examples for h3mtxt." OFF)
# Add the subdirectory with examples, if needed.
if(H3MTXT_BUILD_EXAMPLES)
  set(CMAKE_FOLDER examples)
  add_subdirectory(examples)
  unset(CMAKE_FOLDER)
endif()

# Installation rule for h3mtxt binary.
install(TARGETS h3mtxt)
