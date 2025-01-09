#pragma once

#include <cstdint>

namespace h3m
{

enum class TerrainType : std::uint8_t
{
  Dirt = 0,
  Sand = 1,
  Grass = 2,
  Snow = 3,
  Swamp = 4,
  Rough = 5,
  Subterranean = 6,
  Lava = 7,
  Water = 8,
  Rock = 9,
};

}
