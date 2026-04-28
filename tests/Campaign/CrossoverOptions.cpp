#include "../Utils.h"

#include <h3mtxt/H3JsonReader/H3CJsonReader/H3CJsonReader.h>
#include <h3mtxt/H3JsonWriter/H3CJsonWriter/H3CJsonWriter.h>
#include <h3mtxt/H3Reader/H3CReader/H3CReader.h>
#include <h3mtxt/H3Writer/H3CWriter/H3CWriter.h>
#include <h3mtxt/Campaign/CampaignScenario.h>

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
    // Encodes h3m::CrossoverOptions via H3CWriter.
    // \param crossover_options - input CrossoverOptions.
    // \return std::string storing the encoded data.
    std::string encodeCrossoverOptions(const CrossoverOptions& crossover_options)
    {
      std::ostringstream stream;
      H3CWriter{ stream }.writeData(crossover_options);
      return std::move(stream).str();
    }

    // Decodes h3m::CrossoverOptions via H3MReader.
    // \param encoded_data - input binary data.
    // \return h3m::CrossoverOptions decoded from @encoded_data.
    CrossoverOptions decodeCrossoverOptions(std::string_view encoded_data)
    {
      std::istringstream stream{ std::string{encoded_data} };
      return H3CReader{ stream }.readCrossoverOptions();
    }
  }

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
    static constexpr char kBinaryDataCStr[] =
      "\x07"
      "\x00\x20\x00\x00" "\x00\x00\x00\x00" "\x00\x00\x00\x00" "\x00\x00\x00\x00" "\x00\x02\x00"
      "\x00\x00\x00\x00" "\x00\x00\x02\x00" "\x00\x00\x00\x00" "\x00\x00\x00\x00" "\x00\x00";

    // std::string_view into kBinaryData.
    static constexpr std::string_view kBinaryData{ kBinaryDataCStr, std::size(kBinaryDataCStr) - 1 };

    REQUIRE(asByteVector(encodeCrossoverOptions(kCrossoverOptions)) == asByteVector(kBinaryData));
    REQUIRE(decodeCrossoverOptions(kBinaryData) == kCrossoverOptions);
    REQUIRE(encodeAndDecodeJson(kCrossoverOptions) == kCrossoverOptions);
  }
}
