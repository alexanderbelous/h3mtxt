#include <h3mtxt/H3Reader/H3MReader/H3MReader.h>
#include <h3mtxt/H3Writer/H3MWriter/H3MWriter.h>
#include <h3mtxt/Map/ObjectProperties.h>

#include <catch2/catch_test_macros.hpp>

#include <cstddef>
#include <iterator>
#include <span>
#include <sstream>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

namespace h3m
{
  namespace
  {
    // Encodes h3m::ObjectProperties<T> via H3MWriter.
    // \param object_properties - input ObjectProperties<T>.
    // \return std::string storing the encoded data.
    template<ObjectPropertiesType T>
    std::string encodeObjectProperties(const ObjectProperties<T>& object_properties)
    {
      std::ostringstream stream;
      H3MWriter{ stream }.writeData(object_properties);
      return std::move(stream).str();
    }

    // Decodes h3m::ObjectProperties<T> via H3MReader.
    // \param encoded_data - input binary data.
    // \return h3m::ObjectProperties<T> decoded from @encoded_data.
    template<ObjectPropertiesType T>
    ObjectProperties<T> decodeObjectProperties(std::string_view encoded_data)
    {
      std::istringstream stream{ std::string{encoded_data} };
      return H3MReader{ stream }.readObjectProperties<T>();
    }

    // Catch2 sometimes has issues when printing binary strings
    // (see https://github.com/catchorg/Catch2/issues/2960).
    // Until the issue is resolved, this workaround can be used.
    std::vector<std::byte> asByteVector(std::string_view data)
    {
      const std::span<const std::byte> bytes = std::as_bytes(std::span<const char>(data));
      return std::vector<std::byte>{bytes.begin(), bytes.end()};
    }
  }

  TEST_CASE("H3M.ObjectProperties.AbandonedMine", "[H3M]")
  {
    constexpr ObjectProperties<ObjectPropertiesType::ABANDONED_MINE> kProperties = {
      .potential_resources = []() consteval {
        ResourcesBitmask bitmask;
        bitmask.set(ResourceType::Gems, true);
        bitmask.set(ResourceType::Crystal, true);
        return bitmask;
      }(),
      .unknown = ReservedData<3>{}
    };
    static constexpr char kBinaryDataCStr[] = "\x30\x00\x00\x00";
    static constexpr std::string_view kBinaryData{ kBinaryDataCStr, std::size(kBinaryDataCStr) - 1 };

    REQUIRE(asByteVector(encodeObjectProperties(kProperties)) == asByteVector(kBinaryData));
    REQUIRE(decodeObjectProperties<ObjectPropertiesType::ABANDONED_MINE>(kBinaryData) == kProperties);
  }

  TEST_CASE("H3M.ObjectProperties.Artifact", "[H3M]")
  {
    SECTION("No guardians")
    {
      const ObjectProperties<ObjectPropertiesType::ARTIFACT> kProperties = {
        .guardians = std::nullopt
      };
      static constexpr char kBinaryDataCStr[] = "\x00";
      static constexpr std::string_view kBinaryData{ kBinaryDataCStr, std::size(kBinaryDataCStr) - 1 };

      REQUIRE(asByteVector(encodeObjectProperties(kProperties)) == asByteVector(kBinaryData));
      REQUIRE(decodeObjectProperties<ObjectPropertiesType::ARTIFACT>(kBinaryData) == kProperties);
    }
    SECTION("With guardians")
    {
      const ObjectProperties<ObjectPropertiesType::ARTIFACT> kProperties = {
        .guardians = Guardians{
          .message = "Ready to fight some dragons?",
          .creatures = std::array<CreatureStack, 7>{
            CreatureStack{.type = CreatureType::BlackDragon, .count = 5},
            CreatureStack{.type = CreatureType::GreenDragon, .count = 11},
            CreatureStack{.type = CreatureType::RedDragon, .count = 10},
            CreatureStack{.type = CreatureType::GoldDragon, .count = 6},
            CreatureStack{},
            CreatureStack{},
            CreatureStack{}
          },
          .unknown = ReservedData<4>{}
        }
      };
      static constexpr char kBinaryDataCStr[] =
        "\x01"                                              // has_guardians
          "\x1c\x00\x00\x00" "Ready to fight some dragons?" // message
          "\x01"                                            // has_creatures
            "\x53\x00" "\x05\x00"                           // creatures
            "\x1a\x00" "\x0b\x00"
            "\x52\x00" "\x0a\x00"
            "\x1b\x00" "\x06\x00"
            "\xff\xff" "\x00\x00"
            "\xff\xff" "\x00\x00"
            "\xff\xff" "\x00\x00"
          "\x00\x00\x00\x00";                               // unknown
      static constexpr std::string_view kBinaryData{ kBinaryDataCStr, std::size(kBinaryDataCStr) - 1 };

      REQUIRE(asByteVector(encodeObjectProperties(kProperties)) == asByteVector(kBinaryData));
      REQUIRE(decodeObjectProperties<ObjectPropertiesType::ARTIFACT>(kBinaryData) == kProperties);
    }
  }

  TEST_CASE("H3M.ObjectProperties.GenericNoProperties", "[H3M]")
  {
    constexpr ObjectProperties<ObjectPropertiesType::GENERIC_NO_PROPERTIES> kProperties{};
    constexpr std::string_view kBinaryData = "";

    REQUIRE(asByteVector(encodeObjectProperties(kProperties)) == asByteVector(kBinaryData));
    REQUIRE(decodeObjectProperties<ObjectPropertiesType::GENERIC_NO_PROPERTIES>(kBinaryData) == kProperties);
  }

  TEST_CASE("H3M.ObjectProperties.Grail", "[H3M]")
  {
    constexpr ObjectProperties<ObjectPropertiesType::GRAIL> kProperties = {
      .allowable_radius = 10,
      .unknown = ReservedData<3>{}
    };
    static constexpr char kBinaryDataCStr[] = "\x0a\x00\x00\x00";
    static constexpr std::string_view kBinaryData{ kBinaryDataCStr, std::size(kBinaryDataCStr) - 1 };

    REQUIRE(asByteVector(encodeObjectProperties(kProperties)) == asByteVector(kBinaryData));
    REQUIRE(decodeObjectProperties<ObjectPropertiesType::GRAIL>(kBinaryData) == kProperties);
  }
}
