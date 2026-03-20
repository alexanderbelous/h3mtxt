#pragma once

#include <algorithm>
#include <cstddef>
#include <memory>
#include <span>
#include <stdexcept>
#include <type_traits>

namespace h3m
{
  namespace Detail_NS
  {
    // Storage for ReservedData.
    template<std::size_t NumBytes, class Enable = void>
    class ReservedDataStorage
    {
    public:
      // Constructs an implicit array.
      constexpr ReservedDataStorage() noexcept = default;

      // Copy constructor.
      ReservedDataStorage(const ReservedDataStorage& other):
        data_(other.cloneData())
      {}

      // Move constructor.
      constexpr ReservedDataStorage(ReservedDataStorage&& other) noexcept = default;

      // Copy assignment operator.
      ReservedDataStorage& operator=(const ReservedDataStorage& other)
      {
        if (!other.data_)
        {
          data_ = nullptr;
        }
        else
        {
          if (!data_)
          {
            data_ = std::make_unique_for_overwrite<std::byte[]>(NumBytes);
          }
          std::copy_n(data_.get(), NumBytes, other.data_.get());
        }
        return *this;
      }

      // Move assignment operator.
      constexpr ReservedDataStorage& operator=(ReservedDataStorage&& other) noexcept = default;

      // Destructor.
      ~ReservedDataStorage() = default;

      // \return a pointer to the stored array of NumBytes elements,
      //         or nullptr if the stored elements are is implicitly 0s.
      constexpr std::byte* data() noexcept
      {
        return data_.get();
      }

      constexpr const std::byte* data() const noexcept
      {
        return data_.get();
      }

      // Allocates data for the array if it hasn't been allocated yet.
      // data() will return a nonzero pointer after this call.
      void makeExplicit()
      {
        if (!data_)
        {
          data_ = std::make_unique<std::byte[]>(NumBytes);
        }
      }

    private:
      std::unique_ptr<std::byte[]> cloneData() const
      {
        std::unique_ptr<std::byte[]> new_data;
        if (data_)
        {
          new_data = std::make_unique_for_overwrite<std::byte[]>(NumBytes);
          std::copy_n(data_.get(), NumBytes, new_data.get());
        }
        return new_data;
      }

      // The stored bytes. Nullptr means that all bytes are 0.
      std::unique_ptr<std::byte[]> data_;
    };

    // Partial specialization for the case when NumBytes <= sizeof(std::byte*).
    template<std::size_t NumBytes>
    class ReservedDataStorage<NumBytes, std::enable_if_t<NumBytes <= sizeof(std::byte*)>>
    {
    public:
      // \return a pointer to the stored array of NumBytes elements.
      constexpr std::byte* data() noexcept
      {
        return data_.data();
      }

      // \return a pointer to the stored array of NumBytes elements.
      constexpr const std::byte* data() const noexcept
      {
        return data_.data();
      }

      // No-op. The array is always explicit in this specialization.
      constexpr void makeExplicit() noexcept
      {
      }

    private:
      std::array<std::byte, NumBytes> data_ {};
    };

    // Checks if all bytes in the array are 0.
    // \param data - input array.
    // \return true if all bytes in @data are 0, false otherwise.
    constexpr bool isAllZeros(std::span<const std::byte> data)
    {
      const std::byte* const first = data.data();
      const std::byte* const last = first + data.size();
      return std::all_of(first, last, [](std::byte value) noexcept { return value == std::byte{ 0 }; });
    }
  }

  // Byte array optimized for the special case when all elements are 0.
  //
  // H3M file format has several "reserved" byte array fields which should always be 0.
  // It is somewhat inefficient to always allocate memory for such fields, so
  // this class avoids explicitly storing such arrays by default. You can still explicitly
  // allocate them and write whatever you want there.
  template<std::size_t NumBytes>
  class ReservedData
  {
  public:
    // Constructs an array with all elements being implicitly 0.
    constexpr ReservedData() noexcept = default;

    // Constructs an explicit array.
    // \param data - values to assign to the elements.
    explicit ReservedData(const std::array<std::byte, NumBytes>& data);

    // \return NumBytes.
    constexpr std::size_t size() const noexcept;

    // Gets the value of the specified element.
    //
    // No bounds checking is performed; the behavior is undefined if @index >= NumBytes.
    // \param index - 0-based index of the element.
    // \return the value of the byte at @index.
    constexpr std::byte operator[](std::size_t index) const;

    // Gets the value of the specified element.
    // \param index - 0-based index of the element.
    // \return the value of the byte at @index.
    // \throw std::out_of_range if @index >= NumBytes.
    constexpr std::byte at(std::size_t index) const;

    // \return a pointer to the stored array of NumBytes elements,
    //         or nullptr if !isExplicit().
    constexpr std::byte* data() noexcept;

    // \return a pointer to the stored array of NumBytes elements,
    //         or nullptr if !isExplicit().
    constexpr const std::byte* data() const noexcept;

    // \return true if the data is explicit, false otherwise.
    constexpr bool isExplicit() const noexcept;

    // Allocates memory for the elements, if needed.
    // isExplicit() will return true after this call.
    void makeExplicit();

  private:
    Detail_NS::ReservedDataStorage<NumBytes> storage_;
  };

  template<std::size_t NumBytes>
  ReservedData<NumBytes>::ReservedData(const std::array<std::byte, NumBytes>& data)
  {
    storage_.makeExplicit();
    std::copy_n(data.data(), NumBytes, storage_.data());
  }

  template<std::size_t NumBytes>
  constexpr std::size_t ReservedData<NumBytes>::size() const noexcept
  {
    return NumBytes;
  }

  template<std::size_t NumBytes>
  constexpr std::byte ReservedData<NumBytes>::operator[](std::size_t index) const
  {
    const std::byte* const values = data();
    return values ? values[index] : std::byte{0};
  }

  template<std::size_t NumBytes>
  constexpr std::byte ReservedData<NumBytes>::at(std::size_t index) const
  {
    if (index >= NumBytes)
    {
      throw std::out_of_range("ReservedData::at(): index is out of range.");
    }
    return (*this)[index];
  }

  template<std::size_t NumBytes>
  constexpr std::byte* ReservedData<NumBytes>::data() noexcept
  {
    return storage_.data();
  }

  template<std::size_t NumBytes>
  constexpr const std::byte* ReservedData<NumBytes>::data() const noexcept
  {
    return storage_.data();
  }

  template<std::size_t NumBytes>
  constexpr bool ReservedData<NumBytes>::isExplicit() const noexcept
  {
    return storage_.data() != nullptr;
  }

  template<std::size_t NumBytes>
  void ReservedData<NumBytes>::makeExplicit()
  {
    storage_.makeExplicit();
  }
}
