#include <h3mtxt/Medea/MinifiedJsonWriter.h>
#include <h3mtxt/Medea/ArrayElementsWriter.h>
#include <h3mtxt/Medea/FieldsWriter.h>

#include <algorithm>
#include <iterator>
#include <ostream>

namespace Medea_NS
{
  namespace
  {
    constexpr std::string_view getEscapeSequence(char c) noexcept
    {
      switch (c)
      {
      case '"':
        return "\\\"";
      case '\\':
        return "\\\\";
      case '/':
        return "\\/";
      case '\b':
        return "\\b";
      case '\f':
        return "\\f";
      case '\n':
        return "\\n";
      case '\r':
        return "\\r";
      case '\t':
        return "\\t";
      default:
        return {};
      }
    }
  }

  void MinifiedJsonWriter::beforeWriteElementOrField()
  {
    if (has_members_in_scope_)
    {
      stream_.put(',');
    }
  }

  void MinifiedJsonWriter::writeBool(bool value)
  {
    static constexpr std::string_view kFalseStr = "false";
    static constexpr std::string_view kTrueStr = "true";

    const std::string_view str = value ? kTrueStr : kFalseStr;
    stream_.write(str.data(), str.size());
    has_members_in_scope_ = true;
  }

  void MinifiedJsonWriter::writeInt(std::intmax_t value)
  {
    std::string int_str = std::to_string(value);
    stream_.write(int_str.data(), int_str.size());
    has_members_in_scope_ = true;
  }

  void MinifiedJsonWriter::writeUInt(std::uintmax_t value)
  {
    std::string int_str = std::to_string(value);
    stream_.write(int_str.data(), int_str.size());
    has_members_in_scope_ = true;
  }

  void MinifiedJsonWriter::writeString(std::string_view value)
  {
    stream_.put('"');
    const char* iter = value.data();
    const char* const last = iter + value.size();
    while (iter != last)
    {
      // Check if *iter a special character.
      const std::string_view escape_seq = getEscapeSequence(*iter);
      if (!escape_seq.empty())
      {
        stream_.write(escape_seq.data(), escape_seq.size());
        ++iter;
        continue;
      }
      else
      {
        // Find the next special character.
        const char* const iter_next_special =
          std::find_if(iter, last, [](char c) { return !getEscapeSequence(c).empty(); });
        // Write [iter; iter_next_special).
        stream_.write(iter, std::distance(iter, iter_next_special));
        iter = iter_next_special;
      }
    }
    stream_.put('"');
    has_members_in_scope_ = true;
  }

  void MinifiedJsonWriter::beginAggregate(char bracket)
  {
    stream_.put(bracket);
    has_members_in_scope_ = false;
  }

  void MinifiedJsonWriter::endAggregate(char bracket)
  {
    stream_.put(bracket);
    // We've just finished writing an object/array, so the outer aggregate (whether it's an object or an array)
    // has at least 1 element.
    has_members_in_scope_ = true;
  }

  void MinifiedJsonWriter::writeFieldName(std::string_view field_name)
  {
    writeString(field_name);
    stream_.put(':');
  }

  void MinifiedJsonWriter::writeComment(std::string_view, bool)
  {
  }

  void MinifiedJsonWriter::writeArray(ArrayWriterPtr array_writer, const void* value, bool)
  {
    beginAggregate('[');
    array_writer(ArrayElementsWriter{ *this }, value);
    endAggregate(']');
  }

  void MinifiedJsonWriter::writeObject(ObjectWriterPtr object_writer, const void* value, bool)
  {
    beginAggregate('{');
    {
      FieldsWriter fields_writer{ *this };
      object_writer(fields_writer, value);
    }
    endAggregate('}');
  }
}
