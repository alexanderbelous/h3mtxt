#include "Utils.h"

#include <h3mtxt/H3JsonReader/H3MJsonReader/H3MJsonReader.h>
#include <h3mtxt/H3JsonWriter/H3MJsonWriter/H3MJsonWriter.h>
#include <h3mtxt/H3Reader/H3MReader/H3MReader.h>
#include <h3mtxt/H3Writer/H3MWriter/H3MWriter.h>
#include <h3mtxt/Map/TeamsInfo.h>

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
    // Encodes h3m::TeamsInfo via H3MWriter.
    // \param teams - input TeamsInfo.
    // \return std::string storing the encoded data.
    std::string encodeTeamsInfo(const TeamsInfo& teams)
    {
      std::ostringstream stream;
      H3MWriter{ stream }.writeData(teams);
      return std::move(stream).str();
    }

    // Decodes h3m::TeamsInfo via H3MReader.
    // \param encoded_data - input binary data.
    // \return h3m::TeamsInfo decoded from @encoded_data.
    TeamsInfo decodeTeamsInfo(std::string_view encoded_data)
    {
      std::istringstream stream{ std::string{encoded_data} };
      return H3MReader{ stream }.readTeamsInfo();
    }
  }

  TEST_CASE("H3M.TeamsInfo", "[H3M]")
  {
    SECTION("No teams")
    {
      const TeamsInfo kTeamsInfo{ .num_teams = 0 };
      // The binary representation of kTeamsInfo.
      static constexpr char kBinaryDataCStr[] = "\x00";
      // std::string_view into kBinaryDataCStr.
      static constexpr std::string_view kBinaryData{ kBinaryDataCStr, std::size(kBinaryDataCStr) - 1 };
      REQUIRE(asByteVector(encodeTeamsInfo(kTeamsInfo)) == asByteVector(kBinaryData));
      REQUIRE(decodeTeamsInfo(kBinaryData) == kTeamsInfo);
      REQUIRE(encodeAndDecodeJson(kTeamsInfo) == kTeamsInfo);
    }
    SECTION("With teams")
    {
      const TeamsInfo kTeamsInfo{
        .num_teams = 3,
        .team_for_player {0, 0, 1, 0, 0, 0, 0, 2}
      };
      // The binary representation of kTeamsInfo.
      static constexpr char kBinaryDataCStr[] =
        "\x03"
        "\x00\x00\x01\x00\x00\x00\x00\x02";
      // std::string_view into kBinaryDataCStr.
      static constexpr std::string_view kBinaryData{ kBinaryDataCStr, std::size(kBinaryDataCStr) - 1 };
      REQUIRE(asByteVector(encodeTeamsInfo(kTeamsInfo)) == asByteVector(kBinaryData));
      REQUIRE(decodeTeamsInfo(kBinaryData) == kTeamsInfo);
      REQUIRE(encodeAndDecodeJson(kTeamsInfo) == kTeamsInfo);
    }
  }
}
