#pragma once

#include <h3mtxt/Map/MapFwd.h>
#include <h3mtxt/Map/Base.h>
#include <h3mtxt/Map/Resources.h>
#include <h3mtxt/Map/Utils/EnumBitmask.h>
#include <h3mtxt/Map/Utils/ReservedData.h>

#include <cstdint>
#include <string>

namespace h3m
{
  // Base class for GlobalEvent and TownEvent.
  struct TimedEventBase
  {
    // Event name as shown in the Editor.
    std::string name;
    std::string message;
    // Given/taken resources.
    Resources resources;
    PlayersBitmask affected_players;
    Bool applies_to_human {};
    Bool applies_to_computer {};
    // 0-based day of first occurence (e.g., 0 stands for Day 1).
    std::uint16_t day_of_first_occurence {};
    // 0 means that the event doesn't repeat.
    std::uint8_t repeat_after_days {};
    // Should be 0s. Kept here for compatibility.
    ReservedData<17> unknown {};
  };
}
