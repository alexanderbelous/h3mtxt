#include "TestUtils_H3M.h"

#include <h3mtxt/Map/MapAdditionalInfo.h>

#include <catch2/catch_test_macros.hpp>

#include <string_view>

using namespace std::string_view_literals;
using ::Testing_NS::asByteVector;
using ::Testing_NS::encodeAndDecodeJson;
using ::Testing_NS::encodeViaH3MWriter;
using ::Testing_NS::H3MReaderAdapter;

namespace h3m
{
  TEST_CASE("H3M.MapAdditionalInfo", "[H3M]")
  {
    // MapAdditionalInfo used in this test.
    const MapAdditionalInfo kMapAdditionalInfo{
      .victory_condition = VictoryCondition{
        .details = VictoryConditionDetails<VictoryConditionType::AcquireArtifact>{
          SpecialVictoryConditionBase{.allow_normal_win = 0, .applies_to_computer = 0},
          ArtifactType::ArmageddonsBlade
        }
      },
      .loss_condition = LossCondition{
        .details = LossConditionDetails<LossConditionType::TimeExpires>{
          .days = 30
        }
      },
      .teams = Teams{
        .num_teams = 3,
        .team_for_player {0, 0, 1, 0, 0, 0, 0, 2}
      },
      .heroes_availability = []() consteval {
        HeroesBitmask bitmask;
        bitmask.set(HeroType::Orrin, true);
        bitmask.set(HeroType::Gelu, true);
        bitmask.set(HeroType::Mutare, true);
        bitmask.set(HeroType::Dracon, true);
        return bitmask;
      }(),
      .placeholder_heroes = {HeroType::Gunnar},
      .custom_heroes = {
        CustomHero{
          .type = HeroType::Gelu,
          .portrait = HeroPortrait::Default,
          .name = "",
          .can_hire = []() consteval {
            PlayersBitmask bitmask;
            bitmask.set(PlayerColor::Red, true);
            return bitmask;
          }()
        },
        CustomHero{
          .type = HeroType::Mutare,
          .portrait = HeroPortrait::Mephala,
          .name = "Jessica",
          .can_hire = []() consteval {
            PlayersBitmask bitmask;
            bitmask.set(PlayerColor::Green, true);
            return bitmask;
          }()
        }
      },
      .reserved = ReservedData<31>{},
      .disabled_artifacts = []() consteval {
        ArtifactsBitmask bitmask;
        bitmask.set(ArtifactType::CloakOfTheUndeadKing, true);
        bitmask.set(ArtifactType::AngelWings, true);
        return bitmask;
      }(),
      .disabled_spells = []() consteval {
        SpellsBitmask bitmask;
        bitmask.set(SpellType::DimensionDoor, true);
        bitmask.set(SpellType::Fly, true);
        return bitmask;
      }(),
      .disabled_skills = []() consteval {
        SecondarySkillsBitmask bitmask;
        bitmask.set(SecondarySkillType::EagleEye, true);
        return bitmask;
      }(),
      .rumors = {
        Rumor{
          .name = "Grail",
          .text = "The Grail is buried on the northern island."
        },
        Rumor{
          .name = "Walking Dead",
          .text = "The Walking Dead are great warriors!"
        }
      },
      .heroes_settings = []() {
        HeroesSettings settings;
        settings[HeroType::Dracon] = HeroSettings{
          .experience = 10000,
          .biography = "Best wizard ever",
          .gender = Gender::Male,
          .primary_skills = PrimarySkills{ 5, 5, 50, 50 }
        };
        return settings;
      }()
    };
    // The binary representation of kMapAdditionalInfo.
    static constexpr std::string_view kBinaryData =
      "\x00"                                             // victory_condition
        "\x00\x00" "\x80\x00"
      "\x02"                                             // loss_condition
        "\x1e\x00"
      "\x03"                                             // teams
        "\x00\x00\x01\x00\x00\x00\x00\x02"
      "\x01\x00\x00\x00\x00\x00\x00\x00\x00\x00"         // heroes_availability
      "\x00\x00\x00\x00\x00\x00\x00\x00\x98\x00"
      "\x01\x00\x00\x00"                                 // placeholder_heroes
        "\x55"
      "\x02"                                             // custom_heroes
        "\x94" "\xff" "\x00\x00\x00\x00" "\x01"
        "\x97" "\x10" "\x07\x00\x00\x00" "Jessica" "\x08"
      "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"         // reserved
      "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
      "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
      "\x00\x00\x00\x00\x00\x00\x00\x00\x00"             // disabled_artifacts
      "\x01\x00\x00\x00\x00\x00\x00\x04\x00"
      "\x40\x01\x00\x00\x00\x00\x00\x00\x00"             // disabled_spells
      "\x00\x08\x00\x00"                                 // disabled_skills
      "\x02\x00\x00\x00"                                 // rumors
        "\x05\x00\x00\x00" "Grail" "\x2b\x00\x00\x00" "The Grail is buried on the northern island."
        "\x0c\x00\x00\x00" "Walking Dead" "\x24\x00\x00\x00" "The Walking Dead are great warriors!"
      "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" // heroes_settings
      "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
      "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
      "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
      "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
      "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
      "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
      "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
      "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
      "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
      "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
      "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
      "\x00\x00\x00"
      "\x01"
        "\x01" "\x10\x27\x00\x00"                    // experience
        "\x00"                                       // secondary_skills
        "\x00"                                       // artifacts
        "\x01" "\x10\x00\x00\x00" "Best wizard ever" // biography
        "\x00"                                       // gender
        "\x00"                                       // spells
        "\x01" "\x05\x05\x32\x32"                    // primary_skills
      "\x00\x00\x00\x00\x00\x00\x00\x00"
      ""sv;
    REQUIRE(asByteVector(encodeViaH3MWriter(kMapAdditionalInfo)) == asByteVector(kBinaryData));
    REQUIRE(H3MReaderAdapter(kBinaryData).readMapAdditionalInfo() == kMapAdditionalInfo);
    REQUIRE(encodeAndDecodeJson(kMapAdditionalInfo) == kMapAdditionalInfo);
  }
}
