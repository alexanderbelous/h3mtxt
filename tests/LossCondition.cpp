#include <h3mtxt/H3Reader/H3MReader/H3MReader.h>
#include <h3mtxt/H3Writer/H3MWriter/H3MWriter.h>
#include <h3mtxt/Map/LossCondition.h>

#include <catch2/catch_test_macros.hpp>

#include <iterator>
#include <sstream>
#include <string>
#include <string_view>
#include <utility>

namespace h3m
{
  namespace
  {
    // Encodes h3m::LossCondition via H3MWriter.
    // \param victory_condition - input LossCondition.
    // \return std::string storing the encoded data.
    std::string encodeLossCondition(const LossCondition& loss_condition)
    {
      std::ostringstream stream;
      H3MWriter{ stream }.writeData(loss_condition);
      return std::move(stream).str();
    }

    // Decodes h3m::LossCondition via H3MReader.
    // \param encoded_data - input binary data.
    // \return h3m::LossCondition decoded from @encoded_data.
    LossCondition decodeLossCondition(std::string_view encoded_data)
    {
      std::istringstream stream{ std::string{encoded_data} };
      return H3MReader{ stream }.readLossCondition();
    }
  }

  TEST_CASE("H3M.LossCondition.LoseTown", "[H3M]")
  {
    constexpr LossCondition kLossCondition = {
      LossConditionDetails<LossConditionType::LoseTown>{
        .coordinates = Coordinates{.x = 10, .y = 20, .z = 1}
      }
    };
    static constexpr char kBinaryDataCStr[] = "\x00\x0a\x14\x01";
    static constexpr std::string_view kBinaryData{ kBinaryDataCStr, std::size(kBinaryDataCStr) - 1 };

    static_assert(kLossCondition.type() == LossConditionType::LoseTown);
    REQUIRE(encodeLossCondition(kLossCondition) == kBinaryData);
    REQUIRE(decodeLossCondition(kBinaryData) == kLossCondition);
  }

  TEST_CASE("H3M.LossCondition.LoseHero", "[H3M]")
  {
    constexpr LossCondition kLossCondition = {
      LossConditionDetails<LossConditionType::LoseHero>{
        .coordinates = Coordinates{.x = 10, .y = 20, .z = 1}
      }
    };
    static constexpr char kBinaryDataCStr[] = "\x01\x0a\x14\x01";
    static constexpr std::string_view kBinaryData{ kBinaryDataCStr, std::size(kBinaryDataCStr) - 1 };

    static_assert(kLossCondition.type() == LossConditionType::LoseHero);
    REQUIRE(encodeLossCondition(kLossCondition) == kBinaryData);
    REQUIRE(decodeLossCondition(kBinaryData) == kLossCondition);
  }

  TEST_CASE("H3M.LossCondition.TimeExpires", "[H3M]")
  {
    constexpr LossCondition kLossCondition = {
      LossConditionDetails<LossConditionType::TimeExpires>{
        .days = 99
      }
    };
    static constexpr char kBinaryDataCStr[] = "\x02\x63\x00";
    static constexpr std::string_view kBinaryData{ kBinaryDataCStr, std::size(kBinaryDataCStr) - 1 };

    static_assert(kLossCondition.type() == LossConditionType::TimeExpires);
    REQUIRE(encodeLossCondition(kLossCondition) == kBinaryData);
    REQUIRE(decodeLossCondition(kBinaryData) == kLossCondition);
  }

  TEST_CASE("H3M.LossCondition.Normal", "[H3M]")
  {
    constexpr LossCondition kLossCondition = {
      LossConditionDetails<LossConditionType::Normal>{}
    };
    static constexpr char kBinaryDataCStr[] = "\xff";
    static constexpr std::string_view kBinaryData{ kBinaryDataCStr, std::size(kBinaryDataCStr) - 1 };

    static_assert(kLossCondition.type() == LossConditionType::Normal);
    REQUIRE(encodeLossCondition(kLossCondition) == kBinaryData);
    REQUIRE(decodeLossCondition(kBinaryData) == kLossCondition);
  }
}
