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
    // Encodes h3m::CutScene via H3CWriter.
    // \param cutscene - input CutScene.
    // \return std::string storing the encoded data.
    std::string encodeCutScene(const CutScene& cutscene)
    {
      std::ostringstream stream;
      H3CWriter{ stream }.writeData(cutscene);
      return std::move(stream).str();
    }

    // Decodes h3m::CutScene via H3MReader.
    // \param encoded_data - input binary data.
    // \return h3m::CutScene decoded from @encoded_data.
    CutScene decodeCutScene(std::string_view encoded_data)
    {
      std::istringstream stream{ std::string{encoded_data} };
      return H3CReader{ stream }.readCutScene();
    }
  }

  TEST_CASE("H3M.CutScene", "[H3C]")
  {
    // CutScene used in this test.
    const CutScene kCutScene{
      .movie = CampaignVideo::DragonSlayer_a,
      .music = CampaignMusic::TowerTown,
      .message = "Episode I"
    };

    // The binary representation of kCutScene.
    static constexpr char kBinaryDataCStr[] = "\x26" "\x11" "\x09\x00\x00\x00" "Episode I";

    // std::string_view into kBinaryData.
    static constexpr std::string_view kBinaryData{ kBinaryDataCStr, std::size(kBinaryDataCStr) - 1 };

    REQUIRE(asByteVector(encodeCutScene(kCutScene)) == asByteVector(kBinaryData));
    REQUIRE(decodeCutScene(kBinaryData) == kCutScene);
    REQUIRE(encodeAndDecodeJson(kCutScene) == kCutScene);
  }
}
