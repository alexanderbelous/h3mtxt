#include "TestUtils_H3C.h"

#include <h3mtxt/Campaign/CampaignScenario.h>

#include <catch2/catch_test_macros.hpp>

#include <string_view>

using namespace std::string_view_literals;
using ::Testing_NS::asByteVector;
using ::Testing_NS::encodeAndDecodeJson;
using ::Testing_NS::encodeViaH3CWriter;
using ::Testing_NS::H3CReaderAdapter;

namespace h3m
{
  TEST_CASE("H3M.CutScene", "[H3C]")
  {
    // CutScene used in this test.
    const CutScene kCutScene{
      .movie = CampaignVideo::DragonSlayer_a,
      .music = CampaignMusic::TowerTown,
      .message = "Episode I"
    };

    // The binary representation of kCutScene.
    static constexpr std::string_view kBinaryData = "\x26" "\x11" "\x09\x00\x00\x00" "Episode I"sv;

    REQUIRE(asByteVector(encodeViaH3CWriter(kCutScene)) == asByteVector(kBinaryData));
    REQUIRE(H3CReaderAdapter(kBinaryData).readCutScene() == kCutScene);
    REQUIRE(encodeAndDecodeJson(kCutScene) == kCutScene);
  }
}
