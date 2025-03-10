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
#include <h3mtxt/Map/Utils/EnumBitmask.h>
#include <h3mtxt/Map/Utils/ReservedData.h>
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
  // Appears in ARTIFACT, EVENT, PANDORAS_BOX, RESOURCE, SPELL_SCROLL.
  struct Guardians
  {
    std::string message;
    // FYI: CreatureStack::count can be negative. Stacks with negative numbers of creatures will be
    // present on the battlefield, but the behavior is weird (such a stack can only move 1 hex during the 1st turn,
    // and then it will never get a chance to move again).
    std::optional<std::array<CreatureStack, 7>> creatures;
    ReservedData<4> unknown;
  };

  // Only appears in ObjectProperties<MetaObjectType::MONSTER>.
  struct MessageAndTreasure
  {
    std::string message;
    // The amount for each resource can be negative, but the logic is interesting:
    // * The Map Editor will display 0 if the amount is negative.
    // * In the game, if the amount == -N for some resource (N > 0):
    //   * if you have >= N of this resource, then you lose N units.
    //   * if you have < N of this resource, then your new amount becomes 0.
    Resources resources {};
    // 0xFFFF means no artifact.
    ArtifactType artifact {};
  };

  // Base class for ObjectProperties<MetaObjectType::PANDORAS_BOX> and
  // ObjectProperties<MetaObjectType::EVENT>.
  struct EventBase
  {
    std::optional<Guardians> guardians;
    // The Map Editor only allows using values from [0; 99999999].
    // Negative experience points are allowed, but the game ignores them (they have the same effect as 0).
    std::int32_t experience {};
    std::int32_t spell_points {};
    std::int8_t morale {};
    std::int8_t luck {};
    Resources resources;
    // FYI: in the game negative values are ignored (they have the same effect as 0).
    PrimarySkills primary_skills;
    // FYI: you can add more than 8 secondary skills, but the game will only consider the first 8
    // (the rest will be ignored).
    std::vector<SecondarySkill> secondary_skills;
    std::vector<ArtifactType> artifacts;
    std::vector<SpellType> spells;
    // FYI: if CreatureStack::count is negative, the number of creatures in the hero's stack will decrease.
    std::vector<CreatureStack> creatures;
    ReservedData<8> unknown {};
  };

  template<>
  struct ObjectProperties<MetaObjectType::ABANDONED_MINE>
  {
    ResourcesBitmask potential_resources;
    ReservedData<3> unknown;
  };

  template<>
  struct ObjectProperties<MetaObjectType::ARTIFACT>
  {
    std::optional<Guardians> guardians;
  };

  template<>
  struct ObjectProperties<MetaObjectType::EVENT> : EventBase
  {
    PlayersBitmask affected_players;
    Bool applies_to_computer{};
    Bool remove_after_first_visit{};
    ReservedData<4> unknown2{};
  };

  template<>
  struct ObjectProperties<MetaObjectType::GARRISON>
  {
    // 0xFF means no owner.
    // TODO: replace with PlayerColor. Note that sizeof(PlayerColor) == 1,
    // so you'll need to add ReservedData<3> after it.
    std::uint32_t owner {};
    // 0xFFFF in CreatureStack::type means "no creature".
    // CreatureStack::count can be negative - such stacks will be present in the garrison.
    std::array<CreatureStack, 7> creatures {};
    Bool can_remove_units {};
    ReservedData<8> unknown;
  };

  template<>
  struct ObjectProperties<MetaObjectType::GENERIC_NO_PROPERTIES>
  {
  };

  template<>
  struct ObjectProperties<MetaObjectType::GRAIL>
  {
    // The Map Editor only allows values from [0; 127], but any 8-bit integer can be used here.
    // The Map Editor interprets it as int8_t, but the game interprets it as uint8_t: 0xFF means 255, not -1.
    std::uint8_t allowable_radius {};
    ReservedData<3> unknown;
  };

  // Additional info for ObjectClass::HERO, ObjectClass::RANDOM_HERO and ObjectClass::PRISON.
  //
  // This struct is similar to HeroSettings, but it has extra fields in between, so I'm not reusing that struct.
  //
  // Undocumented features:
  // 1. Neither the official Map Editor nor the Unleashed Editor supports setting a custom name
  //    portrait, biography or gender for a Random Hero. The behavior is well-defined, though, if you do it manually:
  //    * A custom name will be correctly shown in the game.
  //    * A custom biography will be correctly shown in the game.
  //    * A custom portrait will NOT be shown in the game - a random hero will get the default portrait for this HeroType
  //      (which can still be customized through `MapAdditionalInfo::custom_heroes`.
  //    * Customizing the gender seems to work fine, but it has no visible impact on the game anyway.
  // 2. Neither the official Map Editor nor the Unleashed Editor supports putting a random hero in a Prison.
  //    The game does support it, though, and you can customize the name/biography of such random hero as described
  //    above.
  //    Note, however, that both the official Map Editor and the Unleashed Editor will report an error
  //    "Invalid or corrupt map file." if you try to open a map that has a random hero in a Prison.
  template<>
  struct ObjectProperties<MetaObjectType::HERO>
  {
    std::uint32_t absod_id {};
    // Owner for HERO and RANDOM_HERO. For PRISON it is normally set to 0xFF (none); setting a different value doesn't
    // seem to have any effect - you will still become the owner when you release the hero from the prison.
    PlayerColor owner {};
    // 0xFF if random.
    HeroType type {};
    std::optional<std::string> name;
    // Note: in RoE/AB experience is not optional.
    std::optional<std::int32_t> experience;
    std::optional<HeroPortrait> portrait;
    // The size of the vector is serialized as uint32.
    // If 2 or more elements have the same SecondarySkillType, the game will only
    // consider the first such element (and its level).
    std::optional<std::vector<SecondarySkill>> secondary_skills;
    // 0xFFFF in CreatureStack::type means no creature.
    // If CreatureStack::count <= 0 for any slot, this slot will become empty when the game starts.
    std::optional<std::array<CreatureStack, 7>> creatures;
    Formation formation {};
    std::optional<HeroArtifacts> artifacts;
    // The Map Editor only allows values from [0; 10] or 0xFF (no patrol).
    // TODO: check what other values do, especially the ones > 127.
    std::uint8_t patrol_radius {};
    std::optional<std::string> biography;
    Gender gender {};
    std::optional<SpellsBitmask> spells;
    // Treated as uint8_t in the Map Editor; in the game they will be initialized as int8_t,
    // so 0xFF becomes -1.
    // Negative Attack/Defense is displayed as 0 and is treated as 0 during combat.
    // Nonpositive Spell Power/Knowledge is displayed as 1 and is treated as 1.
    std::optional<PrimarySkills> primary_skills;
    // 0s by default; kept here for compatibility.
    ReservedData<16> unknown;
  };

  template<>
  struct ObjectProperties<MetaObjectType::MONSTER>
  {
    std::uint32_t absod_id {};
    // The Map Editor only allows values from [0; 4000] (0 means random), but any 16-bit integer can be used here.
    // However, in the game the number of creatures will be initialized with count % 4096 (4096 also means random),
    // so values > 4095 are somewhat useless.
    std::uint16_t count {};
    Disposition disposition {};
    std::optional<MessageAndTreasure> message_and_treasure;
    Bool never_flees {};
    Bool does_not_grow {};
    ReservedData<2> unknown;
  };

  template<>
  struct ObjectProperties<MetaObjectType::PANDORAS_BOX> : EventBase
  {
  };

  template<>
  struct ObjectProperties<MetaObjectType::PLACEHOLDER_HERO>
  {
    PlayerColor owner {};
    HeroType type {};
    // Only read/written if type == 0xFF.
    std::uint8_t power_rating {};
  };

  template<>
  struct ObjectProperties<MetaObjectType::QUEST_GUARD>
  {
    Quest quest;
  };

  template<>
  struct ObjectProperties<MetaObjectType::RANDOM_DWELLING>
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
  struct ObjectProperties<MetaObjectType::RANDOM_DWELLING_PRESET_ALIGNMENT>
  {
    // 0xFF if none.
    std::uint32_t owner {};
    std::uint8_t min_level {};
    std::uint8_t max_level {};
  };

  template<>
  struct ObjectProperties<MetaObjectType::RANDOM_DWELLING_PRESET_LEVEL>
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
  struct ObjectProperties<MetaObjectType::RESOURCE>
  {
    std::optional<Guardians> guardians;
    // Multiply by 100 for Gold (i.e. subclass 6); 0 means Random.
    // The Map Editor only allows setting a value within [1; 99999]. Values greater than 99999 are OK,
    // but the game uses quantity MOD 524288, so the amount will always be within [1; 524287] or Random.
    std::uint32_t quantity {};
    ReservedData<4> unknown {};
  };

  template<>
  struct ObjectProperties<MetaObjectType::SCHOLAR>
  {
    // TODO: consider replacing with std::variant<PrimarySkillType, SecondarySkillType, Spell, RandomScholarRewardType>.
    ScholarRewardType reward_type {};
    // The meaning of reward_value depends on reward_type:
    //   PrimarySkill:
    //     static_cast<PrimarySkillType>(reward_value)
    //   SecondarySkill:
    //     static_cast<SecondarySkillType>(reward_value)
    //   Spell:
    //     static_cast<SpellType>(reward_value)
    //   Random:
    //     should be 0.
    std::uint8_t reward_value {};
    ReservedData<6> unknown {};
  };

  template<>
  struct ObjectProperties<MetaObjectType::SEERS_HUT>
  {
    Quest quest;
    Reward reward;
    ReservedData<2> unknown {};
  };

  template<>
  struct ObjectProperties<MetaObjectType::SHRINE>
  {
    // 0xFF means random.
    SpellType spell {};
    ReservedData<3> unknown;
  };

  template<>
  struct ObjectProperties<MetaObjectType::SIGN>
  {
    // Empty string means random message.
    std::string message;
    // Should be 0s.
    ReservedData<4> unknown {};
  };

  template<>
  struct ObjectProperties<MetaObjectType::SPELL_SCROLL>
  {
    std::optional<Guardians> guardians;
    // FYI: unlike SHRINE, 0xFF is not allowed here (causes the game to crash).
    SpellType spell {};
    ReservedData<3> unknown;
  };

  struct TownBuildings
  {
    // Each bit indicates whether the building is built.
    TownBuildingsBitmask is_built {};
    // Each bit indicates whether the building is disabled.
    TownBuildingsBitmask is_disabled {};
  };

  struct TownEvent : TimedEventBase
  {
    // Each bit indicates whether the building gets built.
    TownBuildingsBitmask buildings;
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
  struct ObjectProperties<MetaObjectType::TOWN>
  {
    std::uint32_t absod_id {};
    // 0xFF if none.
    PlayerColor owner {};
    // If std::nullopt, some default name will be assigned.
    std::optional<std::string> name {};
    // 0xFFFF in CreatureStack::type means no creature.
    // If CreatureStack::count <= 0 for any slot, this slot will become empty when the game starts.
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
  struct ObjectProperties<MetaObjectType::TRIVIAL_OWNED_OBJECT>
  {
    // 0xFF means that there is no owner.
    PlayerColor owner {};
    ReservedData<3> unknown;
  };

  template<>
  struct ObjectProperties<MetaObjectType::WITCH_HUT>
  {
    SecondarySkillsBitmask potential_skills;
  };
}
