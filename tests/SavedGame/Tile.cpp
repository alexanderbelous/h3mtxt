#include "TestingUtils_H3SVG.h"

#include <h3mtxt/SavedGame/Tile.h>

#include <catch2/catch_test_macros.hpp>

#include <string_view>

using namespace std::string_view_literals;
using ::Testing_NS::asByteVector;
using ::Testing_NS::encodeAndDecodeJson;
using ::Testing_NS::encodeViaH3SVGWriter;
using ::Testing_NS::H3SVGReaderAdapter;

namespace h3svg
{
  TEST_CASE("H3SVG.TileRenderInfo", "[H3SVG]")
  {
    static constexpr TileRenderInfo kTileRenderInfo = {
      .object_idx = 15,
      .x = 3,
      .y = 1,
      .z_buffer = 2
    };
    // Binary representation of kTileRenderInfo.
    static constexpr std::string_view kBinaryData =
      "\x0f\x00" // object_idx
      "\x13"     // x, y
      "\x02"     // z_buffer
      ""sv;

    REQUIRE(asByteVector(encodeViaH3SVGWriter(kTileRenderInfo)) == asByteVector(kBinaryData));
    REQUIRE(H3SVGReaderAdapter(kBinaryData).readTileRenderInfo() == kTileRenderInfo);
    REQUIRE(encodeAndDecodeJson(kTileRenderInfo) == kTileRenderInfo);
  }

  TEST_CASE("H3SVG.Tile", "[H3SVG]")
  {
    const Tile kTile = {
      .terrain_type = TerrainType::Grass,
      .terrain_sprite = 5,
      .river_type = RiverType::Clear,
      .river_sprite = 2,
      .road_type = RoadType::Cobblestone,
      .road_sprite = 4,
      .flags1 = 1,
      .flags2 = 0,
      .object_class = static_cast<ObjectClass16>(ObjectClass::WARRIORS_TOMB),
      .object_subclass = 0,
      .object_idx = 110,
      .object_properties = { std::byte{31}, std::byte{128}, std::byte{142}, std::byte{255} },
      .objects_to_render = {
        TileRenderInfo{ .object_idx = 7, .x = 0, .y = 0, .z_buffer = 1 },
        TileRenderInfo{ .object_idx = 11, .x = 1, .y = 1, .z_buffer = 2 },
        TileRenderInfo{ .object_idx = 33, .x = 1, .y = 5, .z_buffer = 6 }
      }
    };
    // Binary representation of kTile.
    static constexpr std::string_view kBinaryData =
      "\x02" // terrain_type
      "\x05" // terrain_sprite
      "\x01" // river_type
      "\x02" // river_sprite
      "\x03" // road_type
      "\x04" // road_sprite
      "\x01" // flags1
      "\x00" // flags2
      "\x6c\x00" // object_class
      "\x00\x00" // object_subclass
      "\x6e\x00" // object_idx
      "\x1f\x80\x8e\xff" // object_properties
      "\x03\x00\x00\x00" // objects_to_render
      "\x07\x00\x00\x01"
      "\x0b\x00\x11\x02"
      "\x21\x00\x51\x06"
      ""sv;

    REQUIRE(asByteVector(encodeViaH3SVGWriter(kTile)) == asByteVector(kBinaryData));
    REQUIRE(H3SVGReaderAdapter(kBinaryData).readTile() == kTile);
    REQUIRE(encodeAndDecodeJson(kTile) == kTile);
  }
}
