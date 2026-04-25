#include "../Utils.h"

#include <h3mtxt/H3JsonReader/H3CJsonReader/H3CJsonReader.h>
#include <h3mtxt/H3JsonWriter/H3CJsonWriter/H3CJsonWriter.h>
#include <h3mtxt/H3Reader/H3CReader/H3CReader.h>
#include <h3mtxt/H3Writer/H3CWriter/H3CWriter.h>
#include <h3mtxt/Campaign/Constants/CampaignId.h>
#include <h3mtxt/Campaign/CampaignScenario.h>
#include <h3mtxt/Map/Constants/HeroType.h>

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
    // Encodes h3m::CampaignScenario via H3CWriter.
    // \param scenario - input CampaignScenario.
    // \return std::string storing the encoded data.
    std::string encodeCampaignScenario(const CampaignScenario& scenario, CampaignId campaign_id)
    {
      std::ostringstream stream;
      H3CWriter{ stream }.writeCampaignScenario(scenario, campaign_id, scenario.map_file_size);
      return std::move(stream).str();
    }

    // Decodes h3m::CampaignScenario via H3MReader.
    // \param encoded_data - input binary data.
    // \return h3m::CampaignScenario decoded from @encoded_data.
    CampaignScenario decodeCampaignScenario(std::string_view encoded_data, CampaignId campaign_id)
    {
      std::istringstream stream{ std::string{encoded_data} };
      return H3CReader{ stream }.readCampaignScenario(campaign_id);
    }
  }

  TEST_CASE("H3M.CampaignScenario", "[H3C]")
  {
    // CampaignId must be known when reading/writing CampaignScenario.
    constexpr CampaignId kCampaignId = CampaignId::Armageddon;

    // CampaignScenario used in this test.
    const CampaignScenario kScenario = {
      .map_filename = "scenario_6.h3m",
      .map_file_size = 640000,
      .prerequisites = []() consteval {
        BitSet<2> bitmask;
        bitmask.set(2, true);
        bitmask.set(4, true);
        return bitmask;
      }(),
      .region_color = RegionColor::Blue,
      .default_difficulty = MapDifficulty::Impossible,
      .region_right_click_text = "Never gonna give you up, never gonna let you down",
      .prologue = CutScene{
        .movie = CampaignVideo::DragonSlayer_a,
        .music = CampaignMusic::Rampart,
        .message = "Episode I"
      },
      .epilogue = std::nullopt,
      .crossover_options = {
        .retained_features = []() consteval {
            CrossoverFeaturesBitmask bitmask;
            bitmask.set(CrossoverFeature::Experience, true);
            bitmask.set(CrossoverFeature::PrimarySkills, true);
            bitmask.set(CrossoverFeature::SecondarySkills, true);
            return bitmask;
          }(),
        .creatures = []() consteval {
            CreaturesBitmask bitmask;
            bitmask.set(CreatureType::Peasant, true);
            return bitmask;
          }(),
        .artifacts = []() consteval {
            ArtifactsBitmask bitmask;
            bitmask.set(ArtifactType::BirdOfPerception, true);
            return bitmask;
          }()
      },
      .starting_options = {
        .details = StartingOptionsDetails<StartingOptionsType::StartingBonus>{
          .player = PlayerColor::Green,
          .options = {
            StartingBonus{
              .details = StartingBonusDetails<StartingBonusType::Creature>{
                .hero = static_cast<std::uint16_t>(HeroType::Gunnar),
                .creature_stack = {
                  .type = CreatureType::BlackDragon,
                  .count = 1
                }
              }
            },
            StartingBonus{
              .details = StartingBonusDetails<StartingBonusType::SpellScroll>{
                .hero = static_cast<std::uint16_t>(HeroType::Gunnar),
                .spell = SpellType::MeteorShower
              }
            }
          }
        }
      }
    };

    // The binary representation of kScenario.
    static constexpr char kBinaryDataCStr[] =
      "\x0e\x00\x00\x00" "scenario_6.h3m" // map_filename
      "\x00\xc4\x09\x00"                  // map_file_size
      "\x14"                              // prerequisites
      "\x01"                              // region_color
      "\x04"                              // default_difficulty
      "\x31\x00\x00\x00"                  // region_right_click_text
      "Never gonna give you up, never gonna let you down"
      "\x01"                              // prologue
      "\x26"
      "\x12"
      "\x09\x00\x00\x00" "Episode I"
      "\x00"                              // epilogue
      "\x07"                              // crossover_options
      "\x00\x00\x00\x00" "\x00\x00\x00\x00" "\x00\x00\x00\x00" "\x00\x00\x00\x00" "\x00\x08\x00"
      "\x00\x00\x00\x00" "\x00\x00\x00\x80" "\x00\x00\x00\x00" "\x00\x00\x00\x00" "\x00\x00"
      "\x01"                              // starting_options
      "\x03"
      "\x02"
      "\x01" "\x55\x00" "\x53\x00" "\x01\x00"
      "\x04" "\x55\x00" "\x17";

    // std::string_view into kBinaryData.
    static constexpr std::string_view kBinaryData{ kBinaryDataCStr, std::size(kBinaryDataCStr) - 1 };

    REQUIRE(asByteVector(encodeCampaignScenario(kScenario, kCampaignId)) == asByteVector(kBinaryData));
    REQUIRE(decodeCampaignScenario(kBinaryData, kCampaignId) == kScenario);
    REQUIRE(encodeAndDecodeJson(kScenario) == kScenario);
  }
}
