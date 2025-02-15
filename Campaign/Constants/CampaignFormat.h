#pragma once

#include <cstdint>

namespace h3m
{
  // Note: the values are different from MapFormat.
  enum class CampaignFormat : std::uint32_t
  {
    RestorationOfErathia = 0x04,
    ArmageddonsBlade = 0x05,
    ShadowOfDeath = 0x06,
  };
}
