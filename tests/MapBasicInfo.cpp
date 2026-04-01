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
  namespace
  {
    // MapBasicInfo used in tests in this file.
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
    constexpr char kBinaryData[] =      // | Type     | Field name     | Value             | Size in bytes |
                                        // | -------- | -------------- | ----------------- | ------------- |
      "\x01"                            // | Bool     | is_playable    | 1                 | 1             |
      "\x24\x00\x00\x00"                // | uint32   | map_size       | 36                | 4             |
      "\x00"                            // | Bool     | has_two_levels | 0                 | 1             |
      "\x08\x00\x00\x00Test map"        // | String32 | name           | "Test map"        | 12            |
      "\x0f\x00\x00\x00Map description" // | String32 | description    | "Map description" | 19            |
      "\x04"                            // | uint8    | difficulty     | 4                 | 1             |
      "\x32";                           // | uint8    | max_hero_level | 50                | 1             |

    // std::string_view into kBinaryData.
    constexpr std::string_view kBinaryDataView{ kBinaryData, std::size(kBinaryData) - 1 };
  }

  TEST_CASE("readMapBasicInfo", "[H3MReader]")
  {
    std::istringstream stream{ std::string{kBinaryDataView}};
    const h3m::MapBasicInfo map_basic_info = H3MReader{ stream }.readMapBasicInfo();

    REQUIRE(map_basic_info.is_playable == kMapBasicInfo.is_playable);
    REQUIRE(map_basic_info.map_size == kMapBasicInfo.map_size);
    REQUIRE(map_basic_info.has_two_levels == kMapBasicInfo.has_two_levels);
    REQUIRE(map_basic_info.name == kMapBasicInfo.name);
    REQUIRE(map_basic_info.description == kMapBasicInfo.description);
    REQUIRE(map_basic_info.difficulty == kMapBasicInfo.difficulty);
    REQUIRE(map_basic_info.max_hero_level == kMapBasicInfo.max_hero_level);
  }

  TEST_CASE("writeMapBasicInfo", "[H3MWriter]")
  {
    std::ostringstream stream;
    h3m::H3MWriter{ stream }.writeData(kMapBasicInfo);
    stream.flush();

    REQUIRE(stream.view() == kBinaryDataView);
  }
}
