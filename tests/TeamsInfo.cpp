#include "Utils.h"

#include <h3mtxt/H3JsonReader/H3MJsonReader/H3MJsonReader.h>
#include <h3mtxt/H3JsonWriter/H3MJsonWriter/H3MJsonWriter.h>
#include <h3mtxt/H3Reader/H3MReader/H3MReader.h>
#include <h3mtxt/H3Writer/H3MWriter/H3MWriter.h>
#include <h3mtxt/Map/Teams.h>

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
    // Encodes h3m::Teams via H3MWriter.
    // \param teams - input Teams.
    // \return std::string storing the encoded data.
    std::string encodeTeams(const Teams& teams)
    {
      std::ostringstream stream;
      H3MWriter{ stream }.writeData(teams);
      return std::move(stream).str();
    }

    // Decodes h3m::Teams via H3MReader.
    // \param encoded_data - input binary data.
    // \return h3m::Teams decoded from @encoded_data.
    Teams decodeTeams(std::string_view encoded_data)
    {
      std::istringstream stream{ std::string{encoded_data} };
      return H3MReader{ stream }.readTeams();
    }
  }

  TEST_CASE("H3M.Teams", "[H3M]")
  {
    SECTION("No teams")
    {
      const Teams kTeams{ .num_teams = 0 };
      // The binary representation of kTeams.
      static constexpr char kBinaryDataCStr[] = "\x00";
      // std::string_view into kBinaryDataCStr.
      static constexpr std::string_view kBinaryData{ kBinaryDataCStr, std::size(kBinaryDataCStr) - 1 };
      REQUIRE(asByteVector(encodeTeams(kTeams)) == asByteVector(kBinaryData));
      REQUIRE(decodeTeams(kBinaryData) == kTeams);
      REQUIRE(encodeAndDecodeJson(kTeams) == kTeams);
    }
    SECTION("With teams")
    {
      const Teams kTeams{
        .num_teams = 3,
        .team_for_player {0, 0, 1, 0, 0, 0, 0, 2}
      };
      // The binary representation of kTeams.
      static constexpr char kBinaryDataCStr[] =
        "\x03"
        "\x00\x00\x01\x00\x00\x00\x00\x02";
      // std::string_view into kBinaryDataCStr.
      static constexpr std::string_view kBinaryData{ kBinaryDataCStr, std::size(kBinaryDataCStr) - 1 };
      REQUIRE(asByteVector(encodeTeams(kTeams)) == asByteVector(kBinaryData));
      REQUIRE(decodeTeams(kBinaryData) == kTeams);
      REQUIRE(encodeAndDecodeJson(kTeams) == kTeams);
    }
  }
}
