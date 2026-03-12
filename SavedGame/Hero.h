#pragma once

#include <h3mtxt/SavedGame/SavedGameFwd.h>

#include <h3mtxt/Map/Constants/ArtifactSlot.h>
#include <h3mtxt/Map/Constants/ArtifactType.h>
#include <h3mtxt/Map/Constants/HeroClass.h>
#include <h3mtxt/Map/Constants/HeroPortrait.h>
#include <h3mtxt/Map/Constants/HeroType.h>
#include <h3mtxt/Map/Constants/SpellType.h>
#include <h3mtxt/Map/Constants/ObjectClass.h>
#include <h3mtxt/Map/Constants/SecondarySkillType.h>
#include <h3mtxt/Map/Utils/BitSet.h>
#include <h3mtxt/Map/Utils/EnumIndexedArray.h>
#include <h3mtxt/Map/PrimarySkills.h>
#include <h3mtxt/SavedGame/Constants/Constants.h>
#include <h3mtxt/SavedGame/Troops.h>

#include <array>
#include <cstdint>
#include <string>

namespace h3svg
{
  // Artifact equipped on the hero or stored in the backpack.
  struct HeroArtifact
  {
    // Type of the artifact, or 0xFFFFFFFF if there is none.
    ArtifactType32 type = static_cast<ArtifactType32>(-1);
    // Type of the spell for spell scrolls; meaningless if this isn't a spell scroll.
    // The value is usually 0xFFFFFFFF if this is not a spell scroll, but don't rely on that:
    //   * Empty slots in the backpack sometimes use 0.
    //   * War machines and SpellBook slots may use junk values like 1500, 3500, 8000, etc.
    SpellType32 spell_type = static_cast<SpellType32>(0xFFFFFFFF);
  };

  struct HeroArtifacts
  {
    EnumIndexedArray<ArtifactSlot, HeroArtifact, 19> equipped;
    std::array<HeroArtifact, 64> backpack;
  };

  struct Hero
  {
    std::int16_t x {};
    std::int16_t y {};
    std::int16_t z {};
    Bool is_visible {};
    std::uint32_t coordinates_packed {};
    // ObjectClass of the object under the hero, or ObjectClass::NONE if there is none.
    ObjectClass object_class_under {};
    // TODO: figure out what this is.
    //   unknown1[0] seems to be Bool is_actionable_under; Events and Anchor points are not considered actionable.
    //   The rest seems to either be uint32_t object_idx or something like Tile::object_properties.
    std::array<std::uint8_t, 5> unknown1 {};
    Bool is_female {};
    // If 0, the default biography will be displayed for this hero, otherwise the custom one (i.e. Hero::biography).
    Bool use_custom_biography {};
    // Size is 32-bit.
    std::string biography;
    PlayerColor owner {};
    // Patrol radius or -1 if there is none.
    std::int8_t patrol_radius {};
    // TODO: figure out what this is.
    std::array<std::uint8_t, 8> unknown2 {};
    HeroType type {};
    HeroClass hero_class {};
    HeroPortrait portrait {};
    // X-coordinate of the starting position if the hero has patrol; 0xFF otherwise.
    std::uint8_t patrol_x {};
    // Y-coordinate of the starting position if the hero has patrol; 0xFF otherwise.
    std::uint8_t patrol_y {};
    // TODO: figure out what this is.
    std::array<std::uint8_t, 4> unknown3 {};
    // X-coordinate of the destination, or -1 if there is none.
    std::int32_t destination_x {};
    // Y-coordinate of the destination, or -1 if there is none.
    std::int32_t destination_y {};
    // TODO: likely std::int16_t, but not std::int32_t.
    // Note that, if meaningful, it duplicates Hero::z because you cannot plan a route to another layer.
    std::int8_t destination_z {};
      // TODO: figure out what this is.
    std::array<std::uint8_t, 3> unknown4 {};
    // Maximum number of movement points at the moment.
    // This the "potential" value, which basically reflects what would've been the number of move points if the hero
    // hadn't moved this turn. It's not constant though - e.g., visiting Stables, or equipping Boots of Speed increases
    // this number.
    std::int32_t move_points_max {};
    // The actual number of movement points at the moment.
    std::int32_t move_points {};
    std::int32_t experience {};
    std::array<std::uint8_t, 4> unknown5 {};
    std::uint16_t spell_points {};
    // Yes, you can make a hero with level 32767; however, this will be ignored on level-up: the new level
    // will be computed from the experience points.
    std::int16_t level {};
    std::array<std::uint8_t, 2> unknown6 {};
    // 1 bit per Learning Stone, indicating if the hero has visited it.
    BitSet<4> learning_stones;
    // 1 bit per Marletto Tower, indicating if the hero has visited it.
    BitSet<4> marletto_towers;
    // 1 bit per Garden of Revelation, indicating if the hero has visited it.
    BitSet<4> gardens_of_revelation;
    // 1 bit per Mercenary Camp, indicating if the hero has visited it.
    BitSet<4> mercenary_camps;
    // 1 bit per Star Axis, indicating if the hero has visited it.
    BitSet<4> star_axes;
    // 1 bit per Tree of Knowledge, indicating if the hero has visited it.
    BitSet<4> trees_of_knowledge;
    // 1 bit per Library of Enlighenment, indicating if the hero has visited it.
    BitSet<4> libraries_of_enlightenment;
    // 1 bit per Arena, indicating if the hero has visited it.
    BitSet<4> arenas;
    // 1 bit per School of Magic, indicating if the hero has visited it.
    BitSet<4> schools_of_magic;
    // 1 bit per School of War, indicating if the hero has visited it.
    BitSet<4> schools_of_war;
    std::array<std::uint8_t, 20> unknown7 {};
    Troops army;
    // Fixed-size; only the characters before the first null terminator are significant.
    std::array<char, 13> name {};
    // Level for each SeconadrySkillType.
    EnumIndexedArray<SecondarySkillType, std::uint8_t, kNumSecondarySkills> secondary_skills_levels {};
    // Slot on the Hero Screen for each SecondarySkillType.
    EnumIndexedArray<SecondarySkillType, std::uint8_t, kNumSecondarySkills> secondary_skills_slots {};
    // Primary skills of the hero (equipped artifacts are taken into account).
    PrimarySkills primary_skills;
    // 70 bytes: 1 per SpellType, indicating whether the hero has learned this spell.
    EnumIndexedArray<SpellType, Bool, kNumSpells> spells_learned;
    // 70 bytes: 1 per SpellType, indicating whether the hero can cast this spell. Note that some
    // artifacts (e.g., Spell Scrolls, Armageddon's Blade, etc) allow casting spells that the hero
    // hasn't learned yet.
    EnumIndexedArray<SpellType, Bool, kNumSpells> spells_available;
    HeroArtifacts artifacts;
    // TODO: figure out what this is.
    //   unknown8[15] is Bool is_sleeping;
    std::array<std::uint8_t, 22> unknown8 {};
  };
}