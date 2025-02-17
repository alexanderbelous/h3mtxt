#pragma once

#include <h3mtxt/Map/MapFwd.h>
#include <h3mtxt/Map/Constants/ArtifactType.h>
#include <h3mtxt/Map/Constants/Disposition.h>
#include <h3mtxt/Map/Constants/Formation.h>
#include <h3mtxt/Map/Constants/Gender.h>
#include <h3mtxt/Map/Constants/HeroPortrait.h>
#include <h3mtxt/Map/Constants/HeroType.h>
#include <h3mtxt/Map/Constants/MetaObjectType.h>
#include <h3mtxt/Map/Constants/PlayerColor.h>
#include <h3mtxt/Map/Constants/ScholarRewardType.h>
#include <h3mtxt/Map/Constants/SpellType.h>
#include <h3mtxt/Map/Utils/BitSet.h>
#include <h3mtxt/Map/Utils/EnumBitmask.h>
#include <h3mtxt/Map/Utils/ReservedData.h>
#include <h3mtxt/Map/Base.h>
#include <h3mtxt/Map/CreatureStack.h>
#include <h3mtxt/Map/HeroArtifacts.h>
#include <h3mtxt/Map/PrimarySkills.h>
#include <h3mtxt/Map/Resources.h>
#include <h3mtxt/Map/Reward.h>
#include <h3mtxt/Map/SecondarySkill.h>
#include <h3mtxt/Map/TimedEventBase.h>
#include <h3mtxt/Map/Quest.h>

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

  // Only appears in ObjectDetailsData<MetaObjectType::MONSTER>.
  struct MessageAndTreasure
  {
    std::string message;
    Resources<std::uint32_t> resources {};
    // 0xFFFF means no artifact.
    ArtifactType artifact {};
  };

  // Base class for ObjectDetailsData<MetaObjectType::PANDORAS_BOX> and
  // ObjectDetailsData<MetaObjectType::EVENT>.
  struct EventBase
  {
    std::optional<Guardians> guardians;
    std::uint32_t experience {};
    std::int32_t spell_points {};
    std::int8_t morale {};
    std::int8_t luck {};
    Resources<std::int32_t> resources;
    // FYI: the Map Editor interprets the value of each primary skill as int8_t (not uint8_t),
    // but in the game negative values are ignored (they have the same effect as 0).
    PrimarySkills primary_skills;
    // FYI: you can add more than 8 secondary skills, but the game will only consider the first 8
    // (the rest will be ignored).
    std::vector<SecondarySkill> secondary_skills;
    std::vector<ArtifactType> artifacts;
    std::vector<SpellType> spells;
    std::vector<CreatureStack> creatures;
    ReservedData<8> unknown {};
  };

  template<>
  struct ObjectDetailsData<MetaObjectType::ABANDONED_MINE>
  {
    ResourcesBitmask potential_resources;
    ReservedData<3> unknown;
  };

  template<>
  struct ObjectDetailsData<MetaObjectType::ARTIFACT>
  {
    std::optional<Guardians> guardians;
  };

  template<>
  struct ObjectDetailsData<MetaObjectType::EVENT> : EventBase
  {
    PlayersBitmask affected_players;
    Bool applies_to_computer{};
    Bool remove_after_first_visit{};
    ReservedData<4> unknown2{};
  };

  template<>
  struct ObjectDetailsData<MetaObjectType::GARRISON>
  {
    // 0xFF means no owner.
    // TODO: replace with PlayerColor. Note that sizeof(PlayerColor) == 1,
    // so you'll need to add ReservedData<3> after it.
    std::uint32_t owner {};
    // 0xFFFF in CreatureStack.type means "no creature".
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
  // TODO: this implies that you can set name, portrait, biography and gender for a random hero,
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
    std::optional<HeroPortrait> portrait;
    // The size of the vector is serialized as uint32.
    // If 2 or more elements have the same SecondarySkillType, the game will only
    // consider the first such element (and its level).
    std::optional<std::vector<SecondarySkill>> secondary_skills;
    // 0xFFFF in CreatureStack.type means no creature.
    std::optional<std::array<CreatureStack, 7>> creatures;
    Formation formation {};
    std::optional<HeroArtifacts> artifacts;
    // 0xFF means no patrol.
    std::uint8_t patrol_radius {};
    std::optional<std::string> biography;
    Gender gender {};
    std::optional<SpellsBitmask> spells;
    std::optional<PrimarySkills> primary_skills;
    // 0s by default; kept here for compatibility.
    ReservedData<16> unknown;
  };

  template<>
  struct ObjectDetailsData<MetaObjectType::MONSTER>
  {
    std::uint32_t absod_id {};
    // 0 means random.
    std::uint16_t count {};
    Disposition disposition {};
    std::optional<MessageAndTreasure> message_and_treasure;
    Bool never_flees {};
    Bool does_not_grow {};
    ReservedData<2> unknown;
  };

  template<>
  struct ObjectDetailsData<MetaObjectType::PANDORAS_BOX> : EventBase
  {
  };

  template<>
  struct ObjectDetailsData<MetaObjectType::PLACEHOLDER_HERO>
  {
    PlayerColor owner {};
    HeroType type {};
    // Only read/written if type == 0xFF.
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
    TownsBitmask alignment;
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
    TownsBitmask alignment;
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
    // TODO: consider replacing with std::variant<Empty, PrimarySkillType, SecondarySkillType, Spell>.
    ScholarRewardType reward_type {};
    // The meaning of reward_value depends on reward_type:
    //   Random:
    //     should be 0.
    //   PrimarySkill:
    //     static_cast<PrimarySkillType>(reward_value)
    //   SecondarySkill:
    //     static_cast<SecondarySkillType>(reward_value)
    //   Spell:
    //     static_cast<SpellType>(reward_value)
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
    // h3mlib and h3m2json interpret this a bit differently: they act as if the spell is written as uint32,
    // even though the last 3 bytes should always be 0. I think it makes more sense to interpet this as
    // 1 byte for the spell followed by 3 reserved bytes; besides, it improves type safety.
    // 0xFF means random.
    SpellType spell {};
    ReservedData<3> unknown;
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
    // FYI: unlike SHRINE, 0xFF is not allowed here (causes the game to crash).
    SpellType spell {};
    ReservedData<3> unknown;
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
    // FYI: this is "semi-signed":
    // * The Map Editor displays numbers > 32767 as negative numbers.
    // * In the game, however, the behavior varies:
    //   * When the event occurs, the numbers are unsigned (e.g, "65535 Archangels arrive to Innsmouth").
    //   * On the Castle Screen the numbers are signed (e.g., "-399 Archangels available").
    //   * In Kingdom Overview the numbers are also signed (both in vanilla and in HD mod).
    //   * (HD mod only) On the Town Screen the numbers are unsigned (e.g., "65137 Archangels available").
    // In the vanilla game you cannot hire creatures if the available amount is negative. In HD mod,
    // however, you can use Ctrl+LeftMouseButton the maximum possible amount of creatures (within the available
    // resources), and HD mod incorrectly interprets this as an unsigned number. Looks like a bug in HD mod.
    std::array<std::uint16_t, 7> creatures {};
    ReservedData<4> unknown2;
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
    std::optional<std::array<CreatureStack, 7>> garrison;
    Formation formation {};
    std::optional<TownBuildings> buildings;
    // This field is only read/written if !buildings.has_value().
    Bool has_fort {};
    SpellsBitmask must_have_spell;
    SpellsBitmask may_not_have_spell;
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
    SecondarySkillsBitmask potential_skills;
  };
}
