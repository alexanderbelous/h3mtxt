#pragma once

#include <h3mtxt/Map/Constants/ResourceType.h>

#include <cstdint>
#include <stdexcept>

namespace h3m
{
  // Bit array storing a bit for each resource type.
  //
  // AFAIU, this is only used in ObjectDetailsData<MetaObjectType::ABANDONED_MINE>.
  struct ResourcesBitmask
  {
  private:
    // Constructs a bitmask for the given resource type.
    // \param resource_type - resource type for which to construct a bitmask.
    // \return an 8-bit unsigned integer with all bits except int(resource_type) set to 0,
    //         or 0 if int(resource_type) >= 8.
    static constexpr std::byte getBitmask(ResourceType resource_type) noexcept;

  public:
    // Checks if the bit is set for the specified resource type.
    // \param resource_type - resource type to check.
    // \return true if the bit is set in the bitmask for @resource_type, false otherwise.
    constexpr bool operator[](ResourceType resource_type) const;

    // Sets the value of the bit for the specified resource type.
    // \param resource_type - resource type for which to set the bit.
    // \param value - value to set.
    constexpr void set(ResourceType resource_type, bool value);

    std::byte bitset {};
  };

  constexpr std::byte ResourcesBitmask::getBitmask(ResourceType resource_type) noexcept
  {
    const auto bit_index = static_cast<std::underlying_type_t<ResourceType>>(resource_type);
    if (bit_index >= 8)
    {
      return std::byte{0};
    }
    return std::byte{1} << bit_index;
  }

  constexpr bool ResourcesBitmask::operator[](ResourceType resource_type) const
  {
    const std::byte mask = getBitmask(resource_type);
    if (mask == std::byte{0})
    {
      throw std::out_of_range("ResourcesBitmask::operator[](): resource_type is out of range.");
    }
    return (bitset & mask) != std::byte{0};
  }

  constexpr void ResourcesBitmask::set(ResourceType resource_type, bool value)
  {
    const std::byte mask = getBitmask(resource_type);
    if (mask == std::byte{0})
    {
      throw std::out_of_range("ResourcesBitmask::set(): resource_type is out of range.");
    }
    if (value)
    {
      bitset |= mask;
    }
    else
    {
      bitset &= (~mask);
    }
  }
}
