#pragma once

#include <h3mtxt/SavedGame/SavedGameFwd.h>

#include <string_view>

// Each overload of getEnumString follows the same pattern:
// \param value - input enum value.
// \return a human-readable name for @value,
//         or an empty string_view if @value is not a known enum constant.
namespace h3m
{
  std::string_view getEnumString(ArtifactType32 value) noexcept;

  std::string_view getEnumString(TownType32 value) noexcept;
}
