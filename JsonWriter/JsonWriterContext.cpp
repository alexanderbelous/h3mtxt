#include <h3mtxt/JsonWriter/JsonWriterContext.h>

#include <algorithm>
#include <iterator>
#include <ostream>
#include <ranges>

namespace Medea_NS::Detail_NS
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

  void JsonWriterContext::beforeWriteValue(bool newline)
  {
    const bool needs_newline = newline || hasUnflushedComment();
    if (has_members_in_scope_)
    {
      stream_.put(',');
      // Append a space if the next element will be written on the same line.
      if (!needs_newline)
      {
        stream_.put(' ');
      }
    }
    flushComments();
    // Write a newline character and indent, if needed.
    if (needs_newline)
    {
      writeNewline();
    }
  }

  void JsonWriterContext::writeBool(bool value)
  {
    static constexpr std::string_view kFalseStr = "false";
    static constexpr std::string_view kTrueStr = "true";

    const std::string_view str = value ? kTrueStr : kFalseStr;
    stream_.write(str.data(), str.size());
    has_members_in_scope_ = true;
  }

  void JsonWriterContext::writeInt(std::intmax_t value)
  {
    std::string int_str = std::to_string(value);
    stream_.write(int_str.data(), int_str.size());
    has_members_in_scope_ = true;
  }

  void JsonWriterContext::writeUInt(std::uintmax_t value)
  {
    std::string int_str = std::to_string(value);
    stream_.write(int_str.data(), int_str.size());
    has_members_in_scope_ = true;
  }

  void JsonWriterContext::writeString(std::string_view value)
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

  void JsonWriterContext::writeNewline()
  {
    stream_.put('\n');
    std::fill_n(std::ostream_iterator<char>(stream_), indent_, ' ');
  }

  void JsonWriterContext::beginAggregate(char bracket)
  {
    stream_.put(bracket);
    indent_ += 2;
    has_members_in_scope_ = false;
  }

  void JsonWriterContext::endAggregate(char bracket, bool newline)
  {
    const bool has_unflushed_comments = hasUnflushedComment();
    flushComments();
    // Sanity check.
    if (indent_ >= 2)
    {
      indent_ -= 2;
    }
    if (has_unflushed_comments || (newline && has_members_in_scope_))
    {
      writeNewline();
    }
    stream_.put(bracket);
    // We've just finished writing an object/array, so the outer aggregate (whether it's an object or an array)
    // has at least 1 element.
    has_members_in_scope_ = true;
  }

  void JsonWriterContext::writeFieldName(std::string_view field_name)
  {
    constexpr std::string_view kSeparator = ": ";
    writeString(field_name);
    stream_.write(kSeparator.data(), kSeparator.size());
  }

  void JsonWriterContext::writeComment(std::string_view comment, bool newline)
  {
    if (comment.empty())
    {
      return;
    }
    if (!comment_.empty())
    {
      comment_.push_back('\n');
    }
    else
    {
      is_inline_comment_ = !newline;
    }
    comment_.append(comment);
  }

  void JsonWriterContext::flushComments()
  {
    constexpr std::string_view kCommentPrefix = "//";

    if (comment_.empty())
    {
      return;
    }
    // Append a space unless no field has been written for this object yet.
    if (is_inline_comment_ && has_members_in_scope_)
    {
      stream_.put(' ');
    }
    bool needs_newline = !is_inline_comment_;

    for (auto part : std::views::split(comment_, '\n'))
    {
      const std::string_view part_str(part.begin(), part.end());
      if (needs_newline)
      {
        writeNewline();
      }
      stream_.write(kCommentPrefix.data(), kCommentPrefix.size());
      if (!part_str.empty())
      {
        stream_.put(' ');
        stream_.write(part_str.data(), part_str.size());
      }
      needs_newline = true;
    }
    // Clean-up.
    comment_.clear();
    is_inline_comment_ = false;
  }
}
