#include "JsonUtils.h"

#include <h3mtxt/H3JsonReader/H3MJsonReader/H3MJsonReader.h>
#include <h3mtxt/H3JsonWriter/H3MJsonWriter/H3MJsonWriter.h>
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
  // Tile used in tests in this file.
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

  TEST_CASE("H3M.Tile", "[H3M]")
  {
    // The binary representation of kTile.
    static constexpr char kBinaryDataCStr[] = "\x02\x07\x01\x04\x03\x09\x44";

    // std::string_view into kBinaryData.
    static constexpr std::string_view kBinaryData{ kBinaryDataCStr, std::size(kBinaryDataCStr) - 1 };

    SECTION("Encode")
    {
      std::ostringstream stream;
      H3MWriter{ stream }.writeData(kTile);
      REQUIRE(stream.view() == kBinaryData);
    }

    SECTION("Decode")
    {
      std::istringstream stream{ std::string{kBinaryData} };
      REQUIRE(H3MReader{ stream }.readTile() == kTile);
    }
  }

  TEST_CASE("H3Json.Tile", "[H3Json]")
  {
    // We don't check that the output JSON is equal to some string - that's stupid. We only check that
    // serializing h3m::Tile to JSON and then deserializing it results in an equal object.
    // TODO: prepare JSON Schema for H3M and check that the the output JSON satisfies that schema.
    REQUIRE(h3json::encodeAndDecodeJson(kTile) == kTile);
  }
}
