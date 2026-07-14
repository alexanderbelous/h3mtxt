#pragma once

#include <algorithm>
#include <array>
#include <cstddef>
#include <span>
#include <stdexcept>
#include <string_view>

namespace h3svg
{
  // A string that uses a fixed-width buffer to store the characters.
  //
  // H3SVG has several places where strings are encoded as a fixed-size array of bytes
  // instead of a length-prefixed string. Only the bytes before the first null terminator
  // ('\0', aka the byte 0x00) are meaningful - the bytes after the first null terminator
  // are ignored by the game and may contain junk values.
  // * If there is no null terminator, the game seems to consider all bytes in the buffer as
  //   meaningful. This class does the same.
  //
  // While it's tempting to represent such strings via std::string, that would contradict the goal
  // of h3mtxt to provide structured access to any byte of the input file: explicitly storing the
  // null terminator and the following junk bytes in std::string makes the API of std::string
  // rather useless. Moreover, std::string has no way to indicate at compile-time the maximum allowed
  // length (i.e. the size of the buffer).
  //
  // The naive solution is to simply represent such strings as std::array<char, N>. However, that
  // doesn't provide a convenient API for manipulating such strings: e.g., the user will have to
  // manually compute the effective length of the string (i.e. the number of characters before the
  // first null terminator).
  //
  // This class is a compromise between the two: while it provides direct access to the underlying
  // buffer, it implements additional functions to simplify string manipulation.
  //
  // \param N - the number of bytes
  template<std::size_t N>
  class FixedLengthString
  {
  public:
    using value_type = char;
    using size_type = std::size_t;
    using difference_type = std::size_t;
    using reference = char&;
    using const_reference = const char&;
    using pointer = char*;
    using const_pointer = const char*;

    // Constructs an empty string.
    constexpr FixedLengthString() noexcept = default;

    // Constructs a FixedLengthString from the input null-terminated string.
    // \param str - input null-terminated string.
    // \throw std::length_error if str.size() > N.
    constexpr FixedLengthString(const char* str);

    // Constructs a FixedLengthString from the input std::string_view.
    // \param str - input std::string_view.
    // \throw std::length_error if str.size() > N.
    constexpr FixedLengthString(std::string_view str);

    // Replaces the contents with the bytes from the input std::string_view.
    // \param str - input std::string_view. If str.size() < N, the function will assign '\0'
    //        to all bytes [str.size(), N) in the buffer.
    // \return *this
    // \throw std::length_error if str.size() > N.
    constexpr FixedLengthString& operator=(std::string_view str);

    // Equality comparsion.
    // \param other - FixedLengthString to compare with.
    // \return true if (*this)[i] == other[i] for each i in [0; N), false otherwise.
    constexpr bool operator==(const FixedLengthString& other) const noexcept = default;

    // \return N.
    static constexpr std::size_t bufferSize() noexcept;

    // \return a mutable std::span into the underlying buffer.
    constexpr std::span<char, N> buffer() noexcept;

    // \return a read-only std::span into the underlying buffer.
    constexpr std::span<const char, N> buffer() const noexcept;

    // \return std::string_view into the underlying buffer,
    //         i.e. std::string_view{ data(), N }
    constexpr std::string_view bufferView() const noexcept;

    // Mutable access to the character by its index.
    // \param n - 0-based index of the character.
    // \return this->data()[n]
    constexpr char& operator[](std::size_t n);

    // Read-only access to the character by its index.
    // \param n - 0-based index of the character.
    // \return this->data()[n]
    constexpr const char& operator[](std::size_t n) const;

    // Mutable access to the character by its index.
    // \param n - 0-based index of the character.
    // \return this->data()[n]
    // \throw std::out_of_range if n >= N
    constexpr char& at(std::size_t n);

    // Mutable access to the character by its index.
    // \param n - 0-based index of the character.
    // \return this->data()[n]
    // \throw std::out_of_range if n >= N
    constexpr const char& at(std::size_t n) const;

    // \return a pointer to the 0th character in the underlying buffer (read-only).
    constexpr char* data() noexcept;

    // \return a pointer to the 0th character in the underlying buffer (mutable).
    constexpr const char* data() const noexcept;

    // \return a std::string_view into the meaningful substring, i.e.
    //         std::string_view{ this->data(), this->size() }
    constexpr operator std::string_view() const noexcept;

    // \return the length of the string, i.e. the number of bytes before the first null terminator,
    //         or N if there is no null terminator.
    constexpr std::size_t size() const noexcept;

    // \return the length of the string, i.e. the number of bytes before the first null terminator,
    //         or N if there is no null terminator.
    constexpr std::size_t length() const noexcept;

    // \return true if the string is empty, false otherwise,
    //         i.e. this->size() == 0
    constexpr bool empty() const noexcept;

    // Clears the contents, assigning '\0' to all bytes in the buffer.
    constexpr void clear() noexcept;

  private:
    // TODO: allocate memory on the heap for large N.
    std::array<char, N> data_ {};
  };

  template<std::size_t N>
  constexpr FixedLengthString<N>::FixedLengthString(const char* str):
    FixedLengthString(std::string_view{ str })
  {}

  template<std::size_t N>
  constexpr FixedLengthString<N>::FixedLengthString(std::string_view str)
  {
    *this = str;
  }

  template<std::size_t N>
  constexpr FixedLengthString<N>& FixedLengthString<N>::operator=(std::string_view str)
  {
    const std::size_t n = str.size();
    if (n > N)
    {
      throw std::length_error("FixedLengthString: the input string is too long.");
    }
    // @str and @data_ may overlap, but in that case it's guaranteed that &str[0] >= &data_[0],
    // so we will be copying to the left.
    // TODO: strictly speaking, it can be possible that &str[0] < &data_[0]:
    //   struct Foo
    //   {
    //     char values[10] {};
    //     FixedLengthString<10> str;
    //   };
    //
    //   Foo foo;
    //   foo.str = std::string_view{ reinterpret_cast<const char*>(&foo) + 5, 10 };
    std::copy_backward(str.begin(), str.begin() + n, data_.begin() + n);
    std::fill(data_.begin() + n, data_.end(), '\0');
    return *this;
  }

  template<std::size_t N>
  static constexpr std::size_t FixedLengthString<N>::bufferSize() noexcept
  {
    return N;
  }

  template<std::size_t N>
  constexpr std::span<char, N> FixedLengthString<N>::buffer() noexcept
  {
    return std::span<char, N>{ data(), N };
  }

  template<std::size_t N>
  constexpr std::span<const char, N> FixedLengthString<N>::buffer() const noexcept
  {
    return std::span<const char, N>{ data(), N };
  }

  template<std::size_t N>
  constexpr std::string_view FixedLengthString<N>::bufferView() const noexcept
  {
    return std::string_view{ data(), N };
  }

  template<std::size_t N>
  constexpr char& FixedLengthString<N>::operator[](std::size_t n)
  {
    return data_[n];
  }

  template<std::size_t N>
  constexpr const char& FixedLengthString<N>::operator[](std::size_t n) const
  {
    return data_[n];
  }

  template<std::size_t N>
  constexpr char& FixedLengthString<N>::at(std::size_t n)
  {
    return data_.at(n);
  }

  template<std::size_t N>
  constexpr const char& FixedLengthString<N>::at(std::size_t n) const
  {
    return data_.at(n);
  }

  template<std::size_t N>
  constexpr char* FixedLengthString<N>::data() noexcept
  {
    return data_.data();
  }

  template<std::size_t N>
  constexpr const char* FixedLengthString<N>::data() const noexcept
  {
    return data_.data();
  }

  template<std::size_t N>
  constexpr FixedLengthString<N>::operator std::string_view() const noexcept
  {
    return std::string_view{ data(), size() };
  }

  template<std::size_t N>
  constexpr std::size_t FixedLengthString<N>::size() const noexcept
  {
    return std::find(data_.begin(), data_.end(), '\0') - data_.begin();
  }

  template<std::size_t N>
  constexpr std::size_t FixedLengthString<N>::length() const noexcept
  {
    return size();
  }

  template<std::size_t N>
  constexpr bool FixedLengthString<N>::empty() const noexcept
  {
    return size() == 0;
  }

  template<std::size_t N>
  constexpr void FixedLengthString<N>::clear() noexcept
  {
    data_.fill('\0');
  }
}
