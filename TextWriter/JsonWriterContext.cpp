#include <h3mtxt/TextWriter/JsonWriterContext.h>

#include <algorithm>
#include <iterator>
#include <ostream>
#include <ranges>

namespace Util_NS
{
  namespace Detail_NS
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

    void JsonWriterContext::writeComment(std::string_view comment)
    {
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

      if (comment.empty())
      {
        write_comment_part(comment);
        return;
      }
      for (auto part : std::views::split(comment, '\n'))
      {
        const std::string_view part_str(part.begin(), part.end());
        write_comment_part(part_str);
      }
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
  }
}
