#pragma once

#include <h3mtxt/Map/MapFwd.h>

#include <h3mtxt/Map/Constants/PlayerColor.h>
#include <h3mtxt/Map/Constants/ResourceType.h>
#include <h3mtxt/Map/Utils/EnumBitmask.h>
#include <h3mtxt/Map/Utils/EnumIndexedArray.h>
#include <h3mtxt/Map/Utils/ReservedData.h>

#include <cstdint>
#include <string>

// ============================================================================
// On the nature of time in HoMM3.
// ----------------------------------------------------------------------------
// Like in the "The Wheel of Time", time is circular in HoMM3:
// * Each scenario starts on "Month: 1, Week: 1, Day: 1".
// * Each week has 7 days: e.g., "Month: 1, Week: 1, Day: 7" is followed by "Month: 1, Week: 2, Day: 1".
// * Each month has 4 weeks: e.g., "Month: 1, Week: 4, Day: 7" is followed by "Month: 2, Week: 1, Day: 1".
// * The game uses an unsigned 16-bit integer for the month, wrapping around on overflow:
//   "Month: 65535, Week: 4, Day: 7" is followed by "Month: 0, Week: 1, Day: 1".
//
// H3M stores the date as a signed integer representing the number of days that have passed since
// "Month: 1, Week: 1, Day: 1" (similar to Unix time):
// * Date(0)  corresponds to "Month: 1, Week: 1, Day: 1".
// * Date(1)  corresponds to "Month: 1, Week: 1, Day: 2".
// * Date(6)  corresponds to "Month: 1, Week: 1, Day: 7".
// * Date(7)  corresponds to "Month: 1, Week: 2, Day: 1".
// * Date(27) corresponds to "Month: 1, Week: 4, Day: 7".
// * Date(28) corresponds to "Month: 2, Week: 1, Day: 1".
// * In other words, "Month: M, Week: W, Day: D" corresponds to Date((M-1)*28 + (W-1)*7 + (D-1)).
// * Note that the Map Editor displays the dates as 1-based: e.g., "Month: 1, Week: 1, Day: 1"
//   is displayed as "Day 1" even though the .h3m file will store the number 0 for this date.
//
// As a consequence:
// * "Month: 0, Week: 4, Day: 7" corresponds to Date(-1)
// * "Month: 0, Week: 1, Day: 1" corresponds to Date(-28)
// ============================================================================

namespace h3m
{
  // Event that is triggered on a specific day.
  //
  // This class is used in 2 places:
  // * Map::timed_events.
  // * As a base class for TownEvent.
  struct TimedEvent
  {
    constexpr bool operator==(const TimedEvent&) const noexcept = default;

    // The name of the event as shown in the Editor.
    std::string name;
    std::string message;
    // Given/taken resources.
    Resources resources;
    PlayersBitmask affected_players;
    // Only meaningful for MapFormat::ShadowOfDeath.
    Bool applies_to_human = true;
    Bool applies_to_computer = false;
    // 0-based day of first occurence (e.g., 0 stands for "Month: 1, Week: 1, Day: 1").
    // The Map Editor only allows setting a value from [0; 671], i.e. a date within
    // ["Month: 1, Week: 1, Day: 1", "Month: 24, Week: 4, Day: 7"].
    // However, any signed 16-bit integer can be used here. Note that only values from [-28; 32767]
    // (i.e. dates within ["Month: 0, Week: 1, Day: 1"; "Month: 1171, Week: 2, Day: 1"]) are feasible:
    // events whose day of first occurence is outside of this range will never trigger.
    // * Events with the day of first occurence from [-28; -1] are extremely unlikely to trigger in any game,
    //   because they require 65535 months of gameplay.
    // See the comments above for more information about the nature of time in HoMM3.
    std::int16_t day_of_first_occurence = 0;
    // Frequency of this event; 0 means that the event doesn't repeat.
    // The Map Editor only allows setting a value from a small set (0-7, 14, 21, 28); if you set another value manually
    // and try to view it in the Editor, it will freeze. The game handles it correctly, though.
    // Note: some other parsers interpret this as uint8_t and the `unknown` field below as 17 bytes, but that
    // is incorrect - for example, you can add an event that repeats every 256 days.
    std::uint16_t repeat_after_days = 0;
    // Reserved data; should be 0s.
    ReservedData<16> unknown;
  };
}
