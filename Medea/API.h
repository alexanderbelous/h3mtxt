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
  template<class T>
  void writeJson(std::ostream& stream, const T& value, unsigned int initial_indent = 0)
  {
    Detail_NS::JsonWriterImpl::writeJson(stream, value, initial_indent);
  }

  // Class for serializing elements of a JSON array.
  class ArrayElementsWriter
  {
  public:
    explicit constexpr ArrayElementsWriter(Detail_NS::JsonWriterImpl& impl,
                                           bool one_element_per_line = true) noexcept;

    // Non-copyable, non-movable.
    ArrayElementsWriter(const ArrayElementsWriter&) = delete;
    ArrayElementsWriter(ArrayElementsWriter&&) = delete;
    ArrayElementsWriter& operator=(const ArrayElementsWriter&) = delete;
    ArrayElementsWriter& operator=(ArrayElementsWriter&&) = delete;

    constexpr ~ArrayElementsWriter() = default;

    // Writes a single element.
    template<class T>
    void writeElement(const T& value) const;

    // Writes a comment line.
    inline void writeComment(std::string_view comment) const;

  private:
    Detail_NS::JsonWriterImpl& impl_;
    bool one_element_per_line_ {};
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
    template<class T>
    void writeField(std::string_view field_name, const T& value) const;

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
  void FieldsWriter::writeField(std::string_view field_name, const T& value) const
  {
    impl_.writeField(field_name, value);
  }

  void FieldsWriter::writeComment(std::string_view comment, bool newline) const
  {
    impl_.writeComment(comment, newline);
  }

  constexpr ArrayElementsWriter::ArrayElementsWriter(Detail_NS::JsonWriterImpl& impl,
                                                     bool one_element_per_line) noexcept:
    impl_(impl),
    one_element_per_line_(one_element_per_line)
  {}

  template<class T>
  void ArrayElementsWriter::writeElement(const T& value) const
  {
    impl_.writeValue(value, one_element_per_line_);
  }

  void ArrayElementsWriter::writeComment(std::string_view comment) const
  {
    impl_.writeComment(comment, true);
  }
}
