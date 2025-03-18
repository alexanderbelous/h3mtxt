#pragma once

#include <h3mtxt/JsonWriter/JsonWriterFwd.h>
#include <h3mtxt/JsonWriter/writeValue.h>

#include <iosfwd>

namespace Medea_NS
{
  // Serializes the given value as JSON.
  // \param stream - output stream.
  // \param value - input value.
  // \param initial_indent - the initial indent (number of spaces).
  template<class T>
  void writeJson(std::ostream& stream, const T& value, unsigned int initial_indent = 0)
  {
    Detail_NS::JsonWriterContext context(stream, initial_indent);
    Detail_NS::writeValue(context, value);
  }
}
