#pragma once

#include <h3mtxt/SavedGame/SavedGameFwd.h>
#include <h3mtxt/Map/Constants/TownType.h>

#include <cstdint>

namespace h3svg
{
  // Same as h3m::TownType, but uses int32 as the underlying type.
  //
  // In H3SVG there are places where TownType is serialized as a signed 32-bit integer,
  // unlike .h3m where it's serialized as an 8-bit integer.
  // We cannot simply reuse TownType in such places because that wouldn't be lossless
  // (only the least significant byte would be preserved).
  // I don't want to use a raw integer type (int32) either, because type safety.
  //
  // So, instead this enum is defined.
  enum class TownType32 : std::int32_t
  {
    Castle = TownType::Castle,
    Rampart = TownType::Rampart,
    Tower = TownType::Tower,
    Inferno = TownType::Inferno,
    Necropolis = TownType::Necropolis,
    Dungeon = TownType::Dungeon,
    Stronghold = TownType::Stronghold,
    Fortress = TownType::Fortress,
    Conflux = TownType::Conflux,
  };
}
