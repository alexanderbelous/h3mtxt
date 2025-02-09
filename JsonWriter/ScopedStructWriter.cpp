#include <h3mtxt/JsonWriter/ScopedStructWriter.h>

#include <ostream>

namespace Medea_NS
{
  ScopedStructWriter::ScopedStructWriter(const Detail_NS::JsonWriterContext& context):
    context_(context)
  {
    context_.writeNewlineIfNeeded();
    context_.stream_.put('{');
    context_.increaseIndent();
    context_.needs_newline_ = true;
  }

  ScopedStructWriter::~ScopedStructWriter()
  {
    try
    {
      context_.decreaseIndent();
      // TODO: don't write a newline if no fields have been written.
      context_.writeNewlineIfNeeded();
      context_.stream_.put('}');
    }
    catch (...)
    {
    }
  }

  void ScopedStructWriter::writeComment(std::string_view comment, bool newline)
  {
    // If the last token was a comment, write a newline anyway.
    if (!newline && (last_token_ != Token::Comment))
    {
      // Otherwise, append a space and instruct JsonDocumentWriter not to write a newline character.
      context_.stream_.put(' ');
      context_.needs_newline_ = false;
    }
    context_.writeComment(comment);
    last_token_ = Token::Comment;
  }

  void ScopedStructWriter::writeComma()
  {
    static constexpr std::string_view kCommaStr = ", ";
    if (needs_comma_)
    {
      if (last_token_ == Token::Comment)
      {
        context_.writeNewlineIfNeeded();
        context_.stream_.write(kCommaStr.data(), kCommaStr.size());
      }
      else
      {
        // last_token_ can only be Token::Field.
        context_.stream_.put(',');
      }
      needs_comma_ = false;
      last_token_ = Token::Comma;
    }
  }

  void ScopedStructWriter::writeFieldName(std::string_view field_name)
  {
    static constexpr std::string_view kSeparator = ": ";
    // Write a comma, if needed.
    writeComma();
    context_.writeString(field_name);
    context_.stream_.write(kSeparator.data(), kSeparator.size());
    context_.needs_newline_ = false;
  }
}
