#pragma once

#include <h3mtxt/Campaign/Constants/CampaignMusic.h>
#include <h3mtxt/Campaign/Constants/CampaignVideo.h>
#include <h3mtxt/Campaign/Constants/RegionColor.h>
#include <h3mtxt/Campaign/StartingOptions.h>
#include <h3mtxt/Map/Constants/MapDifficulty.h>
#include <h3mtxt/Map/Utils/BitSet.h>

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

  // Bitset describing what crossover heroes retain.
  struct CrossoverFeatures
  {
    enum class Type : std::uint8_t
    {
      Experience = 0,
      PrimarySkills = 1,
      SecondarySkills = 2,
      Spells = 3,
      Artifacts = 4
    };

    constexpr bool operator[](Type feature) const
    {
      return bitset.at(static_cast<std::size_t>(feature));
    }

    constexpr void set(Type feature, bool value)
    {
      bitset.set(static_cast<std::size_t>(feature), value);
    }

    BitSet<1> bitset;
  };

  struct CrossoverOptions
  {
    // Bitmask indicating what crossover heroes retain.
    CrossoverFeatures retained_features;
    // Which creatures crossover heroes retain.
    // Bitmask CreatureType -> bool. TODO: replace with a wrapper.
    BitSet<19> creatures;
    // Which artifacts crossover heroes retain.
    BitSet<18> artifacts;
  };

  struct CampaignScenario
  {
    std::string map_filename;
    // The size of the gzip-compressed map file in bytes.
    std::uint32_t compressed_map_size {};
    // Bitmask.
    std::uint8_t prerequisites {};
    RegionColor region_color {};
    MapDifficulty default_difficulty {};
    std::string region_righ_click_text;
    std::optional<CutScene> prologue;
    std::optional<CutScene> epilogue;
    CrossoverOptions crossover_options;
    StartingOptions starting_options;
  };
}
