#pragma once

#include <sstream>
#include <string>
#include <string_view>
#include <utility>

namespace h3m::H3JsonWriter_NS
{
  // Lame alternative for std::format. Not using std::format here because it still causes bloat.
  class CommentBuilder
  {
  public:
    // Appends a value to the comment.
    template<class T>
    CommentBuilder& operator<<(T&& value)
    {
      stream_ << value;
      return *this;
    }

    // Constructs a comment from the input values.
    // First discards the current contents, then appends the values.
    // \return a string_view to the constructed comment.
    template<class... Args>
    std::string_view build(Args&&... args)
    {
      clear();
      const char kUnused[] = { ((void)(stream_ << std::forward<Args>(args)), char(0))... };
      return stream_.view();
    }

    void clear()
    {
      // Replace the contents with an empty string.
      const std::string kEmptyString;
      stream_.str(kEmptyString);
      // Clear state flags.
      stream_.clear();
    }

    std::string_view view()
    {
      return stream_.view();
    }

    std::string str()
    {
      return std::move(stream_).str();
    }

  private:
    std::ostringstream stream_;
  };
}
