#pragma once

#include <h3mtxt/SavedGame/SavedGameFwd.h>

#include <cstdint>

namespace h3svg
{
  // Names of Seers.
  enum class SeerName : std::uint8_t
  {
    Abraham = 0,
    Goldwyn = 1,
    Bryce = 2,
    Blain = 3,
    Engle = 4,
    Carsten = 5,
    Dulcie = 6,
    Donard = 7,
    Esslock = 8,
    Evander = 9,
    Frederick = 10,
    Fay = 11,
    Genevieve = 12,
    Horace = 13,
    Heather = 14,
    Ike = 15,
    Jhem = 16,
    Julius = 17,
    Joseph = 18,
    Kae = 19,
    Kendrick = 20,
    Lynwood = 21,
    Kyriell = 22,
    Marigold = 23,
    Norwood = 24,
    Clova = 25,
    Tim = 26,
    Gier = 27,
    Paige = 28,
    Pierce = 29,
    Rae = 30,
    Raphael = 31,
    Rex = 32,
    Hester = 33,
    Spiridion = 34,
    Skye = 35,
    Rival = 36,
    Timeus = 37,
    Sulmand = 38,
    Rizlav = 39,
    Violet = 40,
    Wendell = 41,
    Winston = 42,
    Xanthe = 43,
    Xavier = 44,
    Yvette = 45,
    Zaray = 46,
    Zoe = 47
  };

  inline constexpr std::uint8_t kNumSeerNames = 48;
}
