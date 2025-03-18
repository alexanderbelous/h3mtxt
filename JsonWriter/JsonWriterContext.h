#pragma once

#include <h3mtxt/JsonWriter/JsonWriterFwd.h>

#include <cstddef>
#include <cstdint>
#include <iosfwd>
#include <string_view>

namespace Medea_NS
{
  // Forward declaration of writeJson().
  template<class T>
  void writeJson(std::ostream& stream, const T& value, unsigned int initial_indent);

  namespace Detail_NS
  {
    // Internal class for writing formatted JSON.
    //
    // This class cannot be used directly - all members are private.
    class JsonWriterContext
    {
      friend ScopedArrayWriterBase;
      friend ScopedObjectWriter;

      // writeValue() is a friend because it calls member functins writeBool(), writeString(), etc.
      template<class T>
      friend void writeValue(JsonWriterContext& context, const T& value);

      // writeJson() is a friend because it needs to construct JsonWriterContext.
      template<class T>
      friend void ::Medea_NS::writeJson(std::ostream& stream, const T& value, unsigned int initial_indent);

      explicit constexpr JsonWriterContext(std::ostream& stream, unsigned int initial_indent = 0) noexcept:
        stream_(stream),
        indent_(initial_indent)
      {}

      // Non-copyable, non-movable.
      constexpr JsonWriterContext(const JsonWriterContext&) noexcept = delete;
      constexpr JsonWriterContext(JsonWriterContext&&) noexcept = delete;
      JsonWriterContext& operator=(const JsonWriterContext&) = delete;
      JsonWriterContext& operator=(JsonWriterContext&&) = delete;

      constexpr ~JsonWriterContext() = default;

      // Writes a comment to the output stream.
      void writeComment(std::string_view comment);

      // Writes a boolean value to the output stream.
      // \param value - value to write.
      void writeBool(bool value);

      // Writes a signed integer value to the output stream.
      void writeInt(std::intmax_t value);

      // Writes an unsigned integer value to the output stream.
      void writeUInt(std::uintmax_t value);

      // Writes a string value to the output stream.
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
