#pragma once

#include <h3mparser/Constants/Constants.h>

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
  bool applies_to_human {};
  bool applies_to_computer {};
  // 0-based day of first occurence (e.g., 0 stands for Day 1).
  std::uint16_t day_of_first_occurence {};
  // 0 means that the event doesn't repeat.
  std::uint8_t repeat_after_days {};
};

}
