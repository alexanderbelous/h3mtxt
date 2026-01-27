#pragma once

#include <cstdint>

namespace h3m
{
  enum class ScholarRewardType : std::uint8_t
  {
    PrimarySkill = 0,
    SecondarySkill = 1,
    Spell = 2,
    Random = 0xFF,
  };

  // Placeholder type used in ObjectProperties<ObjectPropertiesType::SCHOLAR>
  // for ScholarRewardType::Random.
  //
  // Unlike other reward types, ScholarRewardType::Random doesn't have configurable properties.
  // However, in .h3m a single byte is still serialized for such Scholars; the value of this byte
  // is always set to 0 by the Map Editor.
  enum class ScholarRandomRewardType : std::uint8_t
  {
    Default = 0
  };
}
