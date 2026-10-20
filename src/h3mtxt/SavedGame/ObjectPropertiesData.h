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

  namespace Detail_NS
  {
    // Helper class for deserializing ObjectProperties<T>.
    //
    // In H3SVG ObjectProperties<T> is always serialized as 4 bytes; the game often uses bit packing
    // to fit the data in these 4 bytes. Using masks and arithmetic shifts is prone to errors; this
    // class facilitates deserialization by treating the input 4 bytes as a stream of bits and providing
    // functions for reading fixed-size bit fields from this stream.
    class BitsReader
    {
    public:
      // Constructs a class for reading bits from the given bytes.
      // \param data - the input 4 bytes. LSB of data[0] will be the first bit to read,
      //        MSB of data[3] will be the last bit to read.
      explicit constexpr BitsReader(std::array<std::uint8_t, 4> data) noexcept:
        data_as_int_{ (std::uint32_t(data[3]) << 24) |
                      (std::uint32_t(data[2]) << 16) |
                      (std::uint32_t(data[1]) << 8) |
                       std::uint32_t(data[0]) }
      {}

      // Reads an integer from the underlying stream.
      // \param T - the output integer type.
      // \param NumBits - the number of bits to read from the stream.
      // \return the deserialized integer.
      template<class T, std::size_t NumBits>
      constexpr T readInt()
      {
        return static_cast<T>(readImpl(NumBits));
      }

      // Reads a single bit from the underlying stream.
      // \return the deserialized bit.
      constexpr bool readBit()
      {
        return static_cast<bool>(readImpl(1));
      }

      // Reads an enumeration value from the underlying stream.
      // Same as static_cast<T>(readInt<std::underlying_type_t<T>, NumBits>()).
      // \param T - the output enumeration type.
      // \param NumBits - the number of bits to read from the stream.
      // \return the deserialized enumeration value.
      template<class T, std::size_t NumBits>
      constexpr T readEnum()
      {
        return static_cast<T>(readImpl(NumBits));
      }

    private:
      // Reads the specified number of bits from the underlying stream.
      // \param num_bits - the number of bits to read.
      // \return the deserialized bits as a 32-bit integer.
      constexpr std::uint32_t readImpl(std::size_t num_bits)
      {
        // Edge case: num_bits == 32.
        if (num_bits >= 32)
        {
          // Ideally, we should also assign 0 to data_as_int_. However, reading more
          // bits would be an error anyway, so screw it.
          return data_as_int_;
        }
        else
        {
          constexpr std::uint32_t kAllOnes = static_cast<std::uint32_t>(-1);
          // Mask with bits [0; num_bits) set to 1 and the rest set to 0.
          const std::uint32_t mask = static_cast<std::uint32_t>(~(kAllOnes << num_bits));
          const std::uint32_t result = data_as_int_ & mask;
          data_as_int_ >>= num_bits;
          return result;
        }
      }

      // Input bits.
      // The bits are stored as a 32-bit integer (with LSB being the first bit to read).
      // The class doesn't keep track of the number of consumed bits; instead, the bits
      // get shifted right when consumed.
      std::uint32_t data_as_int_ = 0;
    };
  }

  template<>
  constexpr ObjectProperties<ObjectPropertiesType::None> ObjectPropertiesData::get() const
  {
    return ObjectProperties<ObjectPropertiesType::None>{ .reserved = data };
  }

  template<>
  constexpr void ObjectPropertiesData::set(const ObjectProperties<ObjectPropertiesType::None>& properties)
  {
    data = properties.reserved;
  }

  template<>
  constexpr ObjectProperties<ObjectPropertiesType::BlackMarket> ObjectPropertiesData::get() const
  {
    Detail_NS::BitsReader reader{ data };
    return ObjectProperties<ObjectPropertiesType::BlackMarket>{
      .index = reader.readInt<std::int32_t, 32>()
    };
  }

  template<>
  constexpr void ObjectPropertiesData::set(const ObjectProperties<ObjectPropertiesType::BlackMarket>& properties)
  {
    for (std::size_t i = 0; i < 4; ++i)
    {
      data[i] = static_cast<std::uint8_t>((static_cast<std::uint32_t>(properties.index) >> (i * 8)) & 0xFFu);
    }
  }

  template<>
  constexpr ObjectProperties<ObjectPropertiesType::Campfire> ObjectPropertiesData::get() const
  {
    Detail_NS::BitsReader reader{ data };
    return {
      .resource_type = reader.readEnum<ResourceType, 4>(),
      .quantity = reader.readInt<std::uint8_t, 4>(),
      .reserved = { reader.readInt<std::uint8_t, 8>(),
                    reader.readInt<std::uint8_t, 8>(),
                    reader.readInt<std::uint8_t, 8>() }
    };
  }

  template<>
  constexpr void ObjectPropertiesData::set(const ObjectProperties<ObjectPropertiesType::Campfire>& properties)
  {
    data[0] = (properties.quantity << 4) | static_cast<std::uint8_t>(properties.resource_type);
    data[1] = properties.reserved[0];
    data[2] = properties.reserved[1];
    data[3] = properties.reserved[2];
  }

  template<>
  constexpr ObjectProperties<ObjectPropertiesType::CreatureBank> ObjectPropertiesData::get() const
  {
    Detail_NS::BitsReader reader{ data };
    return {
      .reserved1 = reader.readInt<std::int8_t, 5>(),
      .visited_by { reader.readInt<std::uint8_t, 8>() },
      .index = reader.readInt<std::uint16_t, 14>(),
      .reserved2 = reader.readInt<std::int8_t, 5>()
    };
  }

  template<>
  constexpr ObjectProperties<ObjectPropertiesType::Dwelling> ObjectPropertiesData::get() const
  {
    Detail_NS::BitsReader reader{ data };
    return {
      .index = reader.readInt<std::uint32_t, 32>()
    };
  }

  template<>
  constexpr ObjectProperties<ObjectPropertiesType::Corpse> ObjectPropertiesData::get() const
  {
    Detail_NS::BitsReader reader{ data };
    return {
      .id = reader.readInt<std::uint16_t, 5>(),
      .reserved1 = reader.readInt<std::uint16_t, 1>(),
      .artifact = reader.readEnum<ArtifactType, 10>(),
      .is_lootable = reader.readInt<std::uint16_t, 1>(),
      .reserved2 = reader.readInt<std::int16_t, 15>()
    };
  }

  template<>
  constexpr ObjectProperties<ObjectPropertiesType::Floatsam> ObjectPropertiesData::get() const
  {
    Detail_NS::BitsReader reader{ data };
    return {
      .content = reader.readEnum<ObjectProperties<ObjectPropertiesType::Floatsam>::FloatsamContentType, 32>()
    };
  }

  template<>
  constexpr ObjectProperties<ObjectPropertiesType::FountainOfFortune> ObjectPropertiesData::get() const
  {
    Detail_NS::BitsReader reader{ data };
    return {
      .reserved1 = reader.readInt<std::int32_t, 5>(),
      .reserved2 = reader.readInt<std::int32_t, 8>(),
      .luck_bonus = reader.readInt<std::int32_t, 4>(),
      .reserved3 = reader.readInt<std::int32_t, 15>()
    };
  }

  template<>
  constexpr ObjectProperties<ObjectPropertiesType::Garrison> ObjectPropertiesData::get() const
  {
    Detail_NS::BitsReader reader{ data };
    return {
      .index = reader.readInt<std::uint32_t, 32>()
    };
  }

  template<>
  constexpr ObjectProperties<ObjectPropertiesType::LeanTo> ObjectPropertiesData::get() const
  {
    Detail_NS::BitsReader reader{ data };
    return {
      .index = reader.readInt<std::uint8_t, 5>(),
      .reserved1 = reader.readInt<std::uint8_t, 1>(),
      .quantity = reader.readInt<std::uint8_t, 4>(),
      .resource_type = reader.readInt<ResourceType, 4>(),
      .reserved2 = reader.readInt<std::int32_t, 18>()
    };
  }

  template<>
  constexpr ObjectProperties<ObjectPropertiesType::SeersHut> ObjectPropertiesData::get() const
  {
    Detail_NS::BitsReader reader{ data };
    return {
      .index = reader.readInt<std::uint32_t, 32>()
    };
  }

  template<>
  constexpr ObjectProperties<ObjectPropertiesType::Shrine> ObjectPropertiesData::get() const
  {
    ObjectProperties<ObjectPropertiesType::Shrine> properties;
    Detail_NS::BitsReader reader{ data };
    properties.reserved1 = reader.readInt<std::int16_t, 5>();
    properties.visited_by.bitset.data[0] = reader.readInt<std::uint8_t, 8>();
    properties.spell = reader.readInt<std::int16_t, 10>();
    properties.reserved2 = reader.readInt<std::int16_t, 9>();
    return properties;
  }

  template<>
  constexpr ObjectProperties<ObjectPropertiesType::Sign> ObjectPropertiesData::get() const
  {
    Detail_NS::BitsReader reader{ data };
    return {
      .index = reader.readInt<std::uint32_t, 32>()
    };
  }

  template<>
  constexpr ObjectProperties<ObjectPropertiesType::University> ObjectPropertiesData::get() const
  {
    Detail_NS::BitsReader reader{ data };
    return {
      .reserved1 = reader.readInt<std::int32_t, 5>(),
      .reserved2 = reader.readInt<std::int32_t, 8>(),
      .index = reader.readInt<std::int32_t, 12>(),
      .reserved3 = reader.readInt<std::int32_t, 7>(),
    };
  }

  template<>
  constexpr ObjectProperties<ObjectPropertiesType::WitchHut> ObjectPropertiesData::get() const
  {
    ObjectProperties<ObjectPropertiesType::WitchHut> properties;
    Detail_NS::BitsReader reader{ data };
    properties.reserved1 = reader.readInt<std::uint8_t, 5>();
    properties.visited_by.bitset.data[0] = reader.readInt<std::uint8_t, 8>();
    properties.skill = reader.readEnum<SecondarySkillType, 8>();
    properties.reserved2 = reader.readInt<std::uint16_t, 11>();
    return properties;
  }
}
