#include <h3mtxt/TextWriter/JsonDocumentWriter.h>

#include <h3mtxt/TextWriter/ScopedStructWriter.h>

#include <ostream>

namespace Util_NS
{
  void JsonDocumentWriter::checkNotDone() const
  {
    if (is_done_)
    {
      throw std::runtime_error("JsonDocumentWriter: a value has already been written.");
    }
  }

  void JsonDocumentWriter::writeString(std::string_view value)
  {
    checkNotDone();
    context_.writeString(value);
    is_done_ = true;
  }

  void JsonDocumentWriter::writeBool(bool value)
  {
    checkNotDone();
    context_.writeNewlineIfNeeded();
    context_.stream_ << (value ? "true" : "false");
    is_done_ = true;
  }

  void JsonDocumentWriter::writeInt(std::intmax_t value)
  {
    checkNotDone();
    context_.writeNewlineIfNeeded();
    context_.stream_ << value;
    is_done_ = true;
  }

  void JsonDocumentWriter::writeUInt(std::uintmax_t value)
  {
    checkNotDone();
    context_.writeNewlineIfNeeded();
    context_.stream_ << value;
    is_done_ = true;
  }

  ScopedStructWriter JsonDocumentWriter::writeStruct()
  {
    checkNotDone();
    is_done_ = true;
    return ScopedStructWriter(context_);
  }
}
