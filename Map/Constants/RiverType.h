#pragma once

#include <cstdint>

namespace h3m
{
  enum class RiverType : std::uint8_t
  {
    None = 0,
    Clear = 1,
    Icy = 2,
    Muddy = 3,
    Lava = 4,
  };

  // Returns the number of valid sprites for the specified RiverType.
  //
  // \param river_type - type of the river.
  // \return the number N of valid sprites for @river_type, or 0 if @river_type is not a valid river type.
  //         The values [0; N) are safe to use in Tile::river_sprite for @river_type.
  constexpr std::uint8_t countSprites(RiverType river_type) noexcept
  {
    switch (river_type)
    {
    case RiverType::None:
      return 1;
    case RiverType::Clear:
    case RiverType::Icy:
    case RiverType::Muddy:
    case RiverType::Lava:
      return 13;
    default:
      return 0;
    }
  }

  // ===============================================================================
  //  ____      ____  _       _______     ____  _____  _____  ____  _____   ______
  // |_  _|    |_  _|/ \     |_   __ \   |_   \|_   _||_   _||_   \|_   _|.' ___  |
  //   \ \  /\  / / / _ \      | |__) |    |   \ | |    | |    |   \ | | / .'   \_|
  //    \ \/  \/ / / ___ \     |  __ /     | |\ \| |    | |    | |\ \| | | |   ____
  //     \  /\  /_/ /   \ \_  _| |  \ \_  _| |_\   |_  _| |_  _| |_\   |_\ `.___]  |
  //      \/  \/|____| |____||____| |___||_____|\____||_____||_____|\____|`._____.'
  //
  // ===============================================================================
  //
  // RiverType should be within [0; 4], but the game *sometimes* can handle some
  // other values, rendering non-road sprites for them.
  //
  // This is not guaranteed to work: the behavior depends on how memory is allocated
  // for sprites. Memory for Terrain sprites is allocated first, followed by rivers,
  // and then roads (credits to RoseKavalier for this information). The memory
  // allocator may or may not allocate all of them contiguously; if it does, then
  // values [246; 255] for RiverType will be equivalent to values [0; 9] for TerrainType
  // (i.e. the 0th sprite for RiverType{246} will be the 0th sprite for TerrainType::Dirt).
  //
  // Even though this is not reliable behavior, I thought it's worth mentioning here.
  //
  // * RiverType{6}   -> RoadType::Dirt
  // * RiverType{7}   -> RoadType::Gravel
  // * RiverType{8}   -> RoadType::Cobblestone
  // * RiverType{15}  -> 4 sprites for "uncharted territory"
  // * RiverType{17}  -> 4 sprites for "uncharted territory"
  // * RiverType{246} -> TerrainType::Dirt
  // * RiverType{247} -> TerrainType::Sand
  // * RiverType{248} -> TerrainType::Grass
  // * RiverType{249} -> TerrainType::Snow
  // * RiverType{250} -> TerrainType::Swamp
  // * RiverType{251} -> TerrainType::Rough
  // * RiverType{252} -> TerrainType::Subterranean
  // * RiverType{253} -> TerrainType::Lava
  // * RiverType{254} -> TerrainType::Water
  // * RiverType{255} -> TerrainType::Rock
}
