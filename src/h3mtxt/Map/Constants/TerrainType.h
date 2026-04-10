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

  inline constexpr std::uint8_t kNumTerrainTypes = 10;

  // Returns the number of valid sprites for the specified terrain.
  //
  // See h3mtxt/examples/terrain_sprites_cheatsheet/terrain_sprites_cheatsheet.h3m for more
  // information; this map shows all valid sprites for each TerrainType.
  //
  // FYI: attempting to use values outside of [0; countSprites(terrain_type)) for Tile::terrain_sprite
  // generally causes the game to crash. I haven't found any "hidden" sprites that work reliably.
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
