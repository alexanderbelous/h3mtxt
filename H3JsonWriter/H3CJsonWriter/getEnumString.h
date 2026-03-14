#pragma once

#include <h3mtxt/Campaign/CampaignFwd.h>

#include <string_view>

// Each overload of getEnumString follows the same pattern:
// \param value - input enum value.
// \return a human-readable name for @value,
//         or an empty string_view if @value is not a known enum constant.
namespace h3m
{
  std::string_view getEnumString(CampaignId value) noexcept;

  std::string_view getEnumString(CampaignMusic value) noexcept;

  std::string_view getEnumString(CampaignVideo value) noexcept;

  std::string_view getEnumString(StartingBonusResourceType value) noexcept;

  std::string_view getEnumString(StartingBonusType value) noexcept;

  std::string_view getEnumString(StartingOptionsType value) noexcept;
}
