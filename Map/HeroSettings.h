#pragma once

#include <h3mparser/Map/BitSet.h>
#include <h3mparser/Map/Constants/Gender.h>
#include <h3mparser/Map/Constants/SecondarySkillType.h>

#include <cstdint>
#include <optional>
#include <string>
#include <vector>

namespace h3m
{

// 0xFFFF implies "default" for any slot, whatever that means.
struct HeroArtifacts
{
  std::uint16_t headwear {};
  std::uint16_t shoulders {};
  std::uint16_t neck {};
  std::uint16_t right_hand {};
  std::uint16_t left_hand {};
  std::uint16_t torso {};
  std::uint16_t right_ring {};
  std::uint16_t left_ring {};
  std::uint16_t feet {};
  std::uint16_t misc1 {};
  std::uint16_t misc2 {};
  std::uint16_t misc3 {};
  std::uint16_t misc4 {};
  std::uint16_t device1 {};
  std::uint16_t device2 {};
  std::uint16_t device3 {};
  // Catapult's slot, not accessible via the Editor, always empty.
  std::uint16_t device4 {};
  std::uint16_t spellbook {};
  std::uint16_t misc5 {};
  std::vector<std::uint16_t> backpack;
};

// Settings for a specific hero.
//
// Note that this structure doesn't contain Name, Portrait or "May be hired by" data - if any of these
// is changed, a CustomHero is created and stored in MapAdditionalInfo.
struct HeroSettings
{
  struct SecondarySkill
  {
    SecondarySkillType type {};
    // Not really an enum, as shown by LC.
    std::uint8_t level {};
  };

  struct PrimarySkills
  {
    std::uint8_t attack {};
    std::uint8_t defense {};
    std::uint8_t spell_power {};
    std::uint8_t knowledge {};
  };

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
