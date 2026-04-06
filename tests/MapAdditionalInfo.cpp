#include <h3mtxt/H3Reader/H3MReader/H3MReader.h>
#include <h3mtxt/H3Writer/H3MWriter/H3MWriter.h>
#include <h3mtxt/Map/MapAdditionalInfo.h>

#include <catch2/catch_test_macros.hpp>

#include <cstddef>
#include <iterator>
#include <span>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>

namespace h3m
{
  namespace
  {
    // Encodes h3m::MapAdditionalInfo via H3MWriter.
    // \param map_additional_info - input MapAdditionalInfo.
    // \return std::string storing the encoded data.
    std::string encodeMapAdditionalInfo(const MapAdditionalInfo& map_additional_info)
    {
      std::ostringstream stream;
      H3MWriter{ stream }.writeData(map_additional_info);
      return std::move(stream).str();
    }

    // Decodes h3m::MapAdditionalInfo via H3MReader.
    // \param encoded_data - input binary data.
    // \return h3m::MapAdditionalInfo decoded from @encoded_data.
    MapAdditionalInfo decodeMapAdditionalInfo(std::string_view encoded_data)
    {
      std::istringstream stream{ std::string{encoded_data} };
      return H3MReader{ stream }.readMapAdditionalInfo();
    }

    // Catch2 sometimes has issues when printing binary strings
    // (see https://github.com/catchorg/Catch2/issues/2960).
    // Until the issue is resolved, this workaround can be used.
    std::vector<std::byte> asByteVector(std::string_view data)
    {
      const std::span<const std::byte> bytes = std::as_bytes(std::span<const char>(data));
      return std::vector<std::byte>{bytes.begin(), bytes.end()};
    }
  }

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
      .teams = TeamsInfo{
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
          .description = "The Grail is buried on the northern island."
        },
        Rumor{
          .name = "Walking Dead",
          .description = "The Walking Dead are great warriors!"
        }
      },
      .heroes_settings = []() {
        HeroesSettings settings;
        settings[HeroType::Dracon] = HeroSettings{
          .experience = 10000,
          .biography = "Best wizard ever",
          .gender = Gender::Male,
          .primary_skills = PrimarySkills{
            .attack = 5,
            .defense = 5,
            .spell_power = 50,
            .knowledge = 50
          }
        };
        return settings;
      }()
    };
    // The binary representation of kMapAdditionalInfo.
    static constexpr char kBinaryDataCStr[] =
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
      "\x00\x00\x00\x00\x00\x00\x00\x00";
    // std::string_view into kBinaryDataCStr.
    static constexpr std::string_view kBinaryData{ kBinaryDataCStr, std::size(kBinaryDataCStr) - 1 };
    REQUIRE(asByteVector(encodeMapAdditionalInfo(kMapAdditionalInfo)) == asByteVector(kBinaryData));
    REQUIRE(decodeMapAdditionalInfo(kBinaryData) == kMapAdditionalInfo);
  }
}
