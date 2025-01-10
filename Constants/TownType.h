#pragma once

#include <cstdint>

namespace h3m
{

enum class TownType : std::uint8_t
{
  Castle = 0,
  Rampart = 1,
  Tower = 2,
  Inferno = 3,
  Necropolis = 4,
  Dungeon = 5,
  Stronghold = 6,
  Fortress = 7,
  Conflux = 8,
  Random = 0xFF,
};

}
