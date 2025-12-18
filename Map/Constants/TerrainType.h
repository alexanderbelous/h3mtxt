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

  // Returns the number of valid sprites for the specified terrain.
  //
  // Sprites for TerrainType::Water:
  //   [0; 3] - coast to the West and to the North of the tile.
  //   [4; 7] - coast to the West of the tile.
  //   [8; 11] - coast to the North of the tile.
  //   [12; 15] v [18; 19] - coast in the SouthEastern corner of the tile.
  //   [16; 17] - diagonal coast NorthWest of the tile.
  //   [20; 32] - no coast.
  //
  // FYI: attempting to use values outside of [0; countSprites(terrain_type)) for Tile::terrain_sprite
  // doesn't seem to have any reliable behavior; it will likely cause the game to crash.
  //
  // \param terrain - type of the terrain.
  // \return the number N of valid sprites for terrain, or 0 if @terrain is not a valid terrain type.
  //         The values [0; N) are safe to use in Tile::terrain_sprite for this type of the terrain.
  constexpr std::uint8_t countSprites(TerrainType terrain) noexcept
  {
    switch (terrain)
    {
    case TerrainType::Dirt:
      return 45;
    case TerrainType::Sand:
      return 24;
    case TerrainType::Grass:
    case TerrainType::Snow:
    case TerrainType::Swamp:
    case TerrainType::Rough:
    case TerrainType::Subterranean:
    case TerrainType::Lava:
      return 73;
    case TerrainType::Water:
      return 33;
    case TerrainType::Rock:
      return 48;
    default:
      return 0;
    }
  }
}
