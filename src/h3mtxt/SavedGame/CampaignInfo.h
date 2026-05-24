#pragma once

#include <h3mtxt/SavedGame/SavedGameFwd.h>

#include <array>
#include <cstdint>
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
    // TODO: figure out what this is.
    // * unknown[5] seems to specify the order in which scenarios were completed:
    //   * 1 if this is the first completed scenario.
    //   * 2 if this is the second completed scenario.
    //   * ...
    // * unknown[6] seems to be "is completed or started": the value is 0xFF if the scenario
    //   has been neither completed nor started, 0 otherwise.
    std::array<std::uint8_t, 6> unknown {};
  };

  // Starting settings for a campaign scenario.
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
    std::array<std::uint8_t, 21> unknown3;
    // Information for each region in this campaign.
    // H3SVC explicitly serializes the length as an 8-bit integer.
    std::vector<RegionInfo> regions;
    // TODO: figure out what this is. The type seems to be Bool.
    std::uint8_t unknown4 {};
  };
}
