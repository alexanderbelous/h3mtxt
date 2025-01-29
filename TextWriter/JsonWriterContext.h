#pragma once

#include <h3mtxt/TextWriter/JsonWriterFwd.h>

#include <cstddef>
#include <iosfwd>
#include <string_view>

namespace Util_NS
{
   namespace Detail_NS
  {
    class JsonWriterContext
    {
      explicit constexpr JsonWriterContext(std::ostream& stream, std::size_t initial_indent = 0) noexcept:
        stream_(stream),
        indent_(initial_indent)
      {}

      constexpr JsonWriterContext(const JsonWriterContext&) noexcept = default;
      constexpr JsonWriterContext(JsonWriterContext&&) noexcept = default;
      JsonWriterContext& operator=(const JsonWriterContext&) = delete;
      JsonWriterContext& operator=(JsonWriterContext&&) = delete;
      constexpr ~JsonWriterContext() = default;


      friend JsonDocumentWriter;
      friend ScopedArrayWriterBase;
      friend ScopedStructWriter;

      void writeComment(std::string_view comment);

      void writeString(std::string_view value);

      void writeNewlineIfNeeded();

      void increaseIndent();

      void decreaseIndent();

      std::ostream& stream_;
      std::size_t indent_ = 0;
      bool needs_newline_ = false;
    };
  }
}
