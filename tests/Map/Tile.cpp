#include "TestUtils_H3M.h"

#include <h3mtxt/Map/Tile.h>

#include <catch2/catch_test_macros.hpp>

#include <string_view>

using namespace std::string_view_literals;
using ::Testing_NS::asByteVector;
using ::Testing_NS::encodeAndDecodeJson;
using ::Testing_NS::encodeViaH3MWriter;
using ::Testing_NS::H3MReaderAdapter;

namespace h3m
{
  TEST_CASE("H3M.Tile", "[H3M]")
  {
    // Tile used in this test.
    static constexpr Tile kTile{
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
    static constexpr std::string_view kBinaryData = "\x02\x07\x01\x04\x03\x09\x44"sv;

    REQUIRE(asByteVector(encodeViaH3MWriter(kTile)) == asByteVector(kBinaryData));
    REQUIRE(H3MReaderAdapter(kBinaryData).readTile() == kTile);
    REQUIRE(encodeAndDecodeJson(kTile) == kTile);
  }
}
