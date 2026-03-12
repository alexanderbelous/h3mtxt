#pragma once

#include <h3mtxt/SavedGame/SavedGameFwd.h>

#include <h3mtxt/Map/Constants/ResourceType.h>
#include <h3mtxt/Map/Utils/EnumIndexedArray.h>
#include <h3mtxt/Map/CreatureStack.h>
#include <h3mtxt/Map/PrimarySkills.h>
#include <h3mtxt/Map/SecondarySkill.h>
#include <h3mtxt/SavedGame/Troops.h>

#include <cstdint>
#include <optional>
#include <string>
#include <vector>

namespace h3svg
{
  // Equivalent of h3m::Guardians used in H3SVG.
  struct Guardians
  {
    // Serialized in H3SVG as a length-prefixed string; length is a 16-bit little-endian integer.
    std::string message;
    std::optional<Troops> creatures;
  };

  // The equivalent of h3m::EventBase in H3SVG.
  //
  // This is nearly identical to h3m::EventBase, but there are a couple important differences:
  // * guardians are stored differently (e.g., allows stacks with > 65535 units).
  // * artifacts are stored differently (as 8-bit integers instead of 16-bit integers).
  struct EventBase
  {
    std::optional<Guardians> guardians;
    std::int32_t experience {};
    std::int32_t spell_points {};
    std::int8_t morale {};
    std::int8_t luck {};
    Resources resources;
    PrimarySkills primary_skills;
    // Size is serialzied as an 8-bit integer.
    std::vector<SecondarySkill> secondary_skills;
    // Size is serialzied as an 8-bit integer.
    std::vector<ArtifactType8> artifacts;
    // Size is serialzied as an 8-bit integer.
    std::vector<SpellType> spells;
    // Size is serialzied as an 8-bit integer.
    std::vector<CreatureStack> creatures;
  };
}
