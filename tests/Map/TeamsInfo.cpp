#include "TestUtils_H3M.h"

#include <h3mtxt/Map/Teams.h>

#include <catch2/catch_test_macros.hpp>

#include <string_view>

using namespace std::string_view_literals;
using ::Testing_NS::asByteVector;
using ::Testing_NS::encodeAndDecodeJson;
using ::Testing_NS::encodeViaH3MWriter;
using ::Testing_NS::H3MReaderAdapter;

namespace h3m
{
  TEST_CASE("H3M.Teams", "[H3M]")
  {
    SECTION("No teams")
    {
      const Teams kTeams{ .num_teams = 0 };
      // The binary representation of kTeams.
      static constexpr std::string_view kBinaryData = "\x00"sv;
      REQUIRE(asByteVector(encodeViaH3MWriter(kTeams)) == asByteVector(kBinaryData));
      REQUIRE(H3MReaderAdapter(kBinaryData).readTeams() == kTeams);
      REQUIRE(encodeAndDecodeJson(kTeams) == kTeams);
    }
    SECTION("With teams")
    {
      const Teams kTeams{
        .num_teams = 3,
        .team_for_player {0, 0, 1, 0, 0, 0, 0, 2}
      };
      // The binary representation of kTeams.
      static constexpr std::string_view kBinaryData =
        "\x03"
        "\x00\x00\x01\x00\x00\x00\x00\x02"sv;
      REQUIRE(asByteVector(encodeViaH3MWriter(kTeams)) == asByteVector(kBinaryData));
      REQUIRE(H3MReaderAdapter(kBinaryData).readTeams() == kTeams);
      REQUIRE(encodeAndDecodeJson(kTeams) == kTeams);
    }
  }
}
