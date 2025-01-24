#pragma once

#include <h3mtxt/Map/Constants/TerrainType.h>
#include <h3mtxt/Map/Constants/RoadType.h>
#include <h3mtxt/Map/Constants/RiverType.h>

#include <cstdint>

namespace h3m
{

// Sprites for Water tiles:
//   [0; 3] - coast to the West and to the North of the tile.
//   [4; 7] - coast to the West of the tile.
//   [8; 11] - coast to the North of the tile.
//   [12; 15] v [18; 19] - coast in the SouthEastern corner of the tile.
//   [16; 17] - diagonal coast NorthWest of the tile.
//   [20; 32] - no coast.
struct Tile
{
  TerrainType terrain_type {};
  // Object subclass.
  std::uint8_t terrain_sprite {};
  RiverType river_type {};
  // (0-3 corners, 4 + , 5 6 T, 7 8 |-, 9 10 | , 11 12--)
  std::uint8_t river_sprite {};
  RoadType road_type {};
  // (0-5 corners, 6 7 |-, 8 9 T, 10 11 | , 12 13 --, 14 ', 15 -, 16 +)
  std::uint8_t road_sprite {};
  // Bitfield: horizontal terrain, vertical terrain, horizontal river, vertical river,
  //           horizontal road, vertical road, coast, favorable winds.
  // Coast is set for non-water tiles adjacent to water tiles, including corners.
  // TODO: check what happens when setting the coast bit for non-coast tiles.
  // TODO: figure out what the "favorable winds" bit does.
  std::uint8_t mirroring {};
};

// Returns the number of valid sprites for the specified terrain.
//
// FYI: there seem to be some "unused" sprites which may even render correctly (sometimes with a unique picture)
//      in the Editor, but I haven't found any that work stable in the game.
//      Examples of such "unused" sprites:
//          Grass:
//              * [0x49; 0x4E] look like some valid sprites (not always Grass) in the Editor; not tested.
//              * 0x69 looks like Rock; freezes the game.
//          Water:
//              * 0x48 looks like a Rock corner in the Editor; in the game in renders as purely black, but
//                when the hero moves it doesn't get rerendered, which looks very glitchy (previosly rendered pixels
//                at that tile will be shown instead). The game can crash because of this.
//              * 0x47 looks like another Rock corner in the Editor; I haven't tested the behavior in the game.
//              * 0x76 looks like Rock; not tested in the game.
//              * 0x40 is similar - looks like some weird shit, like a border between Water and Rock in the Editor;
//                Rock in the game; freezes the game when you move there.
//              * 0x2F looks like Rock both in the Editor and in the game, but freezes the game.
//              * [0x68; 0x70] look like some wet sand surrounded by Rock in the Editor; freezes the game.
//              * [252; 253] look like Rock. 252 appears fine in the Editor, but the game fails to start.
//                253 freezes the Editor sometimes.
//
// \param terrain - type of the terrain.
// \return the number N of valid sprites for terrain, or 0 if @terrain is not a valid terrain type.
//         The values [0; N) are safe to use in Tile.terrain_sprite for this type of the terrain.
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