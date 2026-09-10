#pragma once

#include <h3mtxt/SavedGame/SavedGameFwd.h>

#include <cstdint>

namespace h3svg
{
  // Valid values for object_subclass for h3m::ObjectClass::CARTOGRAPHER.
  //
  // These are also used as indices in h3svg::SavedGame::cartographers.
  enum class CartographerType : std::uint8_t
  {
    Water        = 0,
    Land         = 1,
    Subterranean = 2
  };

  inline constexpr std::uint8_t kNumCartographerTypes = 3;
}
