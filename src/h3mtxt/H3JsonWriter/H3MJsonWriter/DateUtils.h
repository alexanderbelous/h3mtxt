#pragma once

#include <cstdint>
#include <string>

// Not a part of the public API.
namespace h3json::Detail_NS
{
  // Formats the input HoMM3 date as a string.
  // \param date - input date as the number of days since "Month: 1, Week: 1, Day: 1". For example:
  //        * 0 corresponds to "Month: 1, Week: 1, Day: 1"
  //        * 1 corresponds to "Month: 1, Week: 1, Day: 2"
  //        * 6 corresponds to "Month: 1, Week: 1, Day: 7"
  //        Note that only values from [-28; 1'834'979] (i.e. dates within
  //        ["Month: 0, Week: 1, Day: 1"; "Month: 65535, Week: 4, Day: 7"]) are meaningful:
  //        the others never occur in HoMM3.
  // \return the string representation of @date in the form of "Month: %d, Week: %d, Day: %d".
  std::string makeDateComment(std::int32_t date);

  // The earliest date in HoMM3 (Month: 0, Week: 1, Day: 1).
  inline constexpr std::int32_t kDateMinFeasible = -28;
  // The latest date in HoMM3 (Month: 65535, Week: 4, Day: 7).
  inline constexpr std::int32_t kDateMaxFeasible = 1'834'979;
}
