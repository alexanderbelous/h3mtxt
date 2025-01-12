#pragma once

#include <h3mparser/Map/Constants/Constants.h>
#include <h3mparser/Map/Base.h>

#include <array>
#include <bitset>
#include <cstdint>
#include <string>

namespace h3m
{

struct GlobalEvent
{
  // Event name as shown in the Editor.
  std::string name;
  std::string message;
  // Given/taken resources.
  std::array<std::int32_t, kNumResources> resources {};
  std::bitset<kMaxPlayers> affected_players {};
  Bool applies_to_human {};
  Bool applies_to_computer {};
  // 0-based day of first occurence (e.g., 0 stands for Day 1).
  std::uint16_t day_of_first_occurence {};
  // 0 means that the event doesn't repeat.
  std::uint8_t repeat_after_days {};
  // Should be 0s. Kept here for compatibility.
  std::array<std::uint8_t, 17> unknown {};
};

}
