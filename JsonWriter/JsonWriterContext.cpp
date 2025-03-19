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

  void JsonWriterContext::writeBool(bool value)
  {
    static constexpr std::string_view kFalseStr = "false";
    static constexpr std::string_view kTrueStr = "true";

    writeNewlineIfNeeded();
    const std::string_view str = value ? kTrueStr : kFalseStr;
    stream_.write(str.data(), str.size());
  }

  void JsonWriterContext::writeInt(std::intmax_t value)
  {
    writeNewlineIfNeeded();
    stream_ << value;
  }

  void JsonWriterContext::writeUInt(std::uintmax_t value)
  {
    writeNewlineIfNeeded();
    stream_ << value;
  }

  void JsonWriterContext::writeString(std::string_view value)
  {
    writeNewlineIfNeeded();
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
  }

  void JsonWriterContext::writeNewlineIfNeeded()
  {
    if (needs_newline_)
    {
      stream_.put('\n');
      std::fill_n(std::ostream_iterator<char>(stream_), indent_, ' ');
      needs_newline_ = false;
    }
  }

  void JsonWriterContext::beginAggregate(char bracket)
  {
    writeNewlineIfNeeded();
    stream_.put(bracket);
    indent_ += 2;
    needs_newline_ = true;
    has_members_in_scope_ = false;
    has_comments_in_scope_ = false;
  }

  void JsonWriterContext::endAggregate(char bracket)
  {
    flushComments();
    // Sanity check.
    if (indent_ >= 2)
    {
      indent_ -= 2;
    }
    writeNewlineIfNeeded();
    stream_.put(bracket);
    // We've just finished writing an object/array, so the outer aggregate (whether it's an object or an array)
    // has at least 1 element.
    has_members_in_scope_ = true;
  }

  void JsonWriterContext::lazyWriteComment(std::string_view comment, bool newline)
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
    if (comment_.empty())
    {
      return;
    }
    // Append a space unless no field has been written for this object yet.
    if (is_inline_comment_ && has_members_in_scope_)
    {
      stream_.put(' ');
      // Instruct JsonWriterContext not to write a newline character.
      needs_newline_ = false;
    }
    // Writes a single comment line.
    // \param part - comment text. @part should not contain newline characters.
    const auto write_comment_part = [this](std::string_view part)
      {
        constexpr std::string_view kCommentPrefix = "//";
        writeNewlineIfNeeded();
        stream_.write(kCommentPrefix.data(), kCommentPrefix.size());
        if (!part.empty())
        {
          stream_.put(' ');
          stream_.write(part.data(), part.size());
        }
        needs_newline_ = true;
      };

    if (comment_.empty())
    {
      write_comment_part(comment_);
      return;
    }
    for (auto part : std::views::split(comment_, '\n'))
    {
      const std::string_view part_str(part.begin(), part.end());
      write_comment_part(part_str);
    }
    // Clean-up.
    comment_.clear();
    is_inline_comment_ = false;
    has_comments_in_scope_ = true;
  }
}
