#pragma once

#include <h3mtxt/JsonWriter/JsonWriterFwd.h>
#include <h3mtxt/JsonWriter/JsonWriterContext.h>

#include <string_view>
#include <type_traits>

namespace Medea_NS
{
  // Class for serializing elements of a JSON array.
  //
  // The class is CopyConstructible and MoveConstructible, but neither CopyAssignable nor MoveAssignable.
  class ScopedArrayWriter
  {
  public:
    explicit constexpr ScopedArrayWriter(Detail_NS::JsonWriterContext& context,
                                         bool one_element_per_line = true) noexcept;

    // Writes a single element.
    template<class T>
    void writeElement(const T& value) const;

    // Writes a comment line.
    inline void writeComment(std::string_view comment) const;

  private:
    Detail_NS::JsonWriterContext& context_;
    bool one_element_per_line_ {};
  };

  // Class for writing fields of a JSON object.
  //
  // The class is CopyConstructible and MoveConstructible, but neither CopyAssignable nor MoveAssignable.
  class ScopedObjectWriter
  {
  public:
    explicit constexpr ScopedObjectWriter(Detail_NS::JsonWriterContext& context) noexcept;

    // Writes a single field.
    template<class T>
    void writeField(std::string_view field_name, const T& value) const;

    // Writes a comment line.
    // \param comment - comment text. Empty comments are ignored.
    // \param newline - if true, the comment will be written on a new line,
    //        otherwise it will be written on the current line.
    inline void writeComment(std::string_view comment, bool newline = true);

  private:
    Detail_NS::JsonWriterContext& context_;
  };

  constexpr ScopedObjectWriter::ScopedObjectWriter(Detail_NS::JsonWriterContext& context) noexcept :
    context_(context)
  {}

  template<class T>
  void ScopedObjectWriter::writeField(std::string_view field_name, const T& value) const
  {
    context_.writeField(field_name, value);
  }

  void ScopedObjectWriter::writeComment(std::string_view comment, bool newline)
  {
    context_.writeComment(comment, newline);
  }

  constexpr ScopedArrayWriter::ScopedArrayWriter(Detail_NS::JsonWriterContext& context,
                                                 bool one_element_per_line) noexcept:
    context_(context),
    one_element_per_line_(one_element_per_line)
  {}

  template<class T>
  void ScopedArrayWriter::writeElement(const T& value) const
  {
    context_.writeValue(value, one_element_per_line_);
  }

  void ScopedArrayWriter::writeComment(std::string_view comment) const
  {
    context_.writeComment(comment, true);
  }
}
