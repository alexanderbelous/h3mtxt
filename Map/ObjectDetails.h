#pragma once

#include <h3mparser/Map/Constants/Constants.h>
#include <h3mparser/Map/Constants/CreatureType.h>
#include <h3mparser/Map/Constants/MetaObjectType.h>
#include <h3mparser/Map/CreatureStack.h>
#include <h3mparser/Map/PrimarySkills.h>
#include <h3mparser/Map/SecondarySkill.h>

#include <array>
#include <cstdint>
#include <string>

namespace h3m
{

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
struct ObjectDetailsData;

template<>
struct ObjectDetailsData<MetaObjectType::ABANDONED_MINE_ABSOD>
{
  // Bitfield: LSB wood that is forced off by editor, then mercury, ore, sulfur, crystal, gems, MSB gold.
  // TODO: replace with BitSet<4> or even a custom wrapper class.
  std::uint32_t potential_resources {};
};

template<>
struct ObjectDetailsData<MetaObjectType::GRAIL>
{
  std::uint32_t allowable_radius {};
};

// TODO: move to a separate header
struct Guardians
{
  std::string message;
  std::optional<std::array<CreatureStack, 7>> creatures;
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
  std::vector<std::uint8_t> spells;
  std::vector<CreatureStack> creatures;
  std::array<std::uint8_t, 8> unknown {};
};

template<>
struct ObjectDetailsData<MetaObjectType::EVENT> : ObjectDetailsData<MetaObjectType::PANDORAS_BOX>
{
  // TODO: replace with BitSet.
  std::uint8_t affected_players{};
  Bool applies_to_computer{};
  Bool remove_after_first_visit{};
  std::array<std::uint8_t, 4> unknown{};
};

// TODO: add specializations for the rest.

struct ObjectDetails
{
  // Coordinates of the bottom right corner.
  std::uint8_t x {};
  std::uint8_t y {};
  std::uint8_t z {};
  // 0-based index of the corresponding ObjectAttributes in Map.objects_attributes.
  std::uint32_t kind {};
  // Should be all 0s; kept here for compatibility.
  std::array<std::uint8_t, 5> unknown {};
  // TODO: add object-specific data.
};

}
