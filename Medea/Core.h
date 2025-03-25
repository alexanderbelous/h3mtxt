#pragma once

// Bare minimum API: does not include built-in specializations for common types (e.g., bool, std::string, etc).
//
// This can be used if you define specializations for JsonObjectWriter and/or JsonArrayWriter in one translation
// unit and want to use them (and only them) in another.
// Alternatively, this can be useful if you don't want to use the built-in specializations,
// e.g., if you want to serialize std::vector as a JSON object instead of an array).
//
// Otherwise, just include Medea.h.

#include <h3mtxt/Medea/MedeaFwd.h>
#include <h3mtxt/Medea/JsonWriterImpl.h>
#include <h3mtxt/Medea/MinifiedJsonWriter.h>

namespace Medea_NS
{
  // Serializes the given value as JSON.
  // \param stream - output stream.
  // \param value - input value.
  // \param initial_indent - the initial indent (number of spaces).
  // \param single_line - if true, @value will be serialized on a single line,
  //        otherwise over multiple lines.
  template<class T>
  void writeJson(std::ostream& stream,
                 const T& value,
                 unsigned int initial_indent = 0,
                 bool single_line = kIsSingleLineByDefault<std::remove_cvref_t<T>>)
  {
    Detail_NS::JsonWriterImpl::writeJson(stream, value, initial_indent, single_line);
  }

  template<class T>
  void writeMinifiedJson(std::ostream& stream, const T& value)
  {
    MinifiedJsonWriter::writeJson(stream, value);
  }
}
