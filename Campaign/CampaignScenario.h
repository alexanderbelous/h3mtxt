#pragma once

#include <h3mtxt/Campaign/Constants/CampaignMusic.h>
#include <h3mtxt/Campaign/Constants/CampaignVideo.h>
#include <h3mtxt/Campaign/Constants/RegionColor.h>
#include <h3mtxt/Campaign/StartingOptions.h>
#include <h3mtxt/Map/Constants/MapDifficulty.h>
#include <h3mtxt/Map/Constants/MapFormat.h>
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

  struct CrossoverOptions
  {
    // Bitmask. TODO: replace with a wrapper.
    std::byte crossover_heroes_retain {};
    // Which creatures crossover heroes retain.
    // Bitmask CreatureType -> bool. TODO: replace with a wrapper.
    BitSet<19> creatures {};
    // Which artifacts crossover heroes retain.
    BitSet<18> artifacts;
  };

  struct CampaignScenario
  {
    MapFormat format = MapFormat::ShadowOfDeath;
    std::string map_filename;
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
