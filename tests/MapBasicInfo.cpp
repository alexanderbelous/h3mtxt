#include "JsonUtils.h"

#include <h3mtxt/H3JsonReader/H3MJsonReader/H3MJsonReader.h>
#include <h3mtxt/H3JsonWriter/H3MJsonWriter/H3MJsonWriter.h>
#include <h3mtxt/H3Reader/H3MReader/H3MReader.h>
#include <h3mtxt/H3Writer/H3MWriter/H3MWriter.h>
#include <h3mtxt/Map/MapBasicInfo.h>

#include <catch2/catch_test_macros.hpp>

#include <iterator>
#include <sstream>
#include <string>
#include <string_view>

namespace h3m
{
  // MapBasicInfo used in tests in this file.
  static const MapBasicInfo kMapBasicInfo{
    .is_playable = 1,
    .map_size = 36,
    .has_two_levels = 0,
    .name = "Test map",
    .description = "Map description",
    .difficulty = MapDifficulty::Impossible,
    .max_hero_level = 50
  };

  // Test encoding/decoding MapBasicInfo for H3M.
  TEST_CASE("H3M.MapBasicInfo", "[H3M]")
  {
    // The binary representation of kMapBasicInfo.
    static constexpr char kBinaryDataCStr[] =  // | Type     | Field name     | Value             | Size in bytes |
                                               // | -------- | -------------- | ----------------- | ------------- |
      "\x01"                                   // | Bool     | is_playable    | 1                 | 1             |
      "\x24\x00\x00\x00"                       // | uint32   | map_size       | 36                | 4             |
      "\x00"                                   // | Bool     | has_two_levels | 0                 | 1             |
      "\x08\x00\x00\x00" "Test map"            // | String32 | name           | "Test map"        | 12            |
      "\x0f\x00\x00\x00" "Map description"     // | String32 | description    | "Map description" | 19            |
      "\x04"                                   // | uint8    | difficulty     | 4                 | 1             |
      "\x32";                                  // | uint8    | max_hero_level | 50                | 1             |

    // std::string_view into kBinaryData.
    static constexpr std::string_view kBinaryData{ kBinaryDataCStr, std::size(kBinaryDataCStr) - 1 };

    SECTION("Encode")
    {
      std::ostringstream stream;
      H3MWriter{ stream }.writeData(kMapBasicInfo);
      REQUIRE(stream.view() == kBinaryData);
    }

    SECTION("Decode")
    {
      std::istringstream stream{ std::string{kBinaryData}};
      REQUIRE(H3MReader{ stream }.readMapBasicInfo() == kMapBasicInfo);
    }
  }

  // Test encoding/decoding MapBasicInfo for JSON.
  TEST_CASE("H3Json.MapBasicInfo", "[H3Json]")
  {
    // We don't check that the output JSON is equal to some string - that's stupid. We only check that
    // serializing MapBasicInfo to JSON and then deserializing it results in an equal object.
    // TODO: prepare JSON Schema for H3M and check that the the output JSON satisfies that schema.
    REQUIRE(h3json::encodeAndDecodeJson(kMapBasicInfo) == kMapBasicInfo);
  }
}
