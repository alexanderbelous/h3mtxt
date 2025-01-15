#pragma once

#include <h3mparser/Map/BitSet.h>
#include <h3mparser/Map/Constants/Constants.h>
#include <h3mparser/Map/Constants/CreatureType.h>
#include <h3mparser/Map/Constants/Disposition.h>
#include <h3mparser/Map/Constants/MetaObjectType.h>
#include <h3mparser/Map/Constants/ScholarRewardType.h>
#include <h3mparser/Map/Constants/SecondarySkillType.h>
#include <h3mparser/Map/Constants/SpellType.h>
#include <h3mparser/Map/CreatureStack.h>
#include <h3mparser/Map/PrimarySkills.h>
#include <h3mparser/Map/SecondarySkill.h>

#include <array>
#include <cstdint>
#include <string>
#include <type_traits>
#include <variant>

namespace h3m
{

// TODO: move to a separate header
struct Guardians
{
  std::string message;
  std::optional<std::array<CreatureStack, 7>> creatures;
};

// "Extension" of ObjectDetails specific to ObjectClass of this object.
//
// Static polymorphism is used here rather than dynamic polymorphism.
//
// Dynamic polymorphism would also work, but then I would have to implement
// parsing/serialization in H3M structures themselves, which is undesirable:
// if in the future I decide to add JSON serialization or something else, I would
// need to either add extra virtual functions, or use the Visitor pattern (essentially,
// this will become the double dispatch problem).
// Since the set of object classes is fixed (new object classes won't be added, unless
// I decide to support unofficial mods), static polymorphism should be fine.
template<MetaObjectType T>
struct ObjectDetailsData
{
  // TODO: remove the default implementation once ObjectDetailsData is specialized for all MetaObjectTypes.
};

template<>
struct ObjectDetailsData<MetaObjectType::ABANDONED_MINE>
{
  // Bitfield: LSB wood that is forced off by editor, then mercury, ore, sulfur, crystal, gems, MSB gold.
  // TODO: replace with BitSet<4> or even a custom wrapper class.
  std::uint32_t potential_resources {};
};

template<>
struct ObjectDetailsData<MetaObjectType::ARTIFACT>
{
  std::optional<Guardians> guardians;
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

template<>
struct ObjectDetailsData<MetaObjectType::MONSTER>
{
  struct MessageAndTreasure
  {
    std::string message;
    std::array<std::uint32_t, kNumResources> resources {};
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
  std::array<std::int32_t, kNumResources> resources {};
  PrimarySkills primary_skills;
  std::vector<SecondarySkill> secondary_skill;
  std::vector<std::uint16_t> artifacts;
  std::vector<SpellType> spells;
  std::vector<CreatureStack> creatures;
  std::array<std::uint8_t, 8> unknown {};
};

// TODO: use composition instead of inheritance.
template<>
struct ObjectDetailsData<MetaObjectType::EVENT> : ObjectDetailsData<MetaObjectType::PANDORAS_BOX>
{
  // TODO: replace with BitSet.
  std::uint8_t affected_players{};
  Bool applies_to_computer{};
  Bool remove_after_first_visit{};
  std::array<std::uint8_t, 4> unknown{};
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
struct ObjectDetailsData<MetaObjectType::RESOURCE>
{
  std::optional<Guardians> guardians;
  // Multiply by 100 for gold, i.e. subclass 6.
  std::uint32_t quantity {};
  std::array<std::uint8_t, 4> unknown {};
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
  std::array<std::uint8_t, 6> unknown {};
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
  std::array<std::uint8_t, 4> unknown {};
};

template<>
struct ObjectDetailsData<MetaObjectType::SPELL_SCROLL>
{
  std::optional<Guardians> guardians;
  std::uint32_t spell {};
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

// TODO: add specializations for the rest.

namespace Details_NS
{
  template<class Types>
  struct ObjectDetailsVariantTraits;

  template<std::underlying_type_t<MetaObjectType>... meta_object_type_idx>
  struct ObjectDetailsVariantTraits<std::integer_sequence<std::underlying_type_t<MetaObjectType>,
                                                          meta_object_type_idx...>>
  {
    using type = std::variant<ObjectDetailsData<static_cast<MetaObjectType>(meta_object_type_idx)>...>;
  };

  using ObjectDetailsVariant =
    typename ObjectDetailsVariantTraits<std::make_integer_sequence<std::underlying_type_t<MetaObjectType>,
                                                                   kNumMetaObjectTypes>>::type;
}

struct ObjectDetails
{
  // std::variant with kNumMetaObjectTypes alternatives, whose N-th alternative is ObjectDetailsData<N>.
  using Data = Details_NS::ObjectDetailsVariant;

  // Coordinates of the bottom right corner.
  std::uint8_t x {};
  std::uint8_t y {};
  std::uint8_t z {};
  // 0-based index of the corresponding ObjectAttributes in Map.objects_attributes.
  std::uint32_t kind {};
  // Should be all 0s; kept here for compatibility.
  std::array<std::uint8_t, 5> unknown {};
  // Object-specific data.
  // TODO: consider renaming to additional_info.
  Data details;
};

}
