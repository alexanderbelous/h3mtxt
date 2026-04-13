#include "Utils.h"

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
#include <utility>

using ::Testing_NS::asByteVector;
using ::Testing_NS::encodeAndDecodeJson;

namespace h3m
{
  namespace
  {
    // Encodes h3m::MapBasicInfo via H3MWriter.
    // \param map_basic_info - input MapBasicInfo.
    // \return std::string storing the encoded data.
    std::string encodeMapBasicInfo(const MapBasicInfo& map_basic_info)
    {
      std::ostringstream stream;
      H3MWriter{ stream }.writeData(map_basic_info);
      return std::move(stream).str();
    }

    // Decodes h3m::MapBasicInfo via H3MReader.
    // \param encoded_data - input binary data.
    // \return h3m::MapBasicInfo decoded from @encoded_data.
    MapBasicInfo decodeMapBasicInfo(std::string_view encoded_data)
    {
      std::istringstream stream{ std::string{encoded_data} };
      return H3MReader{ stream }.readMapBasicInfo();
    }
  }

  // Test encoding/decoding MapBasicInfo for H3M.
  TEST_CASE("H3M.MapBasicInfo", "[H3M]")
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
      "\x08\x00\x00\x00" "Test map"            // | String32 | name           | "Test map"        | 12            |
      "\x0f\x00\x00\x00" "Map description"     // | String32 | description    | "Map description" | 19            |
      "\x04"                                   // | uint8    | difficulty     | 4                 | 1             |
      "\x32";                                  // | uint8    | max_hero_level | 50                | 1             |

    // std::string_view into kBinaryData.
    static constexpr std::string_view kBinaryData{ kBinaryDataCStr, std::size(kBinaryDataCStr) - 1 };

    REQUIRE(asByteVector(encodeMapBasicInfo(kMapBasicInfo)) == asByteVector(kBinaryData));
    REQUIRE(decodeMapBasicInfo(kBinaryData) == kMapBasicInfo);
    REQUIRE(encodeAndDecodeJson(kMapBasicInfo) == kMapBasicInfo);
  }
}
