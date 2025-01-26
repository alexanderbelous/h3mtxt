#pragma once

#include <h3mtxt/Map/SecondarySkillsBitmask.h>
#include <h3mtxt/H3MTxtWriter/H3MTxtWriter.h>

#include <array>
#include <cstdint>
#include <string_view>

namespace Util_NS
{
  template<>
  struct StructWriter<h3m::SecondarySkillsBitmask>
  {
    void operator()(FieldsWriter& out, const h3m::SecondarySkillsBitmask& bitmask) const
    {
      static constexpr std::uint8_t kNumBits = 32;
      static constexpr std::array<std::string_view, kNumBits> kSecondarySkillsNames{
        "pathfinding",
        "archery",
        "logistics",
        "scouting",
        "diplomacy",
        "navigation",
        "leadership",
        "wisdom",
        "mysticism",
        "luck",
        "ballistics",
        "eagle_eye",
        "necromancy",
        "estates",
        "fire_magic",
        "air_magic",
        "water_magic",
        "earth_magic",
        "scholar",
        "tactics",
        "artillery",
        "learning",
        "offense",
        "armorer",
        "intelligence",
        "sorcery",
        "resistance",
        "first_aid",
        "padding_28",
        "padding_29",
        "padding_30",
        "padding_31"
      };
      for (std::uint8_t i = 0; i < kNumBits; ++i)
      {
        out.writeField(kSecondarySkillsNames[i], bitmask[static_cast<h3m::SecondarySkillType>(i)]);
      }
    }
  };
}
