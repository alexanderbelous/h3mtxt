#include <h3mtxt/H3Reader/H3MReader/H3MReader.h>
#include <h3mtxt/H3Writer/H3MWriter/H3MWriter.h>
#include <h3mtxt/Map/Tile.h>

#include <catch2/catch_test_macros.hpp>

#include <iterator>
#include <sstream>
#include <string>
#include <string_view>

namespace h3m
{
  namespace
  {
    // MapBasicInfo used in tests in this file.
    constexpr Tile kTile{
      .terrain_type = TerrainType::Grass,
      .terrain_sprite = 7,
      .river_type = RiverType::Clear,
      .river_sprite = 4,
      .road_type = RoadType::Cobblestone,
      .road_sprite = 9,
      .flags = []() consteval {
        TileFlags flags;
        flags.set(TileFlag::RiverHorizontalFlip, true);
        flags.set(TileFlag::Coast, true);
        return flags;
      }()
    };

    // The binary representation of kTile.
    constexpr char kBinaryData[] = "\x02\x07\x01\x04\x03\x09\x44";

    // std::string_view into kBinaryData.
    constexpr std::string_view kBinaryDataView{ kBinaryData, std::size(kBinaryData) - 1 };
  }

  TEST_CASE("readTile", "[H3MReader]")
  {
    std::istringstream stream{ std::string{kBinaryDataView}};
    const h3m::Tile tile = H3MReader{ stream }.readTile();

    REQUIRE(tile.terrain_type == kTile.terrain_type);
    REQUIRE(tile.terrain_sprite == kTile.terrain_sprite);
    REQUIRE(tile.river_type == kTile.river_type);
    REQUIRE(tile.river_sprite == kTile.river_sprite);
    REQUIRE(tile.road_type == kTile.road_type);
    REQUIRE(tile.road_sprite == kTile.road_sprite);
    REQUIRE(tile.flags.bitset.data == kTile.flags.bitset.data);
  }

  TEST_CASE("writeTile", "[H3MWriter]")
  {
    std::ostringstream stream;
    h3m::H3MWriter{ stream }.writeData(kTile);
    stream.flush();

    REQUIRE(stream.view() == kBinaryDataView);
  }
}
