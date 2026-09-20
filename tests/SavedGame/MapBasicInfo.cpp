#include "TestingUtils_H3SVG.h"

#include <h3mtxt/Map/MapBasicInfo.h>

#include <catch2/catch_test_macros.hpp>

using namespace std::string_view_literals;
using ::Testing_NS::asByteVector;
using ::Testing_NS::encodeAndDecodeJson;
using ::Testing_NS::encodeViaH3SVGWriter;
using ::Testing_NS::H3SVGReaderAdapter;

namespace h3svg
{
  // Test encoding/decoding MapBasicInfo for H3SVG.
  TEST_CASE("H3SVG.MapBasicInfo", "[H3SVG]")
  {
    const MapBasicInfo kMapBasicInfo{
      .is_playable = 1,
      .map_size = 36,
      .has_two_levels = 0,
      .name = "Test map",
      .description = "Map description",
      .difficulty = MapDifficulty::Impossible,
      .max_hero_level = 50
    };
    // The binary representation of kMapBasicInfo.
    static constexpr std::string_view kBinaryData =  // | Type     | Field name     | Value             | Size in bytes |
                                                     // | -------- | -------------- | ----------------- | ------------- |
      "\x01"                                         // | Bool     | is_playable    | 1                 | 1             |
      "\x24\x00\x00\x00"                             // | uint32   | map_size       | 36                | 4             |
      "\x00"                                         // | Bool     | has_two_levels | 0                 | 1             |
      "\x08\x00" "Test map"                          // | String16 | name           | "Test map"        | 10            |
      "\x0f\x00" "Map description"                   // | String16 | description    | "Map description" | 17            |
      "\x04"                                         // | uint8    | difficulty     | 4                 | 1             |
      "\x32"                                         // | uint8    | max_hero_level | 50                | 1             |
      ""sv;

    REQUIRE(asByteVector(encodeViaH3SVGWriter(kMapBasicInfo)) == asByteVector(kBinaryData));
    REQUIRE(H3SVGReaderAdapter(kBinaryData).readMapBasicInfo() == kMapBasicInfo);
  }
}
