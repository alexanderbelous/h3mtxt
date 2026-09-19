#include "../Utils.h"
#include "TestingUtils_H3SVG.h"

#include <h3mtxt/SavedGame/SavedGame.h>

#include <catch2/catch_test_macros.hpp>

#include <string_view>

using namespace std::string_view_literals;
using ::Testing_NS::asByteVector;
using ::Testing_NS::encodeAndDecodeJson;
using ::Testing_NS::encodeViaH3SVGWriter;
using ::Testing_NS::H3SVGReaderAdapter;

namespace h3svg
{
  TEST_CASE("H3SVG.ArtifactMerchants", "[H3SVG]")
  {
    static constexpr ArtifactMerchants kArtifactMerchants{
      .artifacts = {
        static_cast<ArtifactType32>(ArtifactType::BadgeOfCourage),
        static_cast<ArtifactType32>(ArtifactType::CentaurAxe),
        static_cast<ArtifactType32>(ArtifactType::CloverOfFortune),
        static_cast<ArtifactType32>(ArtifactType::EndlessBagOfGold),
        static_cast<ArtifactType32>(ArtifactType::BowOfElvenCherrywood),
        static_cast<ArtifactType32>(ArtifactType::None),
        static_cast<ArtifactType32>(ArtifactType::None)
      }
    };
    static constexpr std::string_view kBinaryData =
      "\x31\x00\x00\x00" "\x07\x00\x00\x00" "\x2e\x00\x00\x00" "\x74\x00\x00\x00"
      "\x3c\x00\x00\x00" "\xff\xff\xff\xff" "\xff\xff\xff\xff"
      ""sv;

    REQUIRE(asByteVector(encodeViaH3SVGWriter(kArtifactMerchants)) == asByteVector(kBinaryData));
    REQUIRE(H3SVGReaderAdapter(kBinaryData).readArtifactMerchants() == kArtifactMerchants);
    REQUIRE(encodeAndDecodeJson(kArtifactMerchants) == kArtifactMerchants);
  }
}
