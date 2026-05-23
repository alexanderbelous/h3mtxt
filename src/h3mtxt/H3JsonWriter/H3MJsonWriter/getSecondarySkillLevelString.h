#pragma once

#include <h3mtxt/Map/MapFwd.h>

#include <cstdint>
#include <string_view>

namespace h3json
{
  // Returns a comment for the specified level of the given secondary skill.
  // \param skill - input secondary skill.
  // \param level - (possibly "hexed") level of @skill.
  // \return a comment for @level, or an empty string_view if this is not a known "hexed" level.
  std::string_view getSecondarySkillLevelString(h3m::SecondarySkillType skill, std::uint8_t level) noexcept;
}
