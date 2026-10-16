#pragma once

#include <h3mtxt/SavedGame/SavedGameFwd.h>
#include <h3mtxt/SavedGame/ObjectProperties.h>

#include <array>
#include <cstdint>

namespace h3svg
{
  // Stores the 4 bytes representing the simple properties of an object on the Adventure Map.
  //
  // This is used in h3svg::Tile::object_properties and h3svg::Hero::unknown1.
  //
  // Note that, unlike h3m::ObjectPropertiesVariant, this class is not type-safe: it does not
  // store the type of the Adventure Map object.
  struct ObjectPropertiesData
  {
    // Deserializes ObjectProperties<T> from the stored bytes.
    //
    // TODO: move to H3SVGReader. This will require changes in h3svg::Tile and h3svg::Hero, so that
    // object properties are stored as a union of ObjectProperties<T> rather than simply 4 bytes.
    // \return ObjectProperties<T> represented by this->data.
    template<ObjectPropertiesType T>
    constexpr ObjectProperties<T> get() const
    {
      static_assert(false, "Not implemented.");
      return {};
    }

    // Updates the stored bytes to match the binary representation of the given ObjectProperties<T>.
    //
    // TODO: move to H3SVGWriter. This will require changes in h3svg::Tile and h3svg::Hero, so that
    // object properties are stored as a union of ObjectProperties<T> rather than simply 4 bytes.
    // \param properties - input ObjectProperties<T>.
    template<ObjectPropertiesType T>
    constexpr void set(const ObjectProperties<T>& properties)
    {
      static_assert(false, "Not implemented.");
    }

    // Raw access to the bytes.
    std::array<std::uint8_t, 4> data {};
  };

  // ==================== None ====================
  template<>
  constexpr ObjectProperties<ObjectPropertiesType::None> ObjectPropertiesData::get() const
  {
    std::array<std::byte, 4> bytes{};
    for (std::size_t i = 0; i < 4; ++i)
    {
      bytes[i] = static_cast<std::byte>(data[i]);
    }
    return ObjectProperties<ObjectPropertiesType::None>{
      .reserved{ bytes }
    };
  }

  template<>
  constexpr void ObjectPropertiesData::set(const ObjectProperties<ObjectPropertiesType::None>& properties)
  {
    for (std::size_t i = 0; i < 4; ++i)
    {
      data[i] = static_cast<std::uint8_t>(properties.reserved[i]);
    }
  }
}
