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

# Set compiler options.
h3mtxt_add_common_compiler_options(Medea)
