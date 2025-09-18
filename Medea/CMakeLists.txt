add_library(Medea STATIC
    "ArrayElementsWriter.h"
    "Core.h"
    "FieldsWriter.h"
    "JsonWriterImpl.h"
    "Medea.h"
    "MedeaFwd.h"
    "JsonWriterImpl.cpp"
)
add_library(h3mtxt::Medea ALIAS Medea)

target_include_directories(Medea PUBLIC "${PROJECT_SOURCE_DIR}/..")

# For Visual Studio: Use Unicode Character Set.
target_compile_definitions(Medea PRIVATE _UNICODE)

# Enable Whole Program Optimization in Release if it's supported.
include(CheckIPOSupported)
check_ipo_supported(RESULT IPO_SUPPORTED)
if(IPO_SUPPORTED)
  set_target_properties(Medea PROPERTIES
    INTERPROCEDURAL_OPTIMIZATION TRUE
    INTERPROCEDURAL_OPTIMIZATION_DEBUG FALSE
    INTERPROCEDURAL_OPTIMIZATION_RELEASE TRUE
    INTERPROCEDURAL_OPTIMIZATION_RELWITHDEBINFO TRUE
    INTERPROCEDURAL_OPTIMIZATION_MINSIZEREL TRUE
  )
endif()

# Set warning level
if(MSVC)
  target_compile_options(Medea PRIVATE /W4)
else()
  target_compile_options(Medea PRIVATE -Wall -Wextra -Wpedantic)
endif()
