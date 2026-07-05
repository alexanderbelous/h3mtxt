#pragma once

#include <h3mtxt/SavedGame/SavedGameFwd.h>

#include <cstdint>

namespace h3svg
{
  // Valid values for object_subclass for h3m::ObjectClass::BOAT.
  enum class BoatType : std::uint8_t
  {
    Necropolis = 0,
    Castle = 1,
    Fortress = 2
  };

  inline constexpr std::uint8_t kNumBoatTypes = 3;
}