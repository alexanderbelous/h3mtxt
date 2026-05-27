#pragma once

#include <h3mtxt/SavedGame/SavedGameFwd.h>

#include <h3mtxt/SavedGame/Hero.h>

#include <array>
#include <cstdint>
#include <optional>
#include <string>
#include <vector>

namespace h3svg
{
  struct RegionInfo
  {
    // 0 if this scenario hasn't been completed yet, nonzero otherwise.
    Bool is_completed = false;
    // The number of days that it took the player to complete this scenario.
    // The value is meaningless if is_completed == false, but the game seems to store 0 in this case.
    std::uint32_t num_days = 0;
    // Score for this scenario (see https://heroes.thelazy.net/index.php/Score).
    // The value is meaningless if is_completed == false, but the game seems to store 0 in this case.
    std::uint32_t score = 0;
    // 1-based rank of this scenario among all scenarios in the order in which they were played (ascending).
    // The value is meaningless if is_completed == false, but the game seems to store 0 in this case.
    std::uint8_t order = 0;
    // TODO: figure out what this is.
    // Seems to be "is completed or started": the value is 0xFF if the scenario
    // has been neither completed nor started, 0 otherwise.
    std::uint8_t unknown {};
  };

  struct CrossoverInfo
  {
    struct UnknownPair
    {
      // TODO: figure out what this is. Kinda looks like HeroType16, but values are not unique.
      std::uint16_t first {};
      // TODO: figure out what this is. Kinda looks like move points.
      std::uint16_t second {};
    };

    // Heroes that crossed over from earlier scenarios.
    //
    // This array stores their settings at the end of the scenario from which they crossed over.
    //
    // Note that this also contains crossover heroes for future scenarios: e.g., if
    //   * Scenario 0: you play as Gelu
    //   * Scenario 1: you play as Dracon
    //   * Scenario 2: you play as both Gelu and Dracon
    // then crossover_heroes for Scenario 1 will contain Gelu even though he's not present in that scenario.
    //
    // Length is serialized as an 8-bit integer.
    std::vector<Hero> crossover_heroes;
    // TODO: figure out what this is. Each element occupies 4 bytes.
    // Size is serialized as a 16-bit integer.
    std::vector<UnknownPair> unknown;
  };

  // Campaign-specific data stored in saved games.
  struct CampaignInfo
  {
    // TODO: figure out what this is.
    std::array<std::uint8_t, 3> unknown1 {};
    // 0-based index of the current region, i.e. the index of the relevant CampaignScenario element
    // from h3m::CampaignHeader::scenarios.
    std::uint8_t region_idx {};
    // TODO: figure out what this is.
    std::array<std::uint8_t, 3> unknown2 {};
    // 0-based index of the selected starting bonus from h3m::StartingOptions.
    std::uint8_t starting_bonus_idx {};
    // The original filename of the .h3c file (this is used by View Scenario and Restart Scenario commands).
    // Serialized in H3SVC as a length-prefixed string; the length is serialized as a little-endian 32-bit integer.
    std::string filename;
    // TODO: figure out what this is.
    // The last byte seems to indicate whether the campaign itself is completed, but only for custom campaigns
    // (i.e. not for the official NWC campaigns).
    // The other bytes seem to always be 0s for custom campaigns, but not for the official NWC campaigns.
    std::array<std::uint8_t, 21> unknown3 {};
    // Information for each region in this campaign.
    // H3SVC explicitly serializes the length as an 8-bit integer.
    std::vector<RegionInfo> regions;
    // Information about crossover heroes.
    // Length is uint8.
    std::vector<CrossoverInfo> crossover_info;
  };
}
