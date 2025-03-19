#pragma once

#include <h3mtxt/JsonWriter/JsonWriterFwd.h>
#include <h3mtxt/JsonWriter/JsonWriterContext.h>
#include <h3mtxt/JsonWriter/writeValue.h>

#include <string>
#include <string_view>

namespace Medea_NS
{
  // Class for writing fields of a JSON object.
  class ScopedObjectWriter
  {
  public:
    explicit ScopedObjectWriter(Detail_NS::JsonWriterContext& context);
    //  context_(context)
    //{
    //  context_.beginAggregate('{');
    //}

    ~ScopedObjectWriter();
    //{
    //  try
    //  {
    //    context_.endAggregate('}', true);
    //  }
    //  catch (...)
    //  {
    //  }
    //}

    // Non-copyable, non-movable.
    ScopedObjectWriter(const ScopedObjectWriter&) = delete;
    ScopedObjectWriter(ScopedObjectWriter&&) = delete;
    ScopedObjectWriter& operator=(const ScopedObjectWriter&) = delete;
    ScopedObjectWriter& operator=(ScopedObjectWriter&&) = delete;

    // Writes a single field.
    template<class T>
    void writeField(std::string_view field_name, const T& value);

    // Write a comment line.
    // \param comment - comment text. Empty comments are ignored.
    // \param newline - if true, the comment will be written on a new line,
    //        otherwise it will be written on the current line.
    void writeComment(std::string_view comment, bool newline = true);
    //{
    //  context_.writeComment(comment, newline);
    //}

  private:
    Detail_NS::JsonWriterContext& context_;
  };

  template<class T>
  void ScopedObjectWriter::writeField(std::string_view field_name, const T& value)
  {
    context_.beforeWriteValue(true);
    context_.writeFieldName(field_name);
    Detail_NS::writeValueRaw(context_, value);
  }
}
