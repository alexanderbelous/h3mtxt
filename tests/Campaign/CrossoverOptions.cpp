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
  TEST_CASE("H3M.CrossoverOptions", "[H3C]")
  {
    // CrossoverOptions used in this test.
    static constexpr CrossoverOptions kCrossoverOptions{
      .retained_features = []() consteval {
          CrossoverFeaturesBitmask bitmask;
          bitmask.set(CrossoverFeature::Experience, true);
          bitmask.set(CrossoverFeature::PrimarySkills, true);
          bitmask.set(CrossoverFeature::SecondarySkills, true);
          return bitmask;
        }(),
      .creatures = []() consteval {
          CreaturesBitmask bitmask;
          bitmask.set(CreatureType::Archangel, true);
          bitmask.set(CreatureType::Sharpshooter, true);
          return bitmask;
        }(),
      .artifacts = []() consteval {
          ArtifactsBitmask bitmask;
          bitmask.set(ArtifactType::BadgeOfCourage, true);
          return bitmask;
        }()
    };

    // The binary representation of kCrossoverOptions.
    static constexpr std::string_view kBinaryData =
      "\x07"
      "\x00\x20\x00\x00" "\x00\x00\x00\x00" "\x00\x00\x00\x00" "\x00\x00\x00\x00" "\x00\x02\x00"
      "\x00\x00\x00\x00" "\x00\x00\x02\x00" "\x00\x00\x00\x00" "\x00\x00\x00\x00" "\x00\x00"
      ""sv;

    REQUIRE(asByteVector(encodeViaH3CWriter(kCrossoverOptions)) == asByteVector(kBinaryData));
    REQUIRE(H3CReaderAdapter(kBinaryData).readCrossoverOptions() == kCrossoverOptions);
    REQUIRE(encodeAndDecodeJson(kCrossoverOptions) == kCrossoverOptions);
  }
}
