#include "TestingUtils_H3SVG.h"

#include <h3mtxt/SavedGame/Hero.h>

#include <catch2/catch_test_macros.hpp>

using namespace std::string_view_literals;
using ::Testing_NS::asByteVector;
using ::Testing_NS::encodeAndDecodeJson;
using ::Testing_NS::encodeViaH3SVGWriter;
using ::Testing_NS::H3SVGReaderAdapter;

namespace h3svg
{
  // Test encoding/decoding Hero for H3SVG.
  TEST_CASE("H3SVG.Hero", "[H3SVG]")
  {
    const Hero kHero = {
      .x = 20,
      .y = 112,
      .z = 1,
      .is_visible = true,
      .coordinates_packed = {.x = 20, .y = 112, .z = 1},
      .object_class_under = ObjectClass::NONE,
      .has_object_under = false,
      .unknown1 = {0, 0, 0, 0},
      .is_female = true,
      .use_custom_biography = true,
      .biography = "Born on Monday",
      .owner = PlayerColor::Green,
      .patrol_radius = -1,
      .temp_morale = 3,
      .temp_luck = 2,
      .backpack_count = 5,
      .disguise_level = -1,
      .fly_level = -1,
      .water_walk_level = 3,
      .num_dimension_door_casts = 0,
      .visions_level = -1,
      .type = HeroType::Mephala,
      .hero_class = HeroClass::Ranger,
      .portrait = HeroPortrait::Mephala,
      .patrol_x = 0xFF,
      .patrol_y = 0xFF,
      .orientation = CompassPoint::SouthWest,
      .formation_flags = { 0x03 },
      .seed = 42,
      .unknown2 = 0,
      .destination_x = 22,
      .destination_y = 113,
      .destination_z = 1,
      .unknown3 = {0, 0, 0},
      .move_points_max = 2600,
      .move_points = 2000,
      .experience = 10'000'000,
      .num_secondary_skills = 8,
      .spell_points = 1980,
      .level = 46,
      .unknown4 = {0, 0},
      .learning_stones = {0xFF, 0xFF, 0xFF, 0x0F},
      .marletto_towers = {0x03, 0xFF, 0x00, 0x00},
      .gardens_of_revelation = {0x00, 0x00, 0x00, 0x07},
      .mercenary_camps = {0x00, 0x00, 0x00, 0x00},
      .star_axes = {0x01, 0x00, 0x00, 0x00},
      .trees_of_knowledge = {0x07, 0x00, 0x00, 0x00},
      .libraries_of_enlightenment = {0x80, 0x00, 0x00, 0x01},
      .arenas = {0xFF, 0x00, 0x00, 0x01},
      .schools_of_magic = {0x00, 0x00, 0xFF, 0x00},
      .schools_of_war = {0x00, 0x03, 0x00, 0x00},
      .reserved = {},
      .flags = []() consteval {
        HeroFlags result;
        result.set(HeroFlag::Temple2, true);
        result.set(HeroFlag::IdolOfFortuneMorale, true);
        result.set(HeroFlag::FountainOfFortune2, true);
        return result;
      }(),
      .army = {
        .creature_types = {
          static_cast<CreatureType32>(CreatureType::Enchanter),
          static_cast<CreatureType32>(CreatureType::AzureDragon),
          static_cast<CreatureType32>(CreatureType::Sharpshooter),
          static_cast<CreatureType32>(CreatureType::SilverPegasus),
          static_cast<CreatureType32>(CreatureType::None),
          static_cast<CreatureType32>(CreatureType::None),
          static_cast<CreatureType32>(CreatureType::None),
        },
        .creature_counts = { 2000, 130, 4000, 961, 0, 0, 0 }
      },
      .name = "Mephala",
      .secondary_skills_levels = []() consteval {
        EnumIndexedArray<SecondarySkillType, std::uint8_t, h3m::kNumSecondarySkills> levels;
        levels[SecondarySkillType::Armorer] = 3;
        levels[SecondarySkillType::Archery] = 3;
        levels[SecondarySkillType::EarthMagic] = 3;
        levels[SecondarySkillType::Wisdom] = 3;
        levels[SecondarySkillType::WaterMagic] = 3;
        levels[SecondarySkillType::Intelligence] = 3;
        levels[SecondarySkillType::Tactics] = 3;
        levels[SecondarySkillType::Logistics] = 3;
        return levels;
      }(),
      .secondary_skills_slots = []() consteval {
        EnumIndexedArray<SecondarySkillType, std::uint8_t, h3m::kNumSecondarySkills> slots;
        slots[SecondarySkillType::Armorer] = 1;
        slots[SecondarySkillType::Archery] = 2;
        slots[SecondarySkillType::Wisdom] = 3;
        slots[SecondarySkillType::Logistics] = 4;
        slots[SecondarySkillType::EarthMagic] = 5;
        slots[SecondarySkillType::WaterMagic] = 6;
        slots[SecondarySkillType::Tactics] = 7;
        slots[SecondarySkillType::Intelligence] = 8;
        return slots;
      }(),
      .primary_skills = { 71, 63, 59, 68 },
      .spells_learned = []() consteval {
        EnumIndexedArray<SpellType, Bool, h3m::kNumSpells> spells;
        spells[SpellType::ForceField] = true;
        spells[SpellType::Slow] = true;
        spells[SpellType::QuickSand] = true;
        return spells;
      }(),
      .spells_available = []() consteval {
        EnumIndexedArray<SpellType, Bool, h3m::kNumSpells> spells;
        spells[SpellType::ForceField] = true;
        spells[SpellType::Slow] = true;
        spells[SpellType::QuickSand] = true;
        spells[SpellType::Resurrection] = true;
        spells[SpellType::Armageddon] = true;
        return spells;
      }(),
      .artifacts = {
        .equipped = []() consteval {
          EnumIndexedArray<ArtifactSlot, HeroArtifact, h3m::kNumArtifactSlots> result;
          result[ArtifactSlot::RightHand] = HeroArtifact{
            .type = static_cast<ArtifactType32>(ArtifactType::ArmageddonsBlade)
          };
          result[ArtifactSlot::Misc1] = HeroArtifact{
            .type = static_cast<ArtifactType32>(ArtifactType::SpellScroll),
            .spell_type = static_cast<SpellType32>(SpellType::Resurrection)
          };
          result[ArtifactSlot::Misc2] = HeroArtifact{
            .type = static_cast<ArtifactType32>(ArtifactType::BowOfTheSharpshooter),
          };
          result[ArtifactSlot::Spellbook] = HeroArtifact{
            .type = static_cast<ArtifactType32>(ArtifactType::Spellbook)
          };
          return result;
        }(),
        .backpack = {
          HeroArtifact{ .type = static_cast<ArtifactType32>(ArtifactType::TalismanOfMana) },
          HeroArtifact{.type = static_cast<ArtifactType32>(ArtifactType::SeaCaptainsHat) },
          HeroArtifact{.type = static_cast<ArtifactType32>(ArtifactType::HeadOfLegion) },
          HeroArtifact{
            .type = static_cast<ArtifactType32>(ArtifactType::SpellScroll),
            .spell_type = static_cast<SpellType32>(SpellType::TownPortal)
          },
          HeroArtifact{.type = static_cast<ArtifactType32>(ArtifactType::AmbassadorsSash) }
        },
        .unknown = 0,
        .locks = []() consteval {
          EnumIndexedArray<ArtifactSlotGroup, std::uint8_t, kNumArtifactSlotGroups> result;
          result[ArtifactSlotGroup::Misc] = 2;
          return result;
        }()
      },
      .is_sleeping = false,
      .visited_towns = {0xFF, 0xF3, 0x00, 0x01, 0x00, 0x00}
    };
    // Binary representation of kHero.
    static constexpr std::string_view kBinaryData =
      "\x14\x00"  // x
      "\x70\x00"  // y
      "\x01\x00"  // z
      "\x01"      // is_visible
      "\x14\x00\x70\x04" // coordinates_packed
      "\x00\x00\x00\x00" // object_class_under
      "\x00" // has_object_under
      "\x00\x00\x00\x00" // unknown1
      "\x01" // is_female
      "\x01" // use_custom_biography
      "\x0e\x00\x00\x00" "Born on Monday" // biography
      "\x03" // owner
      "\xff" // patrol_radius
      "\x03" // temp_morale
      "\x02" // temp_luck
      "\x05" // backpack_count
      "\xff" // disguise_level
      "\xff" // fly_level
      "\x03" // water_walk_level
      "\x00" // num_dimension_door_casts
      "\xff" // visions_level
      "\x10" // type
      "\x02" // hero_class
      "\x10" // portrait
      "\xff" // patrol_x
      "\xff" // patrol_y
      "\x05" // orientation
      "\x03" // formation_flags
      "\x2a" // seed
      "\x00" // unknown2
      "\x16\x00\x00\x00" // destination_x
      "\x71\x00\x00\x00" // destination_y
      "\x01" // destination_z
      "\x00\x00\x00" // unknown3
      "\x28\x0a\x00\x00" // move_points_max
      "\xd0\x07\x00\x00" // move_points
      "\x80\x96\x98\x00" // experience
      "\x08\x00\x00\x00" // num_secondary_skills
      "\xbc\x07" // spell_points
      "\x2e\x00" // level
      "\x00\x00" // unknown4
      "\xff\xff\xff\x0f" // learning_stones
      "\x03\xff\x00\x00" // marletto_towers
      "\x00\x00\x00\x07" // gardens_of_revelation
      "\x00\x00\x00\x00" // mercenary_camps
      "\x01\x00\x00\x00" // star_axes
      "\x07\x00\x00\x00" // trees_of_knowledge
      "\x80\x00\x00\x01" // libraries_of_enlightenment
      "\xff\x00\x00\x01" // arenas
      "\x00\x00\xff\x00" // schools_of_magic
      "\x00\x03\x00\x00" // schools_of_war
      "\x00\x00\x00\x00" "\x00\x00\x00\x00" "\x00\x00\x00\x00" "\x00\x00\x00\x00" // reserved
      "\x10\x00\x00\x14" // flags
      // army
      "\x88\x00\x00\x00" "\x84\x00\x00\x00" "\x89\x00\x00\x00" "\x15\x00\x00\x00" // creature_types
      "\xff\xff\xff\xff" "\xff\xff\xff\xff" "\xff\xff\xff\xff"
      "\xd0\x07\x00\x00" "\x82\x00\x00\x00" "\xa0\x0f\x00\x00" "\xc1\x03\x00\x00" // creature_counts
      "\x00\x00\x00\x00" "\x00\x00\x00\x00" "\x00\x00\x00\x00"
      "Mephala\x00\x00\x00\x00\x00\x00" // name
      "\x00\x03\x03\x00" "\x00\x00\x00\x03" "\x00\x00\x00\x00" "\x00\x00\x00\x00" // secondary_skills_levels
      "\x03\x03\x00\x03" "\x00\x00\x00\x03" "\x03\x00\x00\x00"
      "\x00\x02\x04\x00" "\x00\x00\x00\x03" "\x00\x00\x00\x00" "\x00\x00\x00\x00" // secondary_skills_slots
      "\x06\x05\x00\x07" "\x00\x00\x00\x01" "\x08\x00\x00\x00"
      "\x47\x3f\x3b\x44" // primary_skills
      "\x00\x00\x00\x00" "\x00\x00\x00\x00" "\x00\x00\x01\x00" "\x01\x00\x00\x00" // spells_learned
      "\x00\x00\x00\x00" "\x00\x00\x00\x00" "\x00\x00\x00\x00" "\x00\x00\x00\x00"
      "\x00\x00\x00\x00" "\x00\x00\x00\x00" "\x00\x00\x00\x00" "\x00\x00\x00\x00"
      "\x00\x00\x00\x00" "\x00\x00\x01\x00" "\x00\x00\x00\x00" "\x00\x00\x00\x00"
      "\x00\x00\x00\x00" "\x00\x00"
      "\x00\x00\x00\x00" "\x00\x00\x00\x00" "\x00\x00\x01\x00" "\x01\x00\x00\x00" // spells_available
      "\x00\x00\x00\x00" "\x00\x00\x00\x00" "\x00\x00\x01\x00" "\x00\x00\x00\x00"
      "\x00\x00\x00\x00" "\x00\x00\x01\x00" "\x00\x00\x00\x00" "\x00\x00\x00\x00"
      "\x00\x00\x00\x00" "\x00\x00\x01\x00" "\x00\x00\x00\x00" "\x00\x00\x00\x00"
      "\x00\x00\x00\x00" "\x00\x00"
      // artifacts
      //   equipped
      "\xff\xff\xff\xff" "\xff\xff\xff\xff" // Head
      "\xff\xff\xff\xff" "\xff\xff\xff\xff" // Shoulders
      "\xff\xff\xff\xff" "\xff\xff\xff\xff" // Neck
      "\x80\x00\x00\x00" "\xff\xff\xff\xff" // RightHand
      "\xff\xff\xff\xff" "\xff\xff\xff\xff" // LeftHand
      "\xff\xff\xff\xff" "\xff\xff\xff\xff" // Torso
      "\xff\xff\xff\xff" "\xff\xff\xff\xff" // RightRing
      "\xff\xff\xff\xff" "\xff\xff\xff\xff" // LeftRing
      "\xff\xff\xff\xff" "\xff\xff\xff\xff" // Feet
      "\x01\x00\x00\x00" "\x26\x00\x00\x00" // Misc1
      "\x89\x00\x00\x00" "\xff\xff\xff\xff" // Misc2
      "\xff\xff\xff\xff" "\xff\xff\xff\xff" // Misc3
      "\xff\xff\xff\xff" "\xff\xff\xff\xff" // Misc4
      "\xff\xff\xff\xff" "\xff\xff\xff\xff" // WarMachine1
      "\xff\xff\xff\xff" "\xff\xff\xff\xff" // WarMachine2
      "\xff\xff\xff\xff" "\xff\xff\xff\xff" // WarMachine3
      "\xff\xff\xff\xff" "\xff\xff\xff\xff" // WarMachine4
      "\x00\x00\x00\x00" "\xff\xff\xff\xff" // Spellbook
      "\xff\xff\xff\xff" "\xff\xff\xff\xff" // Misc5
      //   backpack
      "\x4a\x00\x00\x00" "\xff\xff\xff\xff"
      "\x7b\x00\x00\x00" "\xff\xff\xff\xff"
      "\x7a\x00\x00\x00" "\xff\xff\xff\xff"
      "\x01\x00\x00\x00" "\x09\x00\x00\x00"
      "\x44\x00\x00\x00" "\xff\xff\xff\xff"
      "\xff\xff\xff\xff" "\xff\xff\xff\xff"
      "\xff\xff\xff\xff" "\xff\xff\xff\xff"
      "\xff\xff\xff\xff" "\xff\xff\xff\xff"
      "\xff\xff\xff\xff" "\xff\xff\xff\xff"
      "\xff\xff\xff\xff" "\xff\xff\xff\xff"
      "\xff\xff\xff\xff" "\xff\xff\xff\xff"
      "\xff\xff\xff\xff" "\xff\xff\xff\xff"
      "\xff\xff\xff\xff" "\xff\xff\xff\xff"
      "\xff\xff\xff\xff" "\xff\xff\xff\xff"
      "\xff\xff\xff\xff" "\xff\xff\xff\xff"
      "\xff\xff\xff\xff" "\xff\xff\xff\xff"
      "\xff\xff\xff\xff" "\xff\xff\xff\xff"
      "\xff\xff\xff\xff" "\xff\xff\xff\xff"
      "\xff\xff\xff\xff" "\xff\xff\xff\xff"
      "\xff\xff\xff\xff" "\xff\xff\xff\xff"
      "\xff\xff\xff\xff" "\xff\xff\xff\xff"
      "\xff\xff\xff\xff" "\xff\xff\xff\xff"
      "\xff\xff\xff\xff" "\xff\xff\xff\xff"
      "\xff\xff\xff\xff" "\xff\xff\xff\xff"
      "\xff\xff\xff\xff" "\xff\xff\xff\xff"
      "\xff\xff\xff\xff" "\xff\xff\xff\xff"
      "\xff\xff\xff\xff" "\xff\xff\xff\xff"
      "\xff\xff\xff\xff" "\xff\xff\xff\xff"
      "\xff\xff\xff\xff" "\xff\xff\xff\xff"
      "\xff\xff\xff\xff" "\xff\xff\xff\xff"
      "\xff\xff\xff\xff" "\xff\xff\xff\xff"
      "\xff\xff\xff\xff" "\xff\xff\xff\xff"
      "\xff\xff\xff\xff" "\xff\xff\xff\xff"
      "\xff\xff\xff\xff" "\xff\xff\xff\xff"
      "\xff\xff\xff\xff" "\xff\xff\xff\xff"
      "\xff\xff\xff\xff" "\xff\xff\xff\xff"
      "\xff\xff\xff\xff" "\xff\xff\xff\xff"
      "\xff\xff\xff\xff" "\xff\xff\xff\xff"
      "\xff\xff\xff\xff" "\xff\xff\xff\xff"
      "\xff\xff\xff\xff" "\xff\xff\xff\xff"
      "\xff\xff\xff\xff" "\xff\xff\xff\xff"
      "\xff\xff\xff\xff" "\xff\xff\xff\xff"
      "\xff\xff\xff\xff" "\xff\xff\xff\xff"
      "\xff\xff\xff\xff" "\xff\xff\xff\xff"
      "\xff\xff\xff\xff" "\xff\xff\xff\xff"
      "\xff\xff\xff\xff" "\xff\xff\xff\xff"
      "\xff\xff\xff\xff" "\xff\xff\xff\xff"
      "\xff\xff\xff\xff" "\xff\xff\xff\xff"
      "\xff\xff\xff\xff" "\xff\xff\xff\xff"
      "\xff\xff\xff\xff" "\xff\xff\xff\xff"
      "\xff\xff\xff\xff" "\xff\xff\xff\xff"
      "\xff\xff\xff\xff" "\xff\xff\xff\xff"
      "\xff\xff\xff\xff" "\xff\xff\xff\xff"
      "\xff\xff\xff\xff" "\xff\xff\xff\xff"
      "\xff\xff\xff\xff" "\xff\xff\xff\xff"
      "\xff\xff\xff\xff" "\xff\xff\xff\xff"
      "\xff\xff\xff\xff" "\xff\xff\xff\xff"
      "\xff\xff\xff\xff" "\xff\xff\xff\xff"
      "\xff\xff\xff\xff" "\xff\xff\xff\xff"
      "\xff\xff\xff\xff" "\xff\xff\xff\xff"
      "\xff\xff\xff\xff" "\xff\xff\xff\xff"
      "\xff\xff\xff\xff" "\xff\xff\xff\xff"
      "\xff\xff\xff\xff" "\xff\xff\xff\xff"
      "\xff\xff\xff\xff" "\xff\xff\xff\xff"
      "\x00" //   unknown
      "\x00\x00\x00\x00" "\x00\x00\x00\x00" "\x02\x00\x00\x00" "\x00\x00" //   locks
      "\x00" // is_sleeping
      "\xff\xf3\x00\x01\x00\x00" // visited_towns
      ""sv;

    REQUIRE(asByteVector(encodeViaH3SVGWriter(kHero)) == asByteVector(kBinaryData));
    REQUIRE(H3SVGReaderAdapter(kBinaryData).readHero() == kHero);
    REQUIRE(encodeAndDecodeJson(kHero) == kHero);
  }
}
