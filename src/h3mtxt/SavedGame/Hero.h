#pragma once

#include <h3mtxt/SavedGame/SavedGameFwd.h>

#include <h3mtxt/Map/Constants/ArtifactSlot.h>
#include <h3mtxt/Map/Constants/ArtifactType.h>
#include <h3mtxt/Map/Constants/HeroClass.h>
#include <h3mtxt/Map/Constants/HeroPortrait.h>
#include <h3mtxt/Map/Constants/HeroType.h>
#include <h3mtxt/Map/Constants/PlayerColor.h>
#include <h3mtxt/Map/Constants/PrimarySkillType.h>
#include <h3mtxt/Map/Constants/SecondarySkillType.h>
#include <h3mtxt/Map/Constants/SpellType.h>
#include <h3mtxt/Map/Utils/BitSet.h>
#include <h3mtxt/Map/Utils/EnumBitmask.h>
#include <h3mtxt/Map/Utils/EnumIndexedArray.h>
#include <h3mtxt/Map/Utils/ReservedData.h>
#include <h3mtxt/SavedGame/Constants/ArtifactSlotGroup.h>
#include <h3mtxt/SavedGame/Constants/CompassPoint.h>
#include <h3mtxt/SavedGame/Constants/FormationFlag.h>
#include <h3mtxt/SavedGame/Constants/HeroFlag.h>
#include <h3mtxt/SavedGame/Constants/HeroVisitableObjectType.h>
#include <h3mtxt/SavedGame/CoordinatesPacked.h>
#include <h3mtxt/SavedGame/FixedLengthString.h>
#include <h3mtxt/SavedGame/ObjectPropertiesVariant.h>
#include <h3mtxt/SavedGame/Troops.h>

#include <array>
#include <cstdint>
#include <string>

namespace h3svg
{
  // Represents Adventure Map spells currently cast by the hero.
  struct HeroActiveSpells
  {
    constexpr bool operator==(const HeroActiveSpells&) const noexcept = default;

    // (Air Magic skill) Level at which Disguise was cast, or -1 if it hasn't been cast.
    std::int8_t disguise_level = -1;
    // (Air Magic skill) Level at which Fly was cast, or -1 if it hasn't been cast.
    std::int8_t fly_level = -1;
    // (Water Magic skill) Level at which Water Walk was cast, or -1 if it hasn't been cast.
    std::int8_t water_walk_level = -1;
    // The number of times Dimension Door was cast.
    std::uint8_t num_dimension_door_casts = 0;
    // Level at which Visions was cast, or -1 if it hasn't been cast.
    std::int8_t visions_level = -1;
  };

  // Artifact equipped on the hero or stored in the backpack.
  struct HeroArtifact
  {
    constexpr bool operator==(const HeroArtifact&) const noexcept = default;

    // Type of the artifact, or 0xFFFFFFFF if there is none.
    ArtifactType32 type = static_cast<ArtifactType32>(ArtifactType::None);
    // Type of the spell for spell scrolls; meaningless if this isn't a spell scroll.
    // The value is usually 0xFFFFFFFF if this is not a spell scroll, but don't rely on that:
    //   * Empty slots in the backpack sometimes use 0.
    //   * War machines and SpellBook slots may use junk values like 1500, 3500, 8000, etc.
    SpellType32 spell_type = static_cast<SpellType32>(SpellType::None);
  };

  struct HeroArtifacts
  {
    constexpr bool operator==(const HeroArtifacts&) const noexcept = default;

    // The maximum number of artifacts in the backpack.
    static constexpr std::size_t kBackpackSize = 64;

    EnumIndexedArray<ArtifactSlot, HeroArtifact, h3m::kNumArtifactSlots> equipped;
    std::array<HeroArtifact, kBackpackSize> backpack;
    // TODO: figure out what this is.
    std::uint8_t unknown {};
    // 14 bytes: The number of locks from combination artifacts for each ArtifactSlotGroup.
    EnumIndexedArray<ArtifactSlotGroup, std::uint8_t, kNumArtifactSlotGroups> locks;
  };

  struct Hero
  {
    bool operator==(const Hero&) const noexcept = default;

    // The default value for Hero::formation_flags: Loose combat formation, Tactics enabled.
    static constexpr FormationFlags kDefaultFormationFlags = []() consteval {
      FormationFlags result;
      result.set(FormationFlag::Tactics, true);
      return result;
    }();

    std::int16_t x = -1;
    std::int16_t y = -1;
    std::int16_t z = -1;
    Bool is_visible = false;
    CoordinatesPacked coordinates_packed;
    // Indicates whether there is an actionable object under the hero.
    Bool has_object_under = false;
    // ObjectClass and the "simple" properties of the Adventure Map object under the hero.
    // This field acts as a temporary storage for the original value of Tile::object_properties
    // while the hero occupies the tile. Genius design.
    ObjectPropertiesVariant object_under;
    Bool is_female {};
    // If 0, the default biography will be displayed for this hero, otherwise the custom one (i.e. Hero::biography).
    Bool use_custom_biography = false;
    // String length is 32-bit.
    std::string biography;
    PlayerColor owner = PlayerColor::None;
    // Patrol radius or -1 if there is none.
    std::int8_t patrol_radius = -1;
    // Temporary Morale bonus until the next battle (e.g., from Events, Temples, etc).
    std::int8_t temp_morale = 0;
    // Temporary Luck bonus until the next battle (e.g., from Events, Faerie Rings, etc).
    std::int8_t temp_luck = 0;
    // The number of artifacts in the backpack.
    std::uint8_t backpack_count = 0;
    // Adventure Map spells currently cast by the hero.
    HeroActiveSpells active_spells;
    HeroType type {};
    HeroClass hero_class {};
    HeroPortrait portrait {};
    // X-coordinate of the starting position if the hero has patrol; 0xFF otherwise.
    std::uint8_t patrol_x = 0xFF;
    // Y-coordinate of the starting position if the hero has patrol; 0xFF otherwise.
    std::uint8_t patrol_y = 0xFF;
    // Orientation of the hero on the Adventure Map.
    CompassPoint orientation = CompassPoint::East;
    // Bitmask storing the formation flags.
    FormationFlags formation_flags = kDefaultFormationFlags;
    // Initial seed for the PRNG that controls the primary/secondary skills offered on level-up.
    std::uint8_t seed = 0xFF;
    // TODO: figure out what this is.
    std::uint8_t unknown1 {};
    // X-coordinate of the destination, or -1 if there is none.
    std::int32_t destination_x = -1;
    // Y-coordinate of the destination, or -1 if there is none.
    std::int32_t destination_y = -1;
    // Z-coordinate of the destionation.
    std::int8_t destination_z = 0;
      // TODO: figure out what this is.
    std::array<std::uint8_t, 3> unknown2 {};
    // Maximum number of movement points at the moment.
    // This is the "potential" value, which basically reflects what would've been the number of move points if the hero
    // hadn't moved this turn. It's not constant though - e.g., visiting Stables, or equipping Boots of Speed increases
    // this number.
    std::int32_t move_points_max {};
    // The actual number of movement points at the moment.
    std::int32_t move_points {};
    std::int32_t experience = 0;
    // The number of learned secondary skills.
    std::int32_t num_secondary_skills = 0;
    std::int16_t spell_points {};
    // Yes, you can make a hero with level 32767; however, this will be ignored on level-up: the new level
    // will be computed from the experience points.
    std::int16_t level = 1;
    std::array<std::uint8_t, 2> unknown3 {};
    // 10 bitmasks - 1 for each HeroVisitableObjectType - indicating whether this hero has visited
    // a particular Adventure Map object.
    // * For example, visited_objects[HeroVisitableObjectType::TreesOfKnowledge][5] indicates
    //   whether the hero has visited the Tree of Knowledge whose index = 5
    //   (see ObjectProperties<ObjectPropertiesType::TreeOfKnowledge>).
    EnumIndexedArray<HeroVisitableObjectType, BitSet<4>, 10> visited_objects;
    ReservedData<16> reserved;
    // Bitmask; 32 bits, whose meaning is described by enum HeroFlag.
    HeroFlags flags;
    Troops army;
    // Fixed-size; only the characters before the first null terminator are significant.
    FixedLengthString<13> name;
    // Level for each SeconadrySkillType.
    EnumIndexedArray<SecondarySkillType, std::uint8_t, h3m::kNumSecondarySkills> secondary_skills_levels;
    // Slot on the Hero Screen for each SecondarySkillType.
    EnumIndexedArray<SecondarySkillType, std::uint8_t, h3m::kNumSecondarySkills> secondary_skills_slots;
    // Primary skills of the hero (equipped artifacts are taken into account).
    PrimarySkills primary_skills;
    // 70 bytes: 1 per SpellType, indicating whether the hero has learned this spell.
    EnumIndexedArray<SpellType, Bool, h3m::kNumSpells> spells_learned;
    // 70 bytes: 1 per SpellType, indicating whether the hero can cast this spell. Note that some
    // artifacts (e.g., Spell Scrolls, Armageddon's Blade, etc) allow casting spells that the hero
    // hasn't learned yet.
    EnumIndexedArray<SpellType, Bool, h3m::kNumSpells> spells_available;
    HeroArtifacts artifacts;
    Bool is_sleeping = false;
    // 1 bit per town, indicating if the hero has visited it.
    // This is used, for example, to determine if the hero's Knowledge should increase when visiting
    // a Tower with Wall of Knowledge built.
    BitSet<6> visited_towns;
  };
}
