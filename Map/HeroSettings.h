#pragma once

#include <h3mparser/Map/BitSet.h>
#include <h3mparser/Map/Constants/Gender.h>
#include <h3mparser/Map/Constants/SecondarySkillType.h>
#include <h3mparser/Map/HeroArtifacts.h>
#include <h3mparser/Map/PrimarySkills.h>
#include <h3mparser/Map/SecondarySkill.h>

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
  Gender gender {};
  // TODO: add a wrapper class.
  std::optional<BitSet<9>> spells;
  std::optional<PrimarySkills> primary_skills;
};

}
