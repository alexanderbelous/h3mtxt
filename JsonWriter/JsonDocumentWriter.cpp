#include <h3mtxt/JsonWriter/JsonDocumentWriter.h>

#include <h3mtxt/JsonWriter/ScopedStructWriter.h>

#include <ostream>
#include <stdexcept>

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
    static constexpr std::string_view kFalseStr = "false";
    static constexpr std::string_view kTrueStr = "true";

    checkNotDone();
    context_.writeNewlineIfNeeded();
    const std::string_view str = value ? kTrueStr : kFalseStr;
    context_.stream_.write(str.data(), str.size());
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
