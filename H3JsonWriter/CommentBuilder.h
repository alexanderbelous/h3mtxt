#pragma once

#include <cstdint>
#include <string>
#include <string_view>
#include <type_traits>
#include <utility>

namespace h3m::H3JsonWriter_NS
{
  // Lame alternative for std::format. Not using std::format here because it still causes bloat.
  class CommentBuilder
  {
  public:
    // Lightweight class capable of holding std::string_view, std::uintmax_t or std::intmax_t.
    class StringOrInteger
    {
    public:
      // Constructs an object representing an empty string_view.
      constexpr StringOrInteger() noexcept = default;

      // Constructs an object representing a signed integer.
      template<class T, std::enable_if_t<std::is_integral_v<std::remove_cvref_t<T>> &&
                                         std::is_signed_v<std::remove_cvref_t<T>>, bool> = true>
      constexpr StringOrInteger(const T& value) noexcept:
        str_length_or_tag_{ kIntTag },
        data_{ .int_value = value }
      {}

      // Constructs an object representing an unsigned integer.
      template<class T, std::enable_if_t<std::is_integral_v<std::remove_cvref_t<T>> &&
                                         std::is_unsigned_v<std::remove_cvref_t<T>>, bool> = true>
      constexpr StringOrInteger(const T& value) noexcept:
        str_length_or_tag_{ kUIntTag },
        data_{ .uint_value = value }
      {}

      // Constructs an object representing a string_view.
      template<class T, std::enable_if_t<std::is_convertible_v<const T&, std::string_view>, bool> = true>
      constexpr StringOrInteger(const T& value) noexcept
      {
        const std::string_view value_str{ value };
        str_length_or_tag_ = value_str.size();
        data_.str_data = value_str.data();
      }

      void printTo(std::string& dest) const
      {
        switch (str_length_or_tag_)
        {
        case kUIntTag:
          dest.append(std::to_string(data_.uint_value));
          break;
        case kIntTag:
          dest.append(std::to_string(data_.int_value));
          break;
        default:
          dest.append(std::string_view{ data_.str_data, str_length_or_tag_ });
          break;
        }
      }

    private:
      static constexpr std::size_t kUIntTag = static_cast<std::size_t>(-1);
      static constexpr std::size_t kIntTag = static_cast<std::size_t>(-2);

      // The length of the string or 2 special "tags": kUIntTag or kIntTag
      std::size_t str_length_or_tag_ = 0;
      // Pointer to the string data or the value of the integer.
      union
      {
        const char* str_data = nullptr;
        std::uintmax_t uint_value;
        std::intmax_t int_value;
      } data_;
    };

    CommentBuilder& operator<<(StringOrInteger value)
    {
      value.printTo(comment_);
      return *this;
    }

    // Constructs a comment from the input values.
    // First discards the current contents, then appends the values.
    // \return a string_view to the constructed comment.
    std::string_view build(std::initializer_list<StringOrInteger> args)
    {
      clear();
      for (const StringOrInteger& arg : args)
      {
        arg.printTo(comment_);
      }
      return comment_;
    }

    void clear()
    {
      comment_.clear();
    }

    std::string_view view() const
    {
      return comment_;
    }

    std::string str()
    {
      return std::move(comment_);
    }

  private:
    std::string comment_;
  };
}
