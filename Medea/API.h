#pragma once

#include <h3mtxt/Medea/MedeaFwd.h>
#include <h3mtxt/Medea/JsonWriterImpl.h>

#include <string_view>

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

  // Class for serializing elements of a JSON array.
  class ArrayElementsWriter
  {
  public:
    explicit constexpr ArrayElementsWriter(Detail_NS::JsonWriterImpl& impl) noexcept;

    // Non-copyable, non-movable.
    ArrayElementsWriter(const ArrayElementsWriter&) = delete;
    ArrayElementsWriter(ArrayElementsWriter&&) = delete;
    ArrayElementsWriter& operator=(const ArrayElementsWriter&) = delete;
    ArrayElementsWriter& operator=(ArrayElementsWriter&&) = delete;

    constexpr ~ArrayElementsWriter() = default;

    // Writes a single element.
    // \param value - value of the element.
    // \param single_line - if true, @value will be serialized on a single line, otherwise over multiple lines.
    //        This parameter is ignored if the array itself is being serialized on a single line (in that case
    //        the behavior is equivalent to single_line == true).
    template<class T>
    void writeElement(const T& value, bool single_line = kIsSingleLineByDefault<std::remove_cvref_t<T>>) const;

    // Writes a comment line.
    // \param newline - if true, the comment will be written on a new line,
    //        otherwise it will be written on the current line.
    inline void writeComment(std::string_view comment, bool newline = true) const;

  private:
    Detail_NS::JsonWriterImpl& impl_;
  };

  // Class for writing fields of a JSON object.
  class FieldsWriter
  {
  public:
    explicit constexpr FieldsWriter(Detail_NS::JsonWriterImpl& impl) noexcept;

    // Non-copyable, non-movable.
    FieldsWriter(const FieldsWriter&) = delete;
    FieldsWriter(FieldsWriter&&) = delete;
    FieldsWriter& operator=(const FieldsWriter&) = delete;
    FieldsWriter& operator=(FieldsWriter&&) = delete;

    constexpr ~FieldsWriter() = default;

    // Writes a single field.
    // \param field_name - name of the field.
    // \param value - value of the field.
    // \param single_line - if true, this field will be serialized on a single line, otherwise over multiple lines.
    //        This parameter is ignored if the JSON object itself is being serialized on a single line (in that case
    //        the behavior is equivalent to single_line == true).
    template<class T>
    void writeField(std::string_view field_name,
                    const T& value,
                    bool single_line = kIsSingleLineByDefault<std::remove_cvref_t<T>>) const;

    // Writes a comment line.
    // \param comment - comment text. Empty comments are ignored.
    // \param newline - if true, the comment will be written on a new line,
    //        otherwise it will be written on the current line.
    inline void writeComment(std::string_view comment, bool newline = true) const;

  private:
    Detail_NS::JsonWriterImpl& impl_;
  };

  constexpr FieldsWriter::FieldsWriter(Detail_NS::JsonWriterImpl& impl) noexcept :
    impl_(impl)
  {}

  template<class T>
  void FieldsWriter::writeField(std::string_view field_name, const T& value, bool single_line) const
  {
    impl_.writeField(field_name, value, single_line);
  }

  void FieldsWriter::writeComment(std::string_view comment, bool newline) const
  {
    impl_.writeComment(comment, newline);
  }

  constexpr ArrayElementsWriter::ArrayElementsWriter(Detail_NS::JsonWriterImpl& impl) noexcept:
    impl_(impl)
  {}

  template<class T>
  void ArrayElementsWriter::writeElement(const T& value, bool single_line) const
  {
    impl_.writeArrayElement(value, single_line);
  }

  void ArrayElementsWriter::writeComment(std::string_view comment, bool newline) const
  {
    impl_.writeComment(comment, newline);
  }
}
