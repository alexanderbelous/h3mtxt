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
  class FixedWidthString
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
    constexpr FixedWidthString() noexcept = default;

    // Constructs a FixedWidthString from the input null-terminated string.
    // \param str - input null-terminated string.
    // \throw std::length_error if str.size() > N.
    constexpr FixedWidthString(const char* str);

    // Constructs a FixedWidthString from the input std::string_view.
    // \param str - input std::string_view.
    // \throw std::length_error if str.size() > N.
    constexpr FixedWidthString(std::string_view str);

    // Replaces the contents with the bytes from the input std::string_view.
    // \param str - input std::string_view. If str.size() < N, the function will assign '\0'
    //        to all bytes [str.size(), N) in the buffer.
    // \return *this
    // \throw std::length_error if str.size() > N.
    constexpr FixedWidthString& operator=(std::string_view str);

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
  constexpr FixedWidthString<N>::FixedWidthString(const char* str):
    FixedWidthString(std::string_view{ str })
  {}

  template<std::size_t N>
  constexpr FixedWidthString<N>::FixedWidthString(std::string_view str)
  {
    *this = str;
  }

  template<std::size_t N>
  constexpr FixedWidthString<N>& FixedWidthString<N>::operator=(std::string_view str)
  {
    if (str.size() > N)
    {
      throw std::length_error("FixedWidthString: the input string is too long.");
    }
    std::fill(std::copy(str.begin(), str.end(), data_.begin()),
              data_.end(),
              '\0');
    return *this;
  }

  template<std::size_t N>
  static constexpr std::size_t FixedWidthString<N>::bufferSize() noexcept
  {
    return N;
  }

  template<std::size_t N>
  constexpr std::span<char, N> FixedWidthString<N>::buffer() noexcept
  {
    return std::span<char, N>{ data(), N };
  }

  template<std::size_t N>
  constexpr std::span<const char, N> FixedWidthString<N>::buffer() const noexcept
  {
    return std::span<const char, N>{ data(), N };
  }

  template<std::size_t N>
  constexpr std::string_view FixedWidthString<N>::bufferView() const noexcept
  {
    return std::string_view{ data(), N };
  }

  template<std::size_t N>
  constexpr char& FixedWidthString<N>::operator[](std::size_t n)
  {
    return data_[n];
  }

  template<std::size_t N>
  constexpr const char& FixedWidthString<N>::operator[](std::size_t n) const
  {
    return data_[n];
  }

  template<std::size_t N>
  constexpr char& FixedWidthString<N>::at(std::size_t n)
  {
    return data_.at(n);
  }

  template<std::size_t N>
  constexpr const char& FixedWidthString<N>::at(std::size_t n) const
  {
    return data_.at(n);
  }

  template<std::size_t N>
  constexpr char* FixedWidthString<N>::data() noexcept
  {
    return data_.data();
  }

  template<std::size_t N>
  constexpr const char* FixedWidthString<N>::data() const noexcept
  {
    return data_.data();
  }

  template<std::size_t N>
  constexpr FixedWidthString<N>::operator std::string_view() const noexcept
  {
    return std::string_view{ data(), size() };
  }

  template<std::size_t N>
  constexpr std::size_t FixedWidthString<N>::size() const noexcept
  {
    return std::find(data_.begin(), data_.end(), '\0') - data_.begin();
  }

  template<std::size_t N>
  constexpr std::size_t FixedWidthString<N>::length() const noexcept
  {
    return size();
  }

  template<std::size_t N>
  constexpr bool FixedWidthString<N>::empty() const noexcept
  {
    return size() == 0;
  }

  template<std::size_t N>
  constexpr void FixedWidthString<N>::clear() noexcept
  {
    data_.fill('\0');
  }
}
