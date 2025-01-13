#pragma once

#include <h3mparser/Map/Constants/MetaObjectType.h>

#include <array>
#include <cstdint>

namespace h3m
{

// "Extension" of ObjectDetails specific to ObjectClass of this object.
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
