#pragma once

#include <h3mtxt/JsonWriter/JsonWriterFwd.h>

#include <cstddef>
#include <iosfwd>
#include <string_view>

namespace Medea_NS
{
  namespace Detail_NS
  {
    // Stores the underlying std::ostream and formatting-related data.
    // Note that all members are private - this class should not be used directly.
    class JsonWriterContext
    {
      friend JsonDocumentWriter;
      friend ScopedArrayWriterBase;
      friend ScopedObjectWriter;

      explicit constexpr JsonWriterContext(std::ostream& stream, unsigned int initial_indent = 0) noexcept:
        stream_(stream),
        indent_(initial_indent)
      {}

      constexpr JsonWriterContext(const JsonWriterContext&) noexcept = default;
      constexpr JsonWriterContext(JsonWriterContext&&) noexcept = default;
      JsonWriterContext& operator=(const JsonWriterContext&) = delete;
      JsonWriterContext& operator=(JsonWriterContext&&) = delete;
      constexpr ~JsonWriterContext() = default;

      void writeComment(std::string_view comment);

      void writeString(std::string_view value);

      void writeNewlineIfNeeded();

      constexpr void increaseIndent() noexcept
      {
        indent_ += 2;
      }

      constexpr void decreaseIndent() noexcept
      {
        // This should never happen.
        if (indent_ < 2)
        {
          indent_ = 0;
        }
        indent_ -= 2;
      }

      std::ostream& stream_;
      unsigned int indent_ = 0;
      bool needs_newline_ = false;
    };
  }
}
