#pragma once

#include <h3mtxt/Campaign/Constants/CampaignMusic.h>
#include <h3mtxt/Campaign/Constants/CampaignVideo.h>
#include <h3mtxt/Campaign/Constants/RegionColor.h>
#include <h3mtxt/Campaign/StartingOptions.h>
#include <h3mtxt/Map/MapFwd.h>
#include <h3mtxt/Map/Constants/MapDifficulty.h>
#include <h3mtxt/Map/Utils/BitSet.h>
#include <h3mtxt/Map/Utils/EnumBitmask.h>

#include <optional>
#include <string>

namespace h3m
{
  struct CutScene
  {
    CampaignVideo movie {};
    CampaignMusic music {};
    std::string message;
  };

  enum class CrossoverFeature : std::uint8_t
  {
    Experience = 0,
    PrimarySkills = 1,
    SecondarySkills = 2,
    Spells = 3,
    Artifacts = 4
  };

  using CrossoverFeaturesBitmask = EnumBitmask<CrossoverFeature, 1>;

  struct CrossoverOptions
  {
    // Bitmask indicating which features crossover heroes retain.
    CrossoverFeaturesBitmask retained_features;
    // Which creatures crossover heroes retain.
    CreaturesBitmask creatures;
    // Which artifacts crossover heroes retain.
    ArtifactsBitmask artifacts;
  };

  struct CampaignScenario
  {
    std::string map_filename;
    // The size of the gzip-compressed map file in bytes.
    std::uint32_t compressed_map_size {};
    // 1 bit per scenario in Campaign::scenarios, indicating whether that scenario must be finished
    // before playing the current scenario.
    //
    // The Campaign Editor doesn't set bits for transitive dependencies: e.g., if scenarioA
    // has scenarioB as a prerequisite, and scenarioB has scenarioC as a prerequisite,
    // then only 1 bit will be set for scenarioA.
    //
    // Note that the bitmask is serialized as 1 byte if the number of regions N <= 8, but
    // as 2 bytes if 8 < N <= 16 ("Unholy Alliance").
    BitSet<2> prerequisites {};
    RegionColor region_color {};
    MapDifficulty default_difficulty {};
    std::string region_righ_click_text;
    std::optional<CutScene> prologue;
    std::optional<CutScene> epilogue;
    CrossoverOptions crossover_options;
    StartingOptions starting_options;
  };
}
