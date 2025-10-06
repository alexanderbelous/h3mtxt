#include <h3mtxt/H3JsonWriter/LocalizedStringsReader.h>

#include <h3mtxt/H3JsonWriter/LocalizedStringId.h>

#include <istream>

namespace h3m::H3JsonWriter_NS
{
  namespace
  {
    // Reads a single line from the input stream.
    // The function supports 3 line endings: "\n", "\r\n" and "\r".
    std::istream& safeGetline(std::istream& stream, std::string& output)
    {
      output.clear();

      // The characters in the stream are read one-by-one using a std::streambuf.
      // That is faster than reading them one-by-one using the std::istream.
      // Code that uses streambuf this way must be guarded by a sentry object.
      // The sentry object performs various tasks,
      // such as thread synchronization and updating the stream state.

      std::istream::sentry se(stream, true);
      std::streambuf* sb = stream.rdbuf();

      for (;;)
      {
        int c = sb->sbumpc();
        switch (c)
        {
        case '\n':
          return stream;
        case '\r':
          // If the line ends with "\r\n", consume both.
          if (sb->sgetc() == '\n')
          {
            sb->sbumpc();
          }
          return stream;
        case std::streambuf::traits_type::eof():
          stream.setstate(std::ios::eofbit);
          // std::getline() ignores an empty last line, so should we.
          if (output.empty())
          {
            stream.setstate(std::ios::failbit);
          }
          return stream;
        default:
          output.push_back(static_cast<char>(c));
          break;
        }
      }
    }
  }

  LocalizedStringsData readLocalizedStringsFromStream(std::istream& stream)
  {
    if (!stream)
    {
      throw std::runtime_error("readLocalizedStringsFromStream(): failed to open the file.");
    }
    LocalizedStringsData data;
    std::string line;
    for (std::size_t i = 0; i < kNumLocalizedStringIds; ++i)
    {
      safeGetline(stream, line);
      // If an I/O error happens, throw an exception.
      if (stream.bad())
      {
        throw std::runtime_error("readLocalizedStringsFromStream(): error while reading the file.");
      }
      // Put the parsed string into LocalizedStringsData on success.
      if (!stream.fail())
      {
        data.set(static_cast<LocalizedStringId>(i), line);
      }
      // Break if EOF has been reached or if failed to read the line.
      // EOF is fine - the resource file may contain fewer than kNumLocalizedStringIds lines.
      if (!stream.good())
      {
        break;
      }
    }
    return data;
  }
}
