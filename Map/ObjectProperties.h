#pragma once

#include <h3mtxt/Map/MapFwd.h>
#include <h3mtxt/Map/Constants/ArtifactType.h>
#include <h3mtxt/Map/Constants/Disposition.h>
#include <h3mtxt/Map/Constants/Formation.h>
#include <h3mtxt/Map/Constants/Gender.h>
#include <h3mtxt/Map/Constants/HeroPortrait.h>
#include <h3mtxt/Map/Constants/HeroType.h>
#include <h3mtxt/Map/Constants/ObjectPropertiesType.h>
#include <h3mtxt/Map/Constants/PlayerColor.h>
#include <h3mtxt/Map/Constants/PrimarySkillType.h>
#include <h3mtxt/Map/Constants/ScholarRewardType.h>
#include <h3mtxt/Map/Constants/SecondarySkillType.h>
#include <h3mtxt/Map/Constants/SpellType.h>
#include <h3mtxt/Map/Utils/EnumBitmask.h>
#include <h3mtxt/Map/Utils/ReservedData.h>
#include <h3mtxt/Map/CreatureStack.h>
#include <h3mtxt/Map/HeroArtifacts.h>
#include <h3mtxt/Map/PrimarySkills.h>
#include <h3mtxt/Map/Resources.h>
#include <h3mtxt/Map/Reward.h>
#include <h3mtxt/Map/SecondarySkill.h>
#include <h3mtxt/Map/TimedEvent.h>
#include <h3mtxt/Map/Quest.h>

#include <array>
#include <cstdint>
#include <optional>
#include <string>
#include <variant>
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

  // Only appears in ObjectProperties<ObjectPropertiesType::MONSTER>.
  struct MessageAndTreasure
  {
    std::string message;
    // The amount for each resource can be negative, but the logic is interesting:
    // * The Map Editor will display 0 if the amount is negative.
    // * In the game, if the amount == -N for some resource (N > 0):
    //   * if you have >= N of this resource, then you lose N units.
    //   * if you have < N of this resource, then your new amount becomes 0.
    Resources resources {};
    ArtifactType artifact = ArtifactType::None;
  };

  // Base class for ObjectProperties<ObjectPropertiesType::PANDORAS_BOX> and
  // ObjectProperties<ObjectPropertiesType::EVENT>.
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
    // FYI: Duplicate spells are OK (the Map Editor won't let you add duplicates,
    // but will display them correctly if they are already present in the .h3m file).
    // The size of the vector (i.e. number of spells) is serialized as a 8-bit integer. It seems that the game
    // uses a signed 8-bit integer: sizes [0; 127] are fine, but the game will crash if you try to use other values.
    // If it's indeed treated as signed, then it's possible that "negative" lengths are equivalent to 0
    // (no spells should be read/written), but I haven't checked it.
    std::vector<SpellType> spells;
    // FYI: if CreatureStack::count is negative, the number of creatures in the hero's stack will decrease.
    std::vector<CreatureStack> creatures;
    ReservedData<8> unknown {};
  };

  template<>
  struct ObjectProperties<ObjectPropertiesType::ABANDONED_MINE>
  {
    ResourcesBitmask potential_resources;
    ReservedData<3> unknown;
  };

  template<>
  struct ObjectProperties<ObjectPropertiesType::ARTIFACT>
  {
    std::optional<Guardians> guardians;
  };

  template<>
  struct ObjectProperties<ObjectPropertiesType::EVENT> : EventBase
  {
    PlayersBitmask affected_players;
    Bool applies_to_computer{};
    Bool remove_after_first_visit{};
    ReservedData<4> unknown2{};
  };

  template<>
  struct ObjectProperties<ObjectPropertiesType::GARRISON>
  {
    // 0xFF means no owner.
    PlayerColor owner {};
    ReservedData<3> unknown;
    // 0xFFFF in CreatureStack::type means "no creature".
    // CreatureStack::count can be negative - such stacks will be present in the garrison.
    std::array<CreatureStack, 7> creatures {};
    Bool can_remove_units {};
    ReservedData<8> unknown2;
  };

  template<>
  struct ObjectProperties<ObjectPropertiesType::GENERIC_NO_PROPERTIES>
  {
  };

  template<>
  struct ObjectProperties<ObjectPropertiesType::GRAIL>
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
  struct ObjectProperties<ObjectPropertiesType::HERO>
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
    // 0 means that the enemy hero will stand still.
    // The Map Editor will freeze if you try viewing the properties of a hero
    // whose patrol radius is outside [0; 10] and not equal to 0xFF.
    //
    // Undocumented features:
    // * Any value within [11; 127] is accepted by the game and interpreted as the radius of the patrol circle.
    // * All values outside [0; 127] are also accepted by the game, but they're equivalent to 0xFF (no patrol).
    std::int8_t patrol_radius {};
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
  struct ObjectProperties<ObjectPropertiesType::MONSTER>
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
  struct ObjectProperties<ObjectPropertiesType::PANDORAS_BOX> : EventBase
  {
  };

  // Undocumented features:
  // * You can effectively make a hero placeholder the visting hero of a town.
  //   In order for a hero placeholder to start in the town, the coordinates of the Object
  //   representing it must be exactly the same as the coordinates of the town (same as how it's
  //   done for normal visiting heroes).
  //   Both the Map Editor and the Unleashed Editor only allow setting specific and random heroes
  //   as visiting heroes. In the Unleashed Editor you can manually move the hero placeholder to
  //   the right tile, which will have the desired behavior, although the Unleashed Editor will
  //   trigger a warning about object overlap.
  //   Both the Map Editor and the Unleashed Editor incorrectly render such hero placeholders on
  //   top of the town, instead of displaying them as the visiting hero in the town settings.
  template<>
  struct ObjectProperties<ObjectPropertiesType::PLACEHOLDER_HERO>
  {
    PlayerColor owner {};
    HeroType type {};
    // Only read/written if type == 0xFF.
    std::uint8_t power_rating {};
  };

  template<>
  struct ObjectProperties<ObjectPropertiesType::QUEST_GUARD>
  {
    Quest quest;
  };

  template<>
  struct ObjectProperties<ObjectPropertiesType::RANDOM_DWELLING>
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
  struct ObjectProperties<ObjectPropertiesType::RANDOM_DWELLING_PRESET_ALIGNMENT>
  {
    // 0xFF if none.
    std::uint32_t owner {};
    std::uint8_t min_level {};
    std::uint8_t max_level {};
  };

  template<>
  struct ObjectProperties<ObjectPropertiesType::RANDOM_DWELLING_PRESET_LEVEL>
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
  struct ObjectProperties<ObjectPropertiesType::RESOURCE>
  {
    std::optional<Guardians> guardians;
    // Multiply by 100 for Gold (i.e. subclass 6); 0 means Random.
    // The Map Editor only allows setting a value within [1; 99999]. Values greater than 99999 are OK,
    // but the game uses quantity MOD 524288, so the amount will always be within [1; 524287] or Random.
    std::uint32_t quantity {};
    ReservedData<4> unknown {};
  };

  template<>
  struct ObjectProperties<ObjectPropertiesType::SCHOLAR>
  {
    // Type-safe union of types that can be used as the value of the reward given by the Scholar.
    using ScholarReward = std::variant<PrimarySkillType, SecondarySkillType, SpellType, ScholarRandomRewardType>;

    // \return the type of the reward.
    constexpr ScholarRewardType rewardType() const noexcept
    {
      const std::size_t alternative_index = reward.index();
      return alternative_index == 3 ? ScholarRewardType::Random
                                    : static_cast<ScholarRewardType>(alternative_index);
    }

    // Returns the index of the variant alternative corresponding to the given ScholarRewardType.
    // \param reward_type - type of the reward.
    // \return 0-based index of the alternative from ScholarReward corresponding to @reward_type,
    //         or std::variant_npos if there is no such alternative.
    static constexpr std::size_t getAlternativeIdx(ScholarRewardType reward_type) noexcept
    {
      switch (reward_type)
      {
      case ScholarRewardType::PrimarySkill:
      case ScholarRewardType::SecondarySkill:
      case ScholarRewardType::Spell:
        return static_cast<std::size_t>(reward_type);
      case ScholarRewardType::Random:
        return 3;
      default:
        return std::variant_npos;
      }
    }

    // In .h3m the reward is always serialized as 2 bytes: the first byte defines the type of the reward
    // (i.e. ScholarRewardType), the second byte defines the details:
    //   ScholarRewardType::PrimarySkill   -> PrimarySkillType
    //   ScholarRewardType::SecondarySkill -> SecondarySkillType
    //   ScholarRewardType::Spell          -> SpellType
    //   ScholarRewardType::Random         -> ScholarRandomRewardType (always set to 0 by the Map Editor).
    //
    // FYI: Heroes3.exe seems to be able to handle other values of ScholarRewardType without crashing
    // (it expects the details to be serialized as a single byte for all of them).
    // However, there are no "hidden" reward types:
    // * Values [3; 7], [11; 15], [19; 23], ..., [8*N+3; 8*N+7] are no-op regardless of
    //   the byte serialzed for details - no reward is given and no message is displayed.
    // * Values [8; 10], [16; 18], [24; 26], ..., [8*N; 8*N+2] are equivalent to values [0; 2]
    //   (i.e. ScholarRewardType{8} is equivalent to PrimarySkill, ScholarRewardType{9} is equivalent
    //   to SecondarySkill, etc).
    // In other words, there's no good reason to use values of ScholarRewardType other than 0, 1, 2 or 0xFF,
    // so this class doesn't support them at all.
    ScholarReward reward = ScholarRandomRewardType{};
    ReservedData<6> unknown {};
  };

  template<>
  struct ObjectProperties<ObjectPropertiesType::SEERS_HUT>
  {
    Quest quest;
    Reward reward;
    ReservedData<2> unknown {};
  };

  template<>
  struct ObjectProperties<ObjectPropertiesType::SHRINE>
  {
    // 0xFF means random.
    SpellType spell {};
    ReservedData<3> unknown;
  };

  template<>
  struct ObjectProperties<ObjectPropertiesType::SIGN>
  {
    // Empty string means random message.
    std::string message;
    // Should be 0s.
    ReservedData<4> unknown {};
  };

  template<>
  struct ObjectProperties<ObjectPropertiesType::SPELL_SCROLL>
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

  struct TownEvent : TimedEvent
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
  struct ObjectProperties<ObjectPropertiesType::TOWN>
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
  struct ObjectProperties<ObjectPropertiesType::TRIVIAL_OWNED_OBJECT>
  {
    // 0xFF means that there is no owner.
    PlayerColor owner {};
    ReservedData<3> unknown;
  };

  template<>
  struct ObjectProperties<ObjectPropertiesType::WITCH_HUT>
  {
    // Normally, the Witch Hut grants you one of the enabled skills from `potential_skills` except those
    // that are disabled globally (see MapAdditionalInfo::disabled_skills).
    //
    // Edge cases:
    // 1) If all bits [0; 27] are set to 0 in `potential_skills`, the behavior is the same as if all skills
    //    are enabled, i.e. the Witch Hut will teach you a random globally enabled skill.
    // 2) If all enabled skills are disabled globally, the Witch Hut won't teach you anything
    //    (the game will say that "it has been deserted for some time").
    SecondarySkillsBitmask potential_skills;
  };
}
