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
      // Writes N least significant bits of the given integer/enum value.
      template<std::size_t NumBits, class T>
      constexpr void writeBits(T value)
      {
        static_assert(std::is_integral_v<T> || std::is_enum_v<T>, "Must be an integral or an enumeration type.");
        static_assert(NumBits <= 32, "NumBits must be less than or equal to 32.");
        static_assert(NumBits <= sizeof(T) * 8, "NumBits must be less than or equal to sizeof(T)*8.");
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
        writeBits<8>(value);
      }
    }

    template<>
    constexpr void ObjectPropertiesWriter::write(const ObjectProperties<ObjectPropertiesType::BlackMarket>& properties)
    {
      writeBits<32>(properties.index);
    }

    template<>
    constexpr void ObjectPropertiesWriter::write(const ObjectProperties<ObjectPropertiesType::Campfire>& properties)
    {
      writeBits<4>(properties.resource_type);
      writeBits<4>(properties.quantity);
      for (std::uint8_t value : properties.reserved)
      {
        writeBits<8>(value);
      }
    }

    template<>
    constexpr void ObjectPropertiesWriter::write(const ObjectProperties<ObjectPropertiesType::CreatureBank>& properties)
    {
      writeBits<5>(properties.reserved1);
      writeBits<8>(properties.visited_by.bitset.data[0]);
      writeBits<12>(properties.index);
      writeBits<1>(properties.is_cleared);
      writeBits<6>(properties.reserved2);
    }

    template<>
    constexpr void ObjectPropertiesWriter::write(const ObjectProperties<ObjectPropertiesType::Dwelling>& properties)
    {
      writeBits<32>(properties.index);
    }

    template<>
    constexpr void ObjectPropertiesWriter::write(const ObjectProperties<ObjectPropertiesType::Corpse>& properties)
    {
      writeBits<5>(properties.id);
      writeBits<1>(properties.reserved1);
      writeBits<10>(properties.artifact);
      writeBits<1>(properties.is_lootable);
      writeBits<15>(properties.reserved2);
    }

    template<>
    constexpr void ObjectPropertiesWriter::write(const ObjectProperties<ObjectPropertiesType::Event>& properties)
    {
      writeBits<10>(properties.id);
      writeBits<8>(properties.affected_players.bitset.data[0]);
      writeBits<1>(properties.applies_to_computer);
      writeBits<1>(properties.cancel_after_first_visit);
      writeBits<12>(properties.reserved);
    }

    template<>
    constexpr void ObjectPropertiesWriter::write(const ObjectProperties<ObjectPropertiesType::Floatsam>& properties)
    {
      writeBits<32>(properties.content);
    }

    template<>
    constexpr void ObjectPropertiesWriter::write(const ObjectProperties<ObjectPropertiesType::FountainOfFortune>& properties)
    {
      writeBits<5>(properties.reserved1);
      writeBits<8>(properties.reserved2);
      writeBits<4>(properties.luck_bonus);
      writeBits<15>(properties.reserved3);
    }

    template<>
    constexpr void ObjectPropertiesWriter::write(const ObjectProperties<ObjectPropertiesType::Garrison>& properties)
    {
      writeBits<32>(properties.index);
    }

    template<>
    constexpr void ObjectPropertiesWriter::write(const ObjectProperties<ObjectPropertiesType::Hero>& properties)
    {
      writeBits<32>(properties.hero);
    }

    template<>
    constexpr void ObjectPropertiesWriter::write(const ObjectProperties<ObjectPropertiesType::LeanTo>& properties)
    {
      writeBits<5>(properties.index);
      writeBits<1>(properties.reserved1);
      writeBits<4>(properties.quantity);
      writeBits<4>(properties.resource_type);
      writeBits<18>(properties.reserved2);
    }

    template<>
    constexpr void ObjectPropertiesWriter::write(const ObjectProperties<ObjectPropertiesType::Pyramid>& properties)
    {
      writeBits<1>(properties.is_lootable);
      writeBits<4>(properties.reserved1);
      writeBits<8>(properties.visited_by.bitset.data[0]);
      writeBits<8>(properties.spell);
      writeBits<11>(properties.reserved2);
    }

    template<>
    constexpr void ObjectPropertiesWriter::write(const ObjectProperties<ObjectPropertiesType::RefugeeCamp>& properties)
    {
      writeBits<32>(properties.quantity);
    }

    template<>
    constexpr void ObjectPropertiesWriter::write(const ObjectProperties<ObjectPropertiesType::Scholar>& properties)
    {
      writeBits<3>(properties.type);
      writeBits<3>(properties.primary_skill);
      writeBits<7>(properties.secondary_skill);
      writeBits<10>(properties.spell);
      writeBits<9>(properties.reserved);
    }

    template<>
    constexpr void ObjectPropertiesWriter::write(const ObjectProperties<ObjectPropertiesType::SeaChest>& properties)
    {
      writeBits<2>(properties.content);
      writeBits<1>(properties.reserved1);
      writeBits<10>(properties.artifact);
      writeBits<19>(properties.reserved2);
    }

    template<>
    constexpr void ObjectPropertiesWriter::write(const ObjectProperties<ObjectPropertiesType::SeersHut>& properties)
    {
      writeBits<32>(properties.index);
    }

    template<>
    constexpr void ObjectPropertiesWriter::write(const ObjectProperties<ObjectPropertiesType::ShipwreckSurvivor>& properties)
    {
      writeBits<32>(properties.artifact);
    }

    template<>
    constexpr void ObjectPropertiesWriter::write(const ObjectProperties<ObjectPropertiesType::Shrine>& properties)
    {
      writeBits<5>(properties.reserved1);
      writeBits<8>(properties.visited_by.bitset.data[0]);
      writeBits<10>(properties.spell);
      writeBits<9>(properties.reserved2);
    }

    template<>
    constexpr void ObjectPropertiesWriter::write(const ObjectProperties<ObjectPropertiesType::Sign>& properties)
    {
      writeBits<32>(properties.index);
    }

    template<>
    constexpr void ObjectPropertiesWriter::write(const ObjectProperties<ObjectPropertiesType::TreeOfKnowledge>& properties)
    {
      writeBits<5>(properties.index);
      writeBits<8>(properties.visited_by.bitset.data[0]);
      writeBits<2>(properties.type);
      writeBits<1>(properties.reserved1);
      writeBits<16>(properties.reserved2);
    }

    template<>
    constexpr void ObjectPropertiesWriter::write(const ObjectProperties<ObjectPropertiesType::University>& properties)
    {
      writeBits<5>(properties.reserved1);
      writeBits<8>(properties.reserved2);
      writeBits<12>(properties.index);
      writeBits<7>(properties.reserved3);
    }

    template<>
    constexpr void ObjectPropertiesWriter::write(const ObjectProperties<ObjectPropertiesType::Wagon>& properties)
    {
      writeBits<5>(properties.resource_quantity);
      writeBits<8>(properties.visited_by.bitset.data[0]);
      writeBits<1>(properties.is_lootable);
      writeBits<1>(properties.has_artifact);
      writeBits<10>(properties.artifact);
      writeBits<4>(properties.resource_type);
      writeBits<3>(properties.reserved);
    }

    template<>
    constexpr void ObjectPropertiesWriter::write(const ObjectProperties<ObjectPropertiesType::WarriorsTomb>& properties)
    {
      writeBits<1>(properties.has_artifact);
      writeBits<4>(properties.reserved1);
      writeBits<8>(properties.visited_by.bitset.data[0]);
      writeBits<10>(properties.artifact);
      writeBits<9>(properties.reserved2);
    }

    template<>
    constexpr void ObjectPropertiesWriter::write(const ObjectProperties<ObjectPropertiesType::WaterWheel>& properties)
    {
      writeBits<5>(properties.bonus);
      writeBits<8>(properties.visited_by.bitset.data[0]);
      writeBits<19>(properties.reserved);
    }

    template<>
    constexpr void ObjectPropertiesWriter::write(const ObjectProperties<ObjectPropertiesType::Windmill>& properties)
    {
      writeBits<4>(properties.resource_type);
      writeBits<1>(properties.reserved1);
      writeBits<8>(properties.visited_by.bitset.data[0]);
      writeBits<4>(properties.resource_quantity);
      writeBits<15>(properties.reserved2);
    }

    template<>
    constexpr void ObjectPropertiesWriter::write(const ObjectProperties<ObjectPropertiesType::WitchHut>& properties)
    {
      writeBits<5>(properties.reserved1);
      writeBits<8>(properties.visited_by.bitset.data[0]);
      writeBits<8>(properties.skill);
      writeBits<11>(properties.reserved2);
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
