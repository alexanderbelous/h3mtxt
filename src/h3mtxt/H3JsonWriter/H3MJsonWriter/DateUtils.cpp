#include <h3mtxt/H3JsonWriter/H3MJsonWriter/DateUtils.h>

namespace h3json::Detail_NS
{
  namespace
  {
    // Components of a date in HoMM3.
    struct Date
    {
      constexpr bool operator==(const Date&) const noexcept = default;

      std::int32_t month {};
      std::uint8_t week {};
      std::uint8_t day {};
    };

    // Decomposes the input HoMM3 date into 3 values: month, week and day.
    // \param date - input date as the number of days since "Month: 1, Week: 1, Day: 1". For example:
    //        * 0 corresponds to "Month: 1, Week: 1, Day: 1"
    //        * 1 corresponds to "Month: 1, Week: 1, Day: 2"
    //        * 6 corresponds to "Month: 1, Week: 1, Day: 7"
    // \return a Date corresponding to @date.
    constexpr Date decomposeDate(std::int32_t date)
    {
      constexpr std::int32_t kNumWeeksInMonth = 4;
      constexpr std::int32_t kNumDaysInWeek = 7;
      constexpr std::int32_t kNumDaysInMonth = kNumWeeksInMonth * kNumDaysInWeek;
      std::int32_t month = static_cast<std::int32_t>(date) / kNumDaysInMonth;
      // Within [-27; 27].
      std::int32_t day_of_month = static_cast<std::int32_t>(date) % kNumDaysInMonth;
      // Normalize month and day_of_month to ensure that day_of_month is within [0; 27].
      if (day_of_month < 0)
      {
        month -= 1;
        day_of_month += kNumDaysInMonth;
      }
      return Date{
        .month = static_cast<std::int32_t>(month + 1),
        .week = static_cast<std::uint8_t>((day_of_month / kNumDaysInWeek) + 1),
        .day = static_cast<std::uint8_t>((day_of_month % kNumDaysInWeek) + 1),
      };
    }

    static_assert(decomposeDate(-28) == Date{ .month = 0, .week = 1, .day = 1 });
    static_assert(decomposeDate(-2) == Date{ .month = 0, .week = 4, .day = 6 });
    static_assert(decomposeDate(-1) == Date{ .month = 0, .week = 4, .day = 7 });
    static_assert(decomposeDate(0) == Date{ .month = 1, .week = 1, .day = 1 });
    static_assert(decomposeDate(1) == Date{ .month = 1, .week = 1, .day = 2 });
    static_assert(decomposeDate(6) == Date{ .month = 1, .week = 1, .day = 7 });
    static_assert(decomposeDate(7) == Date{ .month = 1, .week = 2, .day = 1 });
    static_assert(decomposeDate(27) == Date{ .month = 1, .week = 4, .day = 7 });
    static_assert(decomposeDate(28) == Date{ .month = 2, .week = 1, .day = 1 });
    static_assert(decomposeDate(671) == Date{ .month = 24, .week = 4, .day = 7 });
    static_assert(decomposeDate(32'767) == Date{ .month = 1171, .week = 2, .day = 1 });
    static_assert(decomposeDate(1'834'979) == Date{ .month = 65535, .week = 4, .day = 7 });
  }

  std::string makeDateComment(std::int32_t date)
  {
    const Date decomposed_date = decomposeDate(date);
    return "Month: " + std::to_string(decomposed_date.month) +
           ", Week: " + std::to_string(decomposed_date.week) +
           ", Day: " + std::to_string(decomposed_date.day);
  }
}
