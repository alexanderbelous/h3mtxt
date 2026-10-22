#include <h3mtxt/H3Reader/H3SVGReader/H3SVGReader.h>

#include <h3mtxt/Map/Utils/SwitchStatement.h>
#include <h3mtxt/SavedGame/ObjectProperties.h>
#include <h3mtxt/SavedGame/ObjectPropertiesVariant.h>

#include <cstddef>
#include <span>

namespace h3svg
{
  namespace
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
      explicit constexpr BitsReader(std::span<const std::byte, 4> data) noexcept:
        data_as_int_{ (static_cast<std::uint32_t>(data[3]) << 24) |
                      (static_cast<std::uint32_t>(data[2]) << 16) |
                      (static_cast<std::uint32_t>(data[1]) << 8) |
                       static_cast<std::uint32_t>(data[0]) }
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

    class ObjectPropertiesReader : private BitsReader
    {
    public:
      template<ObjectPropertiesType T>
      static constexpr ObjectProperties<T> parse(std::span<const std::byte, 4> data)
      {
        return ObjectPropertiesReader{ data }.read<T>();
      }

    private:
      explicit constexpr ObjectPropertiesReader(std::span<const std::byte, 4> data):
        BitsReader{ data }
      {}

      template<ObjectPropertiesType T>
      constexpr ObjectProperties<T> read()
      {
        static_assert(false, "Not implemented.");
      }
    };

    template<>
    constexpr ObjectProperties<ObjectPropertiesType::None> ObjectPropertiesReader::read()
    {
      return {
        .reserved = {
          readInt<std::uint8_t, 8>(),
          readInt<std::uint8_t, 8>(),
          readInt<std::uint8_t, 8>(),
          readInt<std::uint8_t, 8>()
        }
      };
    }

    template<>
    constexpr ObjectProperties<ObjectPropertiesType::BlackMarket> ObjectPropertiesReader::read()
    {
      return { .index = readInt<std::int32_t, 32>() };
    }

    template<>
    constexpr ObjectProperties<ObjectPropertiesType::Campfire> ObjectPropertiesReader::read()
    {
      return {
        .resource_type = readEnum<ResourceType, 4>(),
        .quantity = readInt<std::uint8_t, 4>(),
        .reserved = { readInt<std::uint8_t, 8>(),
                      readInt<std::uint8_t, 8>(),
                      readInt<std::uint8_t, 8>() }
      };
    }

    template<>
    constexpr ObjectProperties<ObjectPropertiesType::CreatureBank> ObjectPropertiesReader::read()
    {
      return {
        .reserved1 = readInt<std::int8_t, 5>(),
        .visited_by { readInt<std::uint8_t, 8>() },
        .index = readInt<std::uint16_t, 14>(),
        .reserved2 = readInt<std::int8_t, 5>()
      };
    }

    template<>
    constexpr ObjectProperties<ObjectPropertiesType::Dwelling> ObjectPropertiesReader::read()
    {
      return { .index = readInt<std::uint32_t, 32>() };
    }

    template<>
    constexpr ObjectProperties<ObjectPropertiesType::Corpse> ObjectPropertiesReader::read()
    {
      return {
        .id = readInt<std::uint16_t, 5>(),
        .reserved1 = readInt<std::uint16_t, 1>(),
        .artifact = readEnum<ArtifactType, 10>(),
        .is_lootable = readInt<std::uint16_t, 1>(),
        .reserved2 = readInt<std::int16_t, 15>()
      };
    }

    template<>
    constexpr ObjectProperties<ObjectPropertiesType::Floatsam> ObjectPropertiesReader::read()
    {
      return {
        .content = readEnum<FloatsamContentType, 32>()
      };
    }

    template<>
    constexpr ObjectProperties<ObjectPropertiesType::FountainOfFortune> ObjectPropertiesReader::read()
    {
      return {
        .reserved1 = readInt<std::int32_t, 5>(),
        .reserved2 = readInt<std::int32_t, 8>(),
        .luck_bonus = readInt<std::int32_t, 4>(),
        .reserved3 = readInt<std::int32_t, 15>()
      };
    }

    template<>
    constexpr ObjectProperties<ObjectPropertiesType::Garrison> ObjectPropertiesReader::read()
    {
      return { .index = readInt<std::uint32_t, 32>() };
    }

    template<>
    constexpr ObjectProperties<ObjectPropertiesType::Hero> ObjectPropertiesReader::read()
    {
      return { .hero = readEnum<HeroType32, 32>() };
    }

    template<>
    constexpr ObjectProperties<ObjectPropertiesType::LeanTo> ObjectPropertiesReader::read()
    {
      return {
        .index = readInt<std::uint8_t, 5>(),
        .reserved1 = readInt<std::uint8_t, 1>(),
        .quantity = readInt<std::uint8_t, 4>(),
        .resource_type = readInt<ResourceType, 4>(),
        .reserved2 = readInt<std::int32_t, 18>()
      };
    }

    template<>
    constexpr ObjectProperties<ObjectPropertiesType::Pyramid> ObjectPropertiesReader::read()
    {
      ObjectProperties<ObjectPropertiesType::Pyramid> properties;
      properties.is_lootable = readInt<std::uint16_t, 1>();
      properties.reserved1 = readInt<std::int16_t, 4>();
      properties.visited_by.bitset.data[0] = readInt<std::uint8_t, 8>();
      properties.spell = readEnum<SpellType, 8>();
      properties.reserved2 = readInt<std::int16_t, 11>();
      return properties;
    }

    template<>
    constexpr ObjectProperties<ObjectPropertiesType::SeersHut> ObjectPropertiesReader::read()
    {
      return { .index = readInt<std::uint32_t, 32>() };
    }

    template<>
    constexpr ObjectProperties<ObjectPropertiesType::ShipwreckSurvivor> ObjectPropertiesReader::read()
    {
      return { .artifact = readEnum<ArtifactType32, 32>() };
    }

    template<>
    constexpr ObjectProperties<ObjectPropertiesType::Shrine> ObjectPropertiesReader::read()
    {
      ObjectProperties<ObjectPropertiesType::Shrine> properties;
      properties.reserved1 = readInt<std::int16_t, 5>();
      properties.visited_by.bitset.data[0] = readInt<std::uint8_t, 8>();
      properties.spell = readInt<std::int16_t, 10>();
      properties.reserved2 = readInt<std::int16_t, 9>();
      return properties;
    }

    template<>
    constexpr ObjectProperties<ObjectPropertiesType::Sign> ObjectPropertiesReader::read()
    {
      return { .index = readInt<std::uint32_t, 32>() };
    }

    template<>
    constexpr ObjectProperties<ObjectPropertiesType::TreeOfKnowledge> ObjectPropertiesReader::read()
    {
      ObjectProperties<ObjectPropertiesType::TreeOfKnowledge> properties;
      properties.index = readInt<std::uint8_t, 5>();
      properties.visited_by.bitset.data[0] = readInt<std::uint8_t, 8>();
      properties.type = readEnum<TreeOfKnowledgeType, 2>();
      properties.reserved1 = readInt<std::uint8_t, 1>();
      properties.reserved2 = readInt<std::int16_t, 16>();
      return properties;
    }

    template<>
    constexpr ObjectProperties<ObjectPropertiesType::University> ObjectPropertiesReader::read()
    {
      return {
        .reserved1 = readInt<std::int32_t, 5>(),
        .reserved2 = readInt<std::int32_t, 8>(),
        .index = readInt<std::int32_t, 12>(),
        .reserved3 = readInt<std::int32_t, 7>(),
      };
    }

    template<>
    constexpr ObjectProperties<ObjectPropertiesType::WitchHut> ObjectPropertiesReader::read()
    {
      ObjectProperties<ObjectPropertiesType::WitchHut> properties;
      properties.reserved1 = readInt<std::uint8_t, 5>();
      properties.visited_by.bitset.data[0] = readInt<std::uint8_t, 8>();
      properties.skill = readEnum<SecondarySkillType, 8>();
      properties.reserved2 = readInt<std::uint16_t, 11>();
      return properties;
    }

    template<ObjectPropertiesType T>
    ObjectPropertiesVariant readObjectPropertiesAsVariant(const H3SVGReader& reader, ObjectClass object_class)
    {
      return ObjectPropertiesVariant{ object_class, reader.readObjectProperties<T>() };
    }

    template<ObjectPropertiesType T>
    using readObjectPropertiesAsVariantAlias = SwitchStatement_NS::StaticConstant<&readObjectPropertiesAsVariant<T>>;
  }

  template<ObjectPropertiesType T>
  ObjectProperties<T> H3SVGReader::readObjectProperties() const
  {
    const std::array<std::uint8_t, 4> data = readByteArray<4>();
    return ObjectPropertiesReader::parse<T>(std::as_bytes(std::span{ data }));
  }

  ObjectPropertiesVariant H3SVGReader::readObjectPropertiesVariant(ObjectClass object_class) const
  {
    static constexpr auto switch_statement =
      SwitchStatement_NS::generateSwitchStatement<ObjectPropertiesType,
                                                  h3svg::kNumObjectPropertiesTypes,
                                                  readObjectPropertiesAsVariantAlias>();

    const ObjectPropertiesType object_properties_type = getObjectPropertiesType(object_class);
    return switch_statement(object_properties_type, *this, object_class);
  }
}
