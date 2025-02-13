#pragma once

#include <h3mtxt/Map/Utils/BitSet.h>
#include <h3mtxt/Map/Constants/Gender.h>
#include <h3mtxt/Map/HeroArtifacts.h>
#include <h3mtxt/Map/PrimarySkills.h>
#include <h3mtxt/Map/SecondarySkill.h>
#include <h3mtxt/Map/SpellsBitmask.h>

#include <cstdint>
#include <optional>
#include <string>
#include <vector>

namespace h3m
{

// Settings for a specific hero.
//
// Note that this structure doesn't contain Name, Portrait or "May be hired by" data - if any of these
// is changed, a CustomHero is created and stored in MapAdditionalInfo.
struct HeroSettings
{
  std::optional<std::uint32_t> experience;
  std::optional<std::vector<SecondarySkill>> secondary_skills;
  std::optional<HeroArtifacts> artifacts;
  std::optional<std::string> biography;
  Gender gender = Gender::Default;
  std::optional<SpellsBitmask> spells;
  std::optional<PrimarySkills> primary_skills;
};

}
