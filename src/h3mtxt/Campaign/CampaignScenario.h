#pragma once

#include <h3mtxt/Campaign/CampaignFwd.h>
#include <h3mtxt/Campaign/Constants/CampaignMusic.h>
#include <h3mtxt/Campaign/Constants/CampaignVideo.h>
#include <h3mtxt/Campaign/Constants/CrossoverFeature.h>
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
    constexpr bool operator==(const CutScene&) const noexcept = default;

    CampaignVideo movie {};
    CampaignMusic music {};
    std::string message;
  };

  struct CrossoverOptions
  {
    constexpr bool operator==(const CrossoverOptions&) const noexcept = default;

    // The default value for CrossoverOptions::retained_features.
    // This reflects the behavior of the Campaign Editor: all features except Artifacts
    // are retained by default.
    static constexpr CrossoverFeaturesBitmask kDefaultRetainedFeatures = []() consteval {
        CrossoverFeaturesBitmask bitmask;
        bitmask.set(CrossoverFeature::Experience, true);
        bitmask.set(CrossoverFeature::PrimarySkills, true);
        bitmask.set(CrossoverFeature::SecondarySkills, true);
        bitmask.set(CrossoverFeature::Spells, true);
        return bitmask;
      }();

    // Bitmask indicating which features crossover heroes retain.
    CrossoverFeaturesBitmask retained_features = kDefaultRetainedFeatures;
    // Which creatures crossover heroes retain.
    CreaturesBitmask creatures;
    // Which artifacts crossover heroes retain.
    ArtifactsBitmask artifacts;
  };

  struct CampaignScenario
  {
    constexpr bool operator==(const CampaignScenario&) const noexcept = default;

    std::string map_filename;
    // The size of the map file in bytes.
    // Note that maps in .h3c aren't necessarily compressed.
    std::uint32_t map_file_size = 0;
    // 1 bit per scenario in Campaign::scenarios, indicating whether that scenario must be finished
    // before playing the current scenario.
    //
    // The Campaign Editor doesn't set bits for transitive dependencies: e.g., if scenarioA
    // has scenarioB as a prerequisite, and scenarioB has scenarioC as a prerequisite,
    // then only 1 bit will be set for scenarioA.
    //
    // Note that the bitmask is serialized as 1 byte if the number of regions N <= 8, but
    // as 2 bytes if 8 < N <= 16 ("Unholy Alliance").
    BitSet<2> prerequisites;
    RegionColor region_color = RegionColor::Red;
    MapDifficulty default_difficulty = MapDifficulty::Normal;
    // Displayed in the main menu when you right-click on the region
    // representing this scenario.
    std::string region_right_click_text;
    std::optional<CutScene> prologue;
    std::optional<CutScene> epilogue;
    CrossoverOptions crossover_options;
    StartingOptions starting_options;
  };
}
