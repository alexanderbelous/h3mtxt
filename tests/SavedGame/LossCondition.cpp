#include "TestingUtils_H3SVG.h"

#include <h3mtxt/SavedGame/LossCondition.h>

#include <catch2/catch_test_macros.hpp>

#include <string_view>

using namespace std::string_view_literals;
using ::Testing_NS::asByteVector;
using ::Testing_NS::encodeAndDecodeJson;
using ::Testing_NS::encodeViaH3SVGWriter;
using ::Testing_NS::H3SVGReaderAdapter;

namespace h3svg
{
  TEST_CASE("H3SVG.LossCondition.LoseTown", "[H3SVG]")
  {
    constexpr LossConditionType kType = LossConditionType::LoseTown;
    constexpr LossConditionDetails<kType> kDetails = {
      h3m::LossConditionDetails<kType>{
        .coordinates = {.x = 12, .y = 44, .z = 1}
      }
    };
    constexpr LossCondition kLossCondition = { .details = kDetails };
    constexpr std::string_view kBinaryData = "\x00" "\x0c\x2c\x01" ""sv;
    constexpr std::string_view kBinaryDataDetails = kBinaryData.substr(1);

    REQUIRE(asByteVector(encodeViaH3SVGWriter(kDetails)) == asByteVector(kBinaryDataDetails));
    REQUIRE(H3SVGReaderAdapter(kBinaryDataDetails).readLossConditionDetails<kType>() == kDetails);
    REQUIRE(encodeAndDecodeJson(kDetails) == kDetails);

    REQUIRE(asByteVector(encodeViaH3SVGWriter(kLossCondition)) == asByteVector(kBinaryData));
    REQUIRE(H3SVGReaderAdapter(kBinaryData).readLossCondition() == kLossCondition);
    REQUIRE(encodeAndDecodeJson(kLossCondition) == kLossCondition);
  }

  TEST_CASE("H3SVG.LossCondition.LoseHero", "[H3SVG]")
  {
    constexpr LossConditionType kType = LossConditionType::LoseHero;
    constexpr LossConditionDetails<kType> kDetails = {
      .hero = static_cast<HeroType16>(HeroType::Mephala)
    };
    constexpr LossCondition kLossCondition = { .details = kDetails };
    constexpr std::string_view kBinaryData = "\x01" "\x10\x00" ""sv;
    constexpr std::string_view kBinaryDataDetails = kBinaryData.substr(1);

    REQUIRE(asByteVector(encodeViaH3SVGWriter(kDetails)) == asByteVector(kBinaryDataDetails));
    REQUIRE(H3SVGReaderAdapter(kBinaryDataDetails).readLossConditionDetails<kType>() == kDetails);
    REQUIRE(encodeAndDecodeJson(kDetails) == kDetails);

    REQUIRE(asByteVector(encodeViaH3SVGWriter(kLossCondition)) == asByteVector(kBinaryData));
    REQUIRE(H3SVGReaderAdapter(kBinaryData).readLossCondition() == kLossCondition);
    REQUIRE(encodeAndDecodeJson(kLossCondition) == kLossCondition);
  }

  TEST_CASE("H3SVG.LossCondition.TimeExpires", "[H3SVG]")
  {
    constexpr LossConditionType kType = LossConditionType::TimeExpires;
    constexpr LossConditionDetails<kType> kDetails = {
      h3m::LossConditionDetails<kType>{
        .days = 128
      }
    };
    constexpr LossCondition kLossCondition = { .details = kDetails };
    constexpr std::string_view kBinaryData = "\x02" "\x80\x00" ""sv;
    constexpr std::string_view kBinaryDataDetails = kBinaryData.substr(1);

    REQUIRE(asByteVector(encodeViaH3SVGWriter(kDetails)) == asByteVector(kBinaryDataDetails));
    REQUIRE(H3SVGReaderAdapter(kBinaryDataDetails).readLossConditionDetails<kType>() == kDetails);
    REQUIRE(encodeAndDecodeJson(kDetails) == kDetails);

    REQUIRE(asByteVector(encodeViaH3SVGWriter(kLossCondition)) == asByteVector(kBinaryData));
    REQUIRE(H3SVGReaderAdapter(kBinaryData).readLossCondition() == kLossCondition);
    REQUIRE(encodeAndDecodeJson(kLossCondition) == kLossCondition);
  }

  TEST_CASE("H3SVG.LossCondition.Normal", "[H3SVG]")
  {
    constexpr LossConditionType kType = LossConditionType::Normal;
    constexpr LossConditionDetails<kType> kDetails{};
    constexpr LossCondition kLossCondition = { .details = kDetails };
    constexpr std::string_view kBinaryData = "\xff"sv;
    constexpr std::string_view kBinaryDataDetails = kBinaryData.substr(1);

    REQUIRE(asByteVector(encodeViaH3SVGWriter(kDetails)) == asByteVector(kBinaryDataDetails));
    REQUIRE(H3SVGReaderAdapter(kBinaryDataDetails).readLossConditionDetails<kType>() == kDetails);
    REQUIRE(encodeAndDecodeJson(kDetails) == kDetails);

    REQUIRE(asByteVector(encodeViaH3SVGWriter(kLossCondition)) == asByteVector(kBinaryData));
    REQUIRE(H3SVGReaderAdapter(kBinaryData).readLossCondition() == kLossCondition);
    REQUIRE(encodeAndDecodeJson(kLossCondition) == kLossCondition);
  }
}
