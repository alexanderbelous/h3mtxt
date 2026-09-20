#include "TestingUtils_H3SVG.h"

#include <h3mtxt/SavedGame/CampaignInfo.h>

#include <catch2/catch_test_macros.hpp>

using namespace std::string_view_literals;
using ::Testing_NS::asByteVector;
using ::Testing_NS::encodeAndDecodeJson;
using ::Testing_NS::encodeViaH3SVGWriter;
using ::Testing_NS::H3SVGReaderAdapter;

namespace h3svg
{
  TEST_CASE("H3SVG.CampaignInfo", "[H3SVG]")
  {
    const CampaignInfo kCampaignInfo = {
      .unknown1 = {0, 0, 0},
      .region_idx = 5,
      .id = CampaignId::Custom,
      .unknown2 = {0, 0},
      .starting_bonus_idx = 1,
      .filename = "Eternal Love.h3c",
      .finished_campaigns = []() consteval {
        EnumIndexedArray<CampaignId, Bool, 21> result;
        result[CampaignId::LongLiveTheQueen] = true;
        result[CampaignId::ElixirOfLife] = true;
        return result;
      }(),
      .regions = {
        RegionInfo{
          .is_completed = true,
          .days = 40,
          .score = 420,
          .order = 1,
          .unknown = 0
        },
        RegionInfo{
          .is_completed = false,
          .days = 0,
          .score = 0,
          .order = 0,
          .unknown = 0
        }
      },
      .crossover_info = {
        CrossoverInfo{
          .crossover_heroes = {}, // TODO: make non-empty
          .unknown = {
            CrossoverInfo::UnknownPair{.first = 22, .second = 1500},
            CrossoverInfo::UnknownPair{.first = 25, .second = 1900}
          }
        }
      }
    };

    static constexpr std::string_view kBinaryData =
      "\x00\x00\x00"                        // unknown
      "\x05"                                // region_idx
      "\x14"                                // id
      "\x00\x00"                            // unknown2
      "\x01"                                // starting_bonus_idx
      "\x10\x00\x00\x00" "Eternal Love.h3c" // filename
      "\x01\x00\x00\x00\x00\x00\x00"        // finished_campaigns
      "\x00\x00\x00\x00\x00\x00\x00"
      "\x00\x00\x01\x00\x00\x00\x00"
      "\x02"                                // regions
      "\x01" "\x28\x00\x00\x00" "\xa4\x01\x00\x00" "\x01" "\x00"
      "\x00" "\x00\x00\x00\x00" "\x00\x00\x00\x00" "\x00" "\x00"
      "\x01"                                // crossover_info
      "\x00"                                //   crossover_heroes
      "\x02\x00"                            //   unknown
      "\x16\x00" "\xdc\x05"
      "\x19\x00" "\x6c\x07"
      ""sv;

    REQUIRE(asByteVector(encodeViaH3SVGWriter(kCampaignInfo)) == asByteVector(kBinaryData));
    REQUIRE(H3SVGReaderAdapter(kBinaryData).readCampaignInfo() == kCampaignInfo);
    REQUIRE(encodeAndDecodeJson(kCampaignInfo) == kCampaignInfo);
  }
}
