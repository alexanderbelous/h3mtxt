#include "TestUtils_H3M.h"

#include <h3mtxt/Map/LossCondition.h>

#include <catch2/catch_test_macros.hpp>

#include <string_view>

using namespace std::string_view_literals;
using ::Testing_NS::asByteVector;
using ::Testing_NS::encodeAndDecodeJson;
using ::Testing_NS::encodeViaH3MWriter;
using ::Testing_NS::H3MReaderAdapter;

namespace h3m
{
  TEST_CASE("H3M.LossCondition.LoseTown", "[H3M]")
  {
    constexpr LossCondition kLossCondition = {
      LossConditionDetails<LossConditionType::LoseTown>{
        .coordinates = Coordinates{.x = 10, .y = 20, .z = 1}
      }
    };
    static constexpr std::string_view kBinaryData = "\x00\x0a\x14\x01"sv;

    static_assert(kLossCondition.type() == LossConditionType::LoseTown);
    REQUIRE(asByteVector(encodeViaH3MWriter(kLossCondition)) == asByteVector(kBinaryData));
    REQUIRE(H3MReaderAdapter(kBinaryData).readLossCondition() == kLossCondition);
    REQUIRE(encodeAndDecodeJson(kLossCondition) == kLossCondition);
  }

  TEST_CASE("H3M.LossCondition.LoseHero", "[H3M]")
  {
    constexpr LossCondition kLossCondition = {
      LossConditionDetails<LossConditionType::LoseHero>{
        .coordinates = Coordinates{.x = 10, .y = 20, .z = 1}
      }
    };
    static constexpr std::string_view kBinaryData = "\x01\x0a\x14\x01"sv;

    static_assert(kLossCondition.type() == LossConditionType::LoseHero);
    REQUIRE(asByteVector(encodeViaH3MWriter(kLossCondition)) == asByteVector(kBinaryData));
    REQUIRE(H3MReaderAdapter(kBinaryData).readLossCondition() == kLossCondition);
    REQUIRE(encodeAndDecodeJson(kLossCondition) == kLossCondition);
  }

  TEST_CASE("H3M.LossCondition.TimeExpires", "[H3M]")
  {
    constexpr LossCondition kLossCondition = {
      LossConditionDetails<LossConditionType::TimeExpires>{
        .days = 99
      }
    };
    static constexpr std::string_view kBinaryData = "\x02\x63\x00"sv;

    static_assert(kLossCondition.type() == LossConditionType::TimeExpires);
    REQUIRE(asByteVector(encodeViaH3MWriter(kLossCondition)) == asByteVector(kBinaryData));
    REQUIRE(H3MReaderAdapter(kBinaryData).readLossCondition() == kLossCondition);
    REQUIRE(encodeAndDecodeJson(kLossCondition) == kLossCondition);
  }

  TEST_CASE("H3M.LossCondition.Normal", "[H3M]")
  {
    constexpr LossCondition kLossCondition = {
      LossConditionDetails<LossConditionType::Normal>{}
    };
    static constexpr std::string_view kBinaryData = "\xff"sv;

    static_assert(kLossCondition.type() == LossConditionType::Normal);
    REQUIRE(asByteVector(encodeViaH3MWriter(kLossCondition)) == asByteVector(kBinaryData));
    REQUIRE(H3MReaderAdapter(kBinaryData).readLossCondition() == kLossCondition);
    REQUIRE(encodeAndDecodeJson(kLossCondition) == kLossCondition);
  }
}
