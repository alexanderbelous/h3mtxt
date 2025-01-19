#pragma once

#include <h3mtxt/Map/AffectedPlayers.h>
#include <h3mtxt/Map/Base.h>
#include <h3mtxt/Map/Constants/Disposition.h>
#include <h3mtxt/Map/Constants/Formation.h>
#include <h3mtxt/Map/Constants/Gender.h>
#include <h3mtxt/Map/Constants/HeroType.h>
#include <h3mtxt/Map/Constants/MetaObjectType.h>
#include <h3mtxt/Map/Constants/ScholarRewardType.h>
#include <h3mtxt/Map/Constants/SpellType.h>
#include <h3mtxt/Map/CreatureStack.h>
#include <h3mtxt/Map/HeroArtifacts.h>
#include <h3mtxt/Map/PrimarySkills.h>
#include <h3mtxt/Map/Resources.h>
#include <h3mtxt/Map/Reward.h>
#include <h3mtxt/Map/SecondarySkill.h>
#include <h3mtxt/Map/TimedEventBase.h>
#include <h3mtxt/Map/Quest.h>
#include <h3mtxt/Map/Utils/BitSet.h>
#include <h3mtxt/Map/Utils/ReservedData.h>

#include <array>
#include <cstdint>
#include <optional>
#include <string>
#include <vector>

namespace h3m
{
  // TODO: move to a separate header
  struct Guardians
  {
    std::string message;
    std::optional<std::array<CreatureStack, 7>> creatures;
    ReservedData<4> unknown;
  };

  // "Extension" of ObjectDetails specific to ObjectClass of this object.
  template<MetaObjectType T>
  struct ObjectDetailsData;

  template<>
  struct ObjectDetailsData<MetaObjectType::ABANDONED_MINE>
  {
    // Bitfield: LSB wood that is forced off by editor, then mercury, ore, sulfur, crystal, gems, MSB gold.
    // TODO: replace with a custom wrapper class.
    BitSet<4> potential_resources {};
  };

  template<>
  struct ObjectDetailsData<MetaObjectType::ARTIFACT>
  {
    std::optional<Guardians> guardians;
  };

  template<>
  struct ObjectDetailsData<MetaObjectType::GARRISON>
  {
    // 0xFF means no owner.
    std::uint32_t owner {};
    // Note: h3m2json claims that here 0xFF in CreatureStack.type means "no creature", but
    // in other places 0xFFFF is used instead.
    std::array<CreatureStack, 7> creatures {};
    Bool can_remove_units {};
    ReservedData<8> unknown;
  };

  template<>
  struct ObjectDetailsData<MetaObjectType::GENERIC_NO_PROPERTIES>
  {
  };

  template<>
  struct ObjectDetailsData<MetaObjectType::GRAIL>
  {
    std::uint32_t allowable_radius {};
  };

  // Additional info for ObjectClass::HERO, ObjectClass::RANDOM_HERO and ObjectClass::PRISON.
  // TODO: this implies that you can set name, face, biography and gender for a random hero,
  // or set a random hero in a prison. Check if this is true.
  //
  // Note that this struct is similar to HeroSettings, but it has extra fields in between,
  // so I'm not reusing that struct.
  template<>
  struct ObjectDetailsData<MetaObjectType::HERO>
  {
    std::uint32_t absod_id {};
    // Should always be 0xFF for ObjectClass::PRISON.
    std::uint8_t owner {};
    // 0xFF if random.
    HeroType type {};
    std::optional<std::string> name;
    // Note: in RoE/AB experience is not optional.
    std::optional<std::uint32_t> experience;
    std::optional<std::uint8_t> face;
    std::optional<std::vector<SecondarySkill>> secondary_skills;
    // 0xFFFF in CreatureStack.type means no creature.
    std::optional<std::array<CreatureStack, 7>> creatures;
    Formation formation {};
    std::optional<HeroArtifacts> artifacts;
    // 0xFF means no patrol.
    std::uint8_t patrol_radius {};
    std::optional<std::string> biography;
    Gender gender {};
    // TODO: add a wrapper class.
    std::optional<BitSet<9>> spells;
    std::optional<PrimarySkills> primary_skills;
    // 0s by default; kept here for compatibility.
    ReservedData<16> unknown;
  };

  template<>
  struct ObjectDetailsData<MetaObjectType::MONSTER>
  {
    struct MessageAndTreasure
    {
      std::string message;
      Resources<std::uint32_t> resources {};
      // 0xFFFF means no artifact.
      std::uint16_t artifact {};
    };

    std::uint32_t absod_id {};
    // 0 means random.
    std::uint16_t count {};
    Disposition disposition {};
    std::optional<MessageAndTreasure> message_and_treasure;
    Bool never_flees {};
    Bool does_not_grow {};
  };

  template<>
  struct ObjectDetailsData<MetaObjectType::PANDORAS_BOX>
  {
    std::optional<Guardians> guardians;
    std::uint32_t experience {};
    std::int32_t spell_points {};
    std::int8_t morale {};
    std::int8_t luck {};
    Resources<std::int32_t> resources;
    PrimarySkills primary_skills;
    std::vector<SecondarySkill> secondary_skill;
    std::vector<std::uint16_t> artifacts;
    std::vector<SpellType> spells;
    std::vector<CreatureStack> creatures;
    ReservedData<8> unknown {};
  };

  // TODO: use composition instead of inheritance.
  template<>
  struct ObjectDetailsData<MetaObjectType::EVENT> : ObjectDetailsData<MetaObjectType::PANDORAS_BOX>
  {
    AffectedPlayers affected_players;
    Bool applies_to_computer{};
    Bool remove_after_first_visit{};
    ReservedData<4> unknown{};
  };

  template<>
  struct ObjectDetailsData<MetaObjectType::PLACEHOLDER_HERO>
  {
    // TODO: make this an enum.
    std::uint8_t owner {};
    HeroType type {};
    // Only if type == 0xFF.
    std::uint8_t power_rating {};
  };

  template<>
  struct ObjectDetailsData<MetaObjectType::QUEST_GUARD>
  {
    Quest quest;
  };

  template<>
  struct ObjectDetailsData<MetaObjectType::RANDOM_DWELLING>
  {
    // 0xFF if none.
    std::uint32_t owner {};
    // absod_id of the town ("Random Dwelling Properties" -> "Alignment" -> "Same as").
    // If 0, the dwelling's alignment is not tied to a specific town.
    std::uint32_t town_absod_id {};
    // This field is only read/written if town_absod_id == 0.
    BitSet<2> alignment;
    // 0-based.
    std::uint8_t min_level {};
    std::uint8_t max_level {};
  };

  template<>
  struct ObjectDetailsData<MetaObjectType::RANDOM_DWELLING_PRESET_ALIGNMENT>
  {
    // 0xFF if none.
    std::uint32_t owner {};
    std::uint8_t min_level {};
    std::uint8_t max_level {};
  };

  template<>
  struct ObjectDetailsData<MetaObjectType::RANDOM_DWELLING_PRESET_LEVEL>
  {
    // 0xFF if none.
    std::uint32_t owner {};
    // absod_id of the town ("Random Dwelling Properties" -> "Alignment" -> "Same as").
    // If 0, the dwelling's alignment is not tied to a specific town.
    std::uint32_t town_absod_id {};
    // This field is only read/written if town_absod_id == 0.
    BitSet<2> alignment;
  };

  template<>
  struct ObjectDetailsData<MetaObjectType::RESOURCE>
  {
    std::optional<Guardians> guardians;
    // Multiply by 100 for gold, i.e. subclass 6.
    std::uint32_t quantity {};
    ReservedData<4> unknown {};
  };

  template<>
  struct ObjectDetailsData<MetaObjectType::SCHOLAR>
  {
    ScholarRewardType reward_type {};
    // TODO: consider using std::variant.
    // Always 0 if type is random;
    // 0 boost attack / 1 defense / 2 spell power / 3 knowledge;
    // index in SSTRAITS.TXT;
    // index in SPTRAITS.TXT
    std::uint8_t reward_value {};
    ReservedData<6> unknown {};
  };

  template<>
  struct ObjectDetailsData<MetaObjectType::SEERS_HUT>
  {
    Quest quest;
    Reward reward;
    ReservedData<2> unknown {};
  };

  template<>
  struct ObjectDetailsData<MetaObjectType::SHRINE>
  {
    // 0xFF means random.
    std::uint32_t spell{};
  };

  template<>
  struct ObjectDetailsData<MetaObjectType::SIGN>
  {
    // Empty string means random message.
    std::string message;
    // Should be 0s.
    ReservedData<4> unknown {};
  };

  template<>
  struct ObjectDetailsData<MetaObjectType::SPELL_SCROLL>
  {
    std::optional<Guardians> guardians;
    std::uint32_t spell {};
  };

  struct TownBuildings
  {
    // Each bit indicates whether the building is built.
    BitSet<6> is_built {};
    // Each bit indicates whether the building is disabled.
    BitSet<6> is_disabled {};
  };

  struct TownEvent : TimedEventBase
  {
    // Each bit indicates whether the building gets built.
    BitSet<6> buildings;
    // Extra creatures for each creature level.
    std::array<std::uint16_t, 7> creatures {};
    ReservedData<4> unknown;
  };

  template<>
  struct ObjectDetailsData<MetaObjectType::TOWN>
  {
    std::uint32_t absod_id {};
    // 0xFF if none.
    std::uint8_t owner {};
    // If std::nullopt, some default name will be assigned.
    std::optional<std::string> name {};
    // 0xFFFF in CreatureStack.type means no creature.
    std::optional<std::array<CreatureStack, 7>> creatures;
    Formation formation {};
    std::optional<TownBuildings> buildings;
    // This field is only read/written if !buildings.has_value().
    Bool has_fort {};
    BitSet<9> must_have_spell;
    BitSet<9> may_not_have_spell;
    std::vector<TownEvent> events;
    // For a non-random town: should be 0xFF.
    // For a random town:
    //   * 0xFF means "Same as Owner or Random".
    //   * [0; 7] means "Same as Player N".
    std::uint8_t alignment {};
    ReservedData<3> unknown;
  };

  template<>
  struct ObjectDetailsData<MetaObjectType::TRIVIAL_OWNED_OBJECT>
  {
    // 0xFF means that there is no owner.
    std::uint32_t owner {};
  };

  template<>
  struct ObjectDetailsData<MetaObjectType::WITCH_HUT>
  {
    constexpr bool isAvailable(SecondarySkillType secondary_skill) const
    {
      return skills_availability.at(static_cast<std::size_t>(secondary_skill));
    }

    constexpr void setAvailable(SecondarySkillType secondary_skill, bool is_available)
    {
      skills_availability.set(static_cast<std::size_t>(secondary_skill), is_available);
    }

    BitSet<4> skills_availability;
  };
}
