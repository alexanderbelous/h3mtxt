#include "TestingUtils_H3SVG.h"

#include <h3mtxt/SavedGame/Town.h>

#include <catch2/catch_test_macros.hpp>

using namespace std::string_view_literals;
using ::Testing_NS::asByteVector;
using ::Testing_NS::encodeAndDecodeJson;
using ::Testing_NS::encodeViaH3SVGWriter;
using ::Testing_NS::H3SVGReaderAdapter;

namespace h3svg
{
  namespace
  {
    template<class Enum, std::size_t NumBytes>
    constexpr EnumBitmask<Enum, NumBytes> makeEnumBitmask(std::initializer_list<Enum> bits_to_set)
    {
      EnumBitmask<Enum, NumBytes> bitmask;
      for (Enum value : bits_to_set)
      {
        bitmask.set(value, true);
      }
      return bitmask;
    }
  }

  // Test encoding/decoding Town for H3SVG.
  TEST_CASE("H3SVG.Town", "[H3SVG]")
  {
    const Town kTown{
      .id = 42,
      .owner = PlayerColor::Green,
      .built_this_turn = true,
      .unknown1 = {},
      .type = TownType::Dungeon,
      .coordinates = {.x = 49, .y = 12, .z = 1},
      .generated_boat_x = 0xFFu,
      .generated_boat_y = 0xFFu,
      .garrison = {
        .creature_types = {
          static_cast<CreatureType32>(CreatureType::BlackDragon),
          static_cast<CreatureType32>(CreatureType::None),
          static_cast<CreatureType32>(CreatureType::None),
          static_cast<CreatureType32>(CreatureType::None),
          static_cast<CreatureType32>(CreatureType::None),
          static_cast<CreatureType32>(CreatureType::None),
          static_cast<CreatureType32>(CreatureType::None),
        },
        .creature_counts = {5, 0, 0, 0, 0, 0, 0}
      },
      .garrisoned_hero = HeroType::Geon,
      .visiting_hero = HeroType::Gunnar,
      .mage_guild_level = 3,
      .unknown2 = {},
      .name = "Rhuidean",
      .recruits_nonupgraded = {0, 0, 0, 0, 0, 0, 1},
      .recruits_upgraded = {30, 20, 15, 8, 4, 2, 0},
      .num_external_dwellings = {1, 0, 0, 0, 0, 0, 0},
      .num_external_dwellings2 = {1, 0, 0, 0, 0, 0, 0},
      .unknown3 = {},
      .built = makeEnumBitmask<TownBuildingTypeH3SVG, 6>({
        TownBuildingTypeH3SVG::VillageHall,
        TownBuildingTypeH3SVG::MageGuild1,
        TownBuildingTypeH3SVG::MageGuild2,
        TownBuildingTypeH3SVG::MageGuild3,
        TownBuildingTypeH3SVG::Dwelling1,
        TownBuildingTypeH3SVG::Dwelling1U,
        TownBuildingTypeH3SVG::Dwelling2,
        TownBuildingTypeH3SVG::Dwelling2U,
        TownBuildingTypeH3SVG::Dwelling3,
        TownBuildingTypeH3SVG::Dwelling3U,
        TownBuildingTypeH3SVG::Dwelling4,
        TownBuildingTypeH3SVG::Dwelling4U,
        TownBuildingTypeH3SVG::Dwelling5,
        TownBuildingTypeH3SVG::Dwelling5U,
        TownBuildingTypeH3SVG::Dwelling6,
        TownBuildingTypeH3SVG::Dwelling6U,
        TownBuildingTypeH3SVG::Dwelling7
       }),
      .reserved1 = {},
      .can_be_built = makeEnumBitmask<TownBuildingTypeH3SVG, 6>({}),
      .reserved2 = {},
      .spells = {{
          // Level 1
          {
            static_cast<SpellType32>(SpellType::MagicArrow),
            static_cast<SpellType32>(SpellType::Slow),
            static_cast<SpellType32>(SpellType::Haste),
            static_cast<SpellType32>(SpellType::Cure),
            static_cast<SpellType32>(SpellType::Curse),
            static_cast<SpellType32>(-1)
          },
        // Level 2
        {
          static_cast<SpellType32>(SpellType::QuickSand),
          static_cast<SpellType32>(SpellType::LightningBolt),
          static_cast<SpellType32>(SpellType::FireWall),
          static_cast<SpellType32>(SpellType::DisruptingRay),
          static_cast<SpellType32>(-1),
          static_cast<SpellType32>(-1)
        },
        // Level 3
        {
          static_cast<SpellType32>(SpellType::ForceField),
          static_cast<SpellType32>(SpellType::AntiMagic),
          static_cast<SpellType32>(SpellType::Fireball),
          static_cast<SpellType32>(-1),
          static_cast<SpellType32>(-1),
          static_cast<SpellType32>(-1)
        },
        // Level 4
        {
          static_cast<SpellType32>(SpellType::Resurrection),
          static_cast<SpellType32>(SpellType::TownPortal),
          static_cast<SpellType32>(-1),
          static_cast<SpellType32>(-1),
          static_cast<SpellType32>(-1),
          static_cast<SpellType32>(-1)
        },
        // Level 5
        {
          static_cast<SpellType32>(SpellType::Implosion),
          static_cast<SpellType32>(-1),
          static_cast<SpellType32>(-1),
          static_cast<SpellType32>(-1),
          static_cast<SpellType32>(-1),
          static_cast<SpellType32>(-1)
        }
      }},
      .banned_spells = {},
      .unknown4 = {},
      .unique_buildings_properties = {
        .mana_vortex_available = true,
        .mystic_pond_resource_amount = 0,
        .mystic_pond_resource_type = static_cast<ResourceType>(7),
        .unknown = 0,
        .summoned_creatures = {
          .type = static_cast<CreatureType32>(CreatureType::AzureDragon),
          .quantity = 1
        }
      }
    };

    // The binary representation of kTown.
    static constexpr std::string_view kBinaryData =
      "\x2a" // id
      "\x03" // owner
      "\x01" // built_this_turn
      "\x00" // unknown1
      "\x05" // type
      "\x31\x0c\x01" // coordinates
      "\xff" // generated_boat_x
      "\xff" // generated_boat_y
             // garrison
        "\x53\x00\x00\x00" "\xff\xff\xff\xff" "\xff\xff\xff\xff" "\xff\xff\xff\xff" // creature_types
        "\xff\xff\xff\xff" "\xff\xff\xff\xff" "\xff\xff\xff\xff"
        "\x05\x00\x00\x00" "\x00\x00\x00\x00" "\x00\x00\x00\x00" "\x00\x00\x00\x00" // creature_counts
        "\x00\x00\x00\x00" "\x00\x00\x00\x00" "\x00\x00\x00\x00"
      "\x5c" // garrisoned_hero
      "\x55" // visiting_hero
      "\x03" // mage_guild_level
      "\x00" // unknown2
      "\x08\x00" "Rhuidean" // name
      "\x00\x00" "\x00\x00" "\x00\x00" "\x00\x00" // recruits_nonupgraded
      "\x00\x00" "\x00\x00" "\x01\x00"
      "\x1e\x00" "\x14\x00" "\x0f\x00" "\x08\x00" // recruits_upgraded
      "\x04\x00" "\x02\x00" "\x00\x00"
      "\x01\x00\x00\x00" "\x00\x00\x00\x00" "\x00\x00\x00\x00" "\x00\x00\x00\x00" // num_external_dwellings
      "\x00\x00\x00\x00" "\x00\x00\x00\x00" "\x00\x00\x00\x00"
      "\x01\x00\x00\x00" "\x00\x00\x00\x00" "\x00\x00\x00\x00" "\x00\x00\x00\x00" // num_external_dwellings2
      "\x00\x00\x00\x00" "\x00\x00\x00\x00" "\x00\x00\x00\x00"
      "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" // unknown3
      "\x07\x04\x00\xc0\xff\x07" // built
      "\x00\x00" // reserved1
      "\x00\x00\x00\x00\x00\x00" // can_be_built
      "\x00\x00" // reserved2
        // spells
        "\x0f\x00\x00\x00" "\x36\x00\x00\x00" "\x35\x00\x00\x00" // Level 1
        "\x25\x00\x00\x00" "\x2a\x00\x00\x00" "\xff\xff\xff\xff"
        "\x0a\x00\x00\x00" "\x11\x00\x00\x00" "\x0d\x00\x00\x00" // Level 2
        "\x2f\x00\x00\x00" "\xff\xff\xff\xff" "\xff\xff\xff\xff"
        "\x0c\x00\x00\x00" "\x22\x00\x00\x00" "\x15\x00\x00\x00" // Level 3
        "\xff\xff\xff\xff" "\xff\xff\xff\xff" "\xff\xff\xff\xff"
        "\x26\x00\x00\x00" "\x09\x00\x00\x00" "\xff\xff\xff\xff" // Level 4
        "\xff\xff\xff\xff" "\xff\xff\xff\xff" "\xff\xff\xff\xff"
        "\x12\x00\x00\x00" "\xff\xff\xff\xff" "\xff\xff\xff\xff" // Level 5
        "\xff\xff\xff\xff" "\xff\xff\xff\xff" "\xff\xff\xff\xff"
      "\x00\x00\x00\x00\x00\x00\x00\x00\x00" // banned_spells
      "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" // unknown4
      "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
      "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
      "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
      "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
      // unique_buildings_properties
        "\x71"
        // summoned_creatures
          "\x84\x00\x00\x00" // type
          "\x01\x00"         // quantity
      ""sv;

    REQUIRE(asByteVector(encodeViaH3SVGWriter(kTown)) == asByteVector(kBinaryData));
    REQUIRE(H3SVGReaderAdapter(kBinaryData).readTown() == kTown);
    REQUIRE(encodeAndDecodeJson(kTown) == kTown);
  }
}
