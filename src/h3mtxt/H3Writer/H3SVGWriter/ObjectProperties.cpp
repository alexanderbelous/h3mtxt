#include <h3mtxt/H3Writer/H3SVGWriter/H3SVGWriter.h>

#include <h3mtxt/SavedGame/ObjectProperties.h>
#include <h3mtxt/SavedGame/ObjectPropertiesVariant.h>

#include <array>
#include <cstddef>
#include <cstdint>
#include <type_traits>

namespace h3svg
{
  namespace
  {
    class BitsWriter
    {
    public:
      template<std::size_t NumBits, class T>
      constexpr void writeInt(T value)
      {
        static_assert(std::is_integral_v<T>, "Must be an integral type.");
        static_assert(NumBits <= 32, "NumBits must be less or equal to 32.");
        static_assert(sizeof(T) * 8 >= NumBits, "sizeof(T)*8 must be greater or equal to NumBits.");
        writeIntImpl(static_cast<std::uint32_t>(value), NumBits);
      }

      constexpr void writeBit(bool value)
      {
        writeIntImpl(value, 1);
      }

      template<std::size_t NumBits, class T>
      constexpr void writeEnum(T value)
      {
        static_assert(std::is_enum_v<T>, "Must be an enumeration type.");
        static_assert(NumBits <= 32, "NumBits must be less or equal to 32.");
        static_assert(sizeof(T) * 8 >= NumBits, "sizeof(T)*8 must be greater or equal to NumBits.");
        writeIntImpl(static_cast<std::uint32_t>(value), NumBits);
      }

      constexpr std::uint32_t data() const noexcept
      {
        return data_as_int_;
      }

    private:
      constexpr void writeIntImpl(std::uint32_t value, std::size_t num_bits)
      {
        const std::uint32_t mask = (num_bits >= 32) ? static_cast<std::uint32_t>(-1)
                                                    : ((static_cast<std::uint32_t>(1) << num_bits) - 1);
        data_as_int_ |= ((value & mask) << num_bits_written_);
        num_bits_written_ += num_bits;
      }

      std::uint32_t data_as_int_ = 0;
      std::uint8_t num_bits_written_ = 0;
    };

    // Serializes ObjectProperties<T> into 4 bytes.
    class ObjectPropertiesWriter : private BitsWriter
    {
    public:
      template<ObjectPropertiesType T>
      static constexpr std::array<std::byte, 4> serialize(const ObjectProperties<T>& properties)
      {
        ObjectPropertiesWriter writer;
        writer.write(properties);
        const std::uint32_t data_as_int = writer.data();
        return std::array<std::byte, 4>{
          static_cast<std::byte>(data_as_int & 0xFFu),
          static_cast<std::byte>((data_as_int >> 8) & 0xFFu),
          static_cast<std::byte>((data_as_int >> 16) & 0xFFu),
          static_cast<std::byte>((data_as_int >> 24) & 0xFFu)
        };
      }

    private:
      constexpr ObjectPropertiesWriter() noexcept = default;

      template<ObjectPropertiesType T>
      constexpr void write(const ObjectProperties<T>& properties)
      {
        static_assert(false, "Not implemented");
      }
    };

    template<>
    constexpr void ObjectPropertiesWriter::write(const ObjectProperties<ObjectPropertiesType::None>& properties)
    {
      for (std::uint8_t value : properties.reserved)
      {
        writeInt<8>(value);
      }
    }

    template<>
    constexpr void ObjectPropertiesWriter::write(const ObjectProperties<ObjectPropertiesType::BlackMarket>& properties)
    {
      writeInt<32>(properties.index);
    }

    template<>
    constexpr void ObjectPropertiesWriter::write(const ObjectProperties<ObjectPropertiesType::Campfire>& properties)
    {
      writeEnum<4>(properties.resource_type);
      writeInt<4>(properties.quantity);
      for (std::uint8_t value : properties.reserved)
      {
        writeInt<8>(value);
      }
    }

    template<>
    constexpr void ObjectPropertiesWriter::write(const ObjectProperties<ObjectPropertiesType::CreatureBank>& properties)
    {
      writeInt<5>(properties.reserved1);
      writeInt<8>(properties.visited_by.bitset.data[0]);
      writeInt<12>(properties.index);
      writeInt<1>(properties.is_cleared);
      writeInt<6>(properties.reserved2);
    }

    template<>
    constexpr void ObjectPropertiesWriter::write(const ObjectProperties<ObjectPropertiesType::Dwelling>& properties)
    {
      writeInt<32>(properties.index);
    }

    template<>
    constexpr void ObjectPropertiesWriter::write(const ObjectProperties<ObjectPropertiesType::Corpse>& properties)
    {
      writeInt<5>(properties.id);
      writeInt<1>(properties.reserved1);
      writeEnum<10>(properties.artifact);
      writeInt<1>(properties.is_lootable);
      writeInt<15>(properties.reserved2);
    }

    template<>
    constexpr void ObjectPropertiesWriter::write(const ObjectProperties<ObjectPropertiesType::Event>& properties)
    {
      writeInt<10>(properties.id);
      writeInt<8>(properties.affected_players.bitset.data[0]);
      writeInt<1>(properties.applies_to_computer);
      writeInt<1>(properties.cancel_after_first_visit);
      writeInt<12>(properties.reserved);
    }

    template<>
    constexpr void ObjectPropertiesWriter::write(const ObjectProperties<ObjectPropertiesType::Floatsam>& properties)
    {
      writeEnum<32>(properties.content);
    }

    template<>
    constexpr void ObjectPropertiesWriter::write(const ObjectProperties<ObjectPropertiesType::FountainOfFortune>& properties)
    {
      writeInt<5>(properties.reserved1);
      writeInt<8>(properties.reserved2);
      writeInt<4>(properties.luck_bonus);
      writeInt<15>(properties.reserved3);
    }

    template<>
    constexpr void ObjectPropertiesWriter::write(const ObjectProperties<ObjectPropertiesType::Garrison>& properties)
    {
      writeInt<32>(properties.index);
    }

    template<>
    constexpr void ObjectPropertiesWriter::write(const ObjectProperties<ObjectPropertiesType::Hero>& properties)
    {
      writeEnum<32>(properties.hero);
    }

    template<>
    constexpr void ObjectPropertiesWriter::write(const ObjectProperties<ObjectPropertiesType::LeanTo>& properties)
    {
      writeInt<5>(properties.index);
      writeInt<1>(properties.reserved1);
      writeInt<4>(properties.quantity);
      writeEnum<4>(properties.resource_type);
      writeInt<18>(properties.reserved2);
    }

    template<>
    constexpr void ObjectPropertiesWriter::write(const ObjectProperties<ObjectPropertiesType::Pyramid>& properties)
    {
      writeInt<1>(properties.is_lootable);
      writeInt<4>(properties.reserved1);
      writeInt<8>(properties.visited_by.bitset.data[0]);
      writeEnum<8>(properties.spell);
      writeInt<11>(properties.reserved2);
    }

    template<>
    constexpr void ObjectPropertiesWriter::write(const ObjectProperties<ObjectPropertiesType::RefugeeCamp>& properties)
    {
      writeInt<32>(properties.quantity);
    }

    template<>
    constexpr void ObjectPropertiesWriter::write(const ObjectProperties<ObjectPropertiesType::SeersHut>& properties)
    {
      writeInt<32>(properties.index);
    }

    template<>
    constexpr void ObjectPropertiesWriter::write(const ObjectProperties<ObjectPropertiesType::ShipwreckSurvivor>& properties)
    {
      writeEnum<32>(properties.artifact);
    }

    template<>
    constexpr void ObjectPropertiesWriter::write(const ObjectProperties<ObjectPropertiesType::Shrine>& properties)
    {
      writeInt<5>(properties.reserved1);
      writeInt<8>(properties.visited_by.bitset.data[0]);
      writeInt<10>(properties.spell);
      writeInt<9>(properties.reserved2);
    }

    template<>
    constexpr void ObjectPropertiesWriter::write(const ObjectProperties<ObjectPropertiesType::Sign>& properties)
    {
      writeInt<32>(properties.index);
    }

    template<>
    constexpr void ObjectPropertiesWriter::write(const ObjectProperties<ObjectPropertiesType::TreeOfKnowledge>& properties)
    {
      writeInt<5>(properties.index);
      writeInt<8>(properties.visited_by.bitset.data[0]);
      writeEnum<2>(properties.type);
      writeInt<1>(properties.reserved1);
      writeInt<16>(properties.reserved2);
    }

    template<>
    constexpr void ObjectPropertiesWriter::write(const ObjectProperties<ObjectPropertiesType::University>& properties)
    {
      writeInt<5>(properties.reserved1);
      writeInt<8>(properties.reserved2);
      writeInt<12>(properties.index);
      writeInt<7>(properties.reserved3);
    }

    template<>
    constexpr void ObjectPropertiesWriter::write(const ObjectProperties<ObjectPropertiesType::WaterWheel>& properties)
    {
      writeInt<5>(properties.bonus);
      writeInt<8>(properties.visited_by.bitset.data[0]);
      writeInt<19>(properties.reserved);
    }

    template<>
    constexpr void ObjectPropertiesWriter::write(const ObjectProperties<ObjectPropertiesType::Windmill>& properties)
    {
      writeEnum<4>(properties.resource_type);
      writeInt<1>(properties.reserved1);
      writeInt<8>(properties.visited_by.bitset.data[0]);
      writeInt<4>(properties.resource_quantity);
      writeInt<15>(properties.reserved2);
    }

    template<>
    constexpr void ObjectPropertiesWriter::write(const ObjectProperties<ObjectPropertiesType::WitchHut>& properties)
    {
      writeInt<5>(properties.reserved1);
      writeInt<8>(properties.visited_by.bitset.data[0]);
      writeEnum<8>(properties.skill);
      writeInt<11>(properties.reserved2);
    }
  }

  template<ObjectPropertiesType T>
  void H3SVGWriter::writeData(const ObjectProperties<T>& properties) const
  {
    writeData(ObjectPropertiesWriter::serialize(properties));
  }

  void H3SVGWriter::writeObjectPropetiesVariant(const ObjectPropertiesVariant& properties) const
  {
    properties.visit([this] <ObjectPropertiesType T> (const ObjectProperties<T>& details)
                     {
                       writeData(details);
                     });
  }
}
