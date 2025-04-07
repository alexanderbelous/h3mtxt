#pragma once

#include <h3mtxt/Map/MapFwd.h>
#include <h3mtxt/Map/Utils/EnumBitmask.h>
#include <h3mtxt/Map/Utils/ReservedData.h>
#include <h3mtxt/Map/Resources.h>

#include <cstdint>
#include <string>

namespace h3m
{
  // Event that is triggered on a specific day.
  //
  // This class is used in 2 places:
  // * Map::global_events.
  // * As a base class for TownEvent.
  struct TimedEvent
  {
    // The name of the event as shown in the Editor.
    std::string name;
    std::string message;
    // Given/taken resources.
    Resources resources;
    PlayersBitmask affected_players;
    Bool applies_to_human {};
    Bool applies_to_computer {};
    // 0-based day of first occurence (e.g., 0 stands for Day 1).
    std::uint16_t day_of_first_occurence {};
    // Frequency of this event; 0 means that the event doesn't repeat.
    // The Editor only allows setting a value from a small set (0-7, 14, 21, 28); if you set another value manually
    // and try to view it in the Editor, it will freeze. The game handles it correctly, though.
    // Note: some other parsers interpret this as uint8_t and the `unknown` field below as 17 bytes, but this
    // is incorrect - for example, you can add an event that repeats every 256 days.
    std::uint16_t repeat_after_days {};
    // Reserved data; should be 0s.
    ReservedData<16> unknown {};
  };
}
