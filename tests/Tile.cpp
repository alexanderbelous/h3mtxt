#include "Utils.h"

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
#include <utility>

using ::Testing_NS::asByteVector;
using ::Testing_NS::encodeAndDecodeJson;

namespace h3m
{
  namespace
  {
    // Encodes h3m::Tile via H3MWriter.
    // \param tile - input Tile.
    // \return std::string storing the encoded data.
    std::string encodeTile(const Tile& tile)
    {
      std::ostringstream stream;
      H3MWriter{ stream }.writeData(tile);
      return std::move(stream).str();
    }

    // Decodes h3m::Tile via H3MReader.
    // \param encoded_data - input binary data.
    // \return h3m::Tile decoded from @encoded_data.
    Tile decodeTile(std::string_view encoded_data)
    {
      std::istringstream stream{ std::string{encoded_data} };
      return H3MReader{ stream }.readTile();
    }
  }

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
    static constexpr char kBinaryDataCStr[] = "\x02\x07\x01\x04\x03\x09\x44";

    // std::string_view into kBinaryData.
    static constexpr std::string_view kBinaryData{ kBinaryDataCStr, std::size(kBinaryDataCStr) - 1 };

    REQUIRE(asByteVector(encodeTile(kTile)) == asByteVector(kBinaryData));
    REQUIRE(decodeTile(kBinaryData) == kTile);
    REQUIRE(encodeAndDecodeJson(kTile) == kTile);
  }
}
