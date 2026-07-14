#include "../Utils.h"

#include <h3mtxt/H3Reader/H3SVGReader/H3SVGReader.h>
#include <h3mtxt/H3Writer/H3SVGWriter/H3SVGWriter.h>
#include <h3mtxt/Map/MapBasicInfo.h>

#include <catch2/catch_test_macros.hpp>

#include <iterator>
#include <sstream>
#include <string>
#include <string_view>
#include <utility>

using ::Testing_NS::asByteVector;

namespace h3svg
{
  namespace
  {
    // Encodes h3m::MapBasicInfo via H3MWriter.
    // \param map_basic_info - input MapBasicInfo.
    // \return std::string storing the encoded data.
    std::string encodeMapBasicInfo(const MapBasicInfo& map_basic_info)
    {
      std::ostringstream stream;
      H3SVGWriter{ stream }.writeData(map_basic_info);
      return std::move(stream).str();
    }

    // Decodes h3m::MapBasicInfo via H3MReader.
    // \param encoded_data - input binary data.
    // \return h3m::MapBasicInfo decoded from @encoded_data.
    MapBasicInfo decodeMapBasicInfo(std::string_view encoded_data)
    {
      std::istringstream stream{ std::string{encoded_data} };
      return H3SVGReader{ stream }.readMapBasicInfo();
    }
  }

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
    static constexpr char kBinaryDataCStr[] =  // | Type     | Field name     | Value             | Size in bytes |
                                               // | -------- | -------------- | ----------------- | ------------- |
      "\x01"                                   // | Bool     | is_playable    | 1                 | 1             |
      "\x24\x00\x00\x00"                       // | uint32   | map_size       | 36                | 4             |
      "\x00"                                   // | Bool     | has_two_levels | 0                 | 1             |
      "\x08\x00" "Test map"                    // | String16 | name           | "Test map"        | 10            |
      "\x0f\x00" "Map description"             // | String16 | description    | "Map description" | 17            |
      "\x04"                                   // | uint8    | difficulty     | 4                 | 1             |
      "\x32";                                  // | uint8    | max_hero_level | 50                | 1             |

    // std::string_view into kBinaryData.
    static constexpr std::string_view kBinaryData{ kBinaryDataCStr, std::size(kBinaryDataCStr) - 1 };

    REQUIRE(asByteVector(encodeMapBasicInfo(kMapBasicInfo)) == asByteVector(kBinaryData));
    REQUIRE(decodeMapBasicInfo(kBinaryData) == kMapBasicInfo);
  }
}
