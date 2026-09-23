#include "TestingUtils_H3SVG.h"

#include <h3mtxt/SavedGame/Reward.h>

#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_test_macros.hpp>

#include <string_view>
#include <type_traits>

using namespace std::string_view_literals;
using ::Testing_NS::asByteVector;
using ::Testing_NS::encodeAndDecodeJson;
using ::Testing_NS::encodeViaH3SVGWriter;
using ::Testing_NS::H3SVGReaderAdapter;

namespace h3svg
{
  namespace
  {
    // Aggregates data for a test case for h3svg::RewardDetails.
    template<RewardType T>
    struct TestCaseData
    {
      // Reward details.
      RewardDetails<T> details;
      // Bytes representing @details in H3SVG.
      std::string_view binary_data;
    };

    // Variable template providing test data for each RewardType.
    template<RewardType T>
    const TestCaseData<T> kTestCases;

    template<>
    const TestCaseData<RewardType::None> kTestCases<RewardType::None> = {
      .details = {
        .reserved {{std::byte{0}, std::byte{1}, std::byte{2}, std::byte{3},
                    std::byte{4}, std::byte{5}, std::byte{6}, std::byte{7}}}
      },
      .binary_data = "\x00\x01\x02\x03\x04\x05\x06\x07"sv
    };

    template<>
    const TestCaseData<RewardType::Experience> kTestCases<RewardType::Experience> = {
      .details = {
        .experience = 5000,
        .reserved {{std::byte{0}, std::byte{1}, std::byte{2}, std::byte{3}}}
      },
      .binary_data = "\x88\x13\x00\x00\x00\x01\x02\x03"sv
    };

    template<>
    const TestCaseData<RewardType::SpellPoints> kTestCases<RewardType::SpellPoints> = {
      .details = {
        .spell_points = 500,
        .reserved {{std::byte{0}, std::byte{1}, std::byte{2}, std::byte{3}}}
      },
      .binary_data = "\xf4\x01\x00\x00\x00\x01\x02\x03"sv
    };

    template<>
    const TestCaseData<RewardType::Morale> kTestCases<RewardType::Morale> = {
      .details = {
        .morale = 3,
        .reserved {{std::byte{0}, std::byte{1}, std::byte{2}, std::byte{3}}}
      },
      .binary_data = "\x03\x00\x00\x00\x00\x01\x02\x03"sv
    };

    template<>
    const TestCaseData<RewardType::Luck> kTestCases<RewardType::Luck> = {
      .details = {
        .luck = 2,
        .reserved {{std::byte{0}, std::byte{1}, std::byte{2}, std::byte{3}}}
      },
      .binary_data = "\x02\x00\x00\x00\x00\x01\x02\x03"sv
    };

    template<>
    const TestCaseData<RewardType::Resource> kTestCases<RewardType::Resource> = {
      .details = {
        .resource = {
          .type = static_cast<ResourceType32>(ResourceType::Gems),
          .quantity = 15
        }
      },
      .binary_data = "\x05\x00\x00\x00\x0f\x00\x00\x00"sv
    };

    template<>
    const TestCaseData<RewardType::PrimarySkill> kTestCases<RewardType::PrimarySkill> = {
      .details = {
        .type = static_cast<PrimarySkillType32>(PrimarySkillType::SpellPower),
        .value = 5
      },
      .binary_data = "\x02\x00\x00\x00\x05\x00\x00\x00"sv
    };

    template<>
    const TestCaseData<RewardType::SecondarySkill> kTestCases<RewardType::SecondarySkill> = {
      .details = {
        .type = static_cast<SecondarySkillType32>(SecondarySkillType::EarthMagic),
        .level = 3
      },
      .binary_data = "\x11\x00\x00\x00\x03\x00\x00\x00"sv
    };

    template<>
    const TestCaseData<RewardType::Artifact> kTestCases<RewardType::Artifact> = {
      .details = {
        .artifact = static_cast<ArtifactType32>(ArtifactType::AngelWings),
        .reserved {{std::byte{0}, std::byte{1}, std::byte{2}, std::byte{3}}}
      },
      .binary_data = "\x48\x00\x00\x00\x00\x01\x02\x03"sv
    };

    template<>
    const TestCaseData<RewardType::Spell> kTestCases<RewardType::Spell> = {
      .details = {
        .spell = static_cast<SpellType32>(SpellType::Resurrection),
        .reserved {{std::byte{0}, std::byte{1}, std::byte{2}, std::byte{3}}}
      },
      .binary_data = "\x26\x00\x00\x00\x00\x01\x02\x03"sv
    };

    template<>
    const TestCaseData<RewardType::Creatures> kTestCases<RewardType::Creatures> = {
      .details = {
        .creatures = {
          .type = static_cast<CreatureType32>(CreatureType::AzureDragon),
          .quantity = 1000
        }
      },
      .binary_data = "\x84\x00\x00\x00\xe8\x03\x00\x00"sv
    };

    template<RewardType T>
    using StaticConstant = std::integral_constant<RewardType, T>;
  }

  TEMPLATE_TEST_CASE("H3SVG.Reward", "[H3SVG]",
                     StaticConstant<RewardType::None>,
                     StaticConstant<RewardType::Experience>,
                     StaticConstant<RewardType::SpellPoints>,
                     StaticConstant<RewardType::Morale>,
                     StaticConstant<RewardType::Luck>,
                     StaticConstant<RewardType::Resource>,
                     StaticConstant<RewardType::PrimarySkill>,
                     StaticConstant<RewardType::SecondarySkill>,
                     StaticConstant<RewardType::Artifact>,
                     StaticConstant<RewardType::Spell>,
                     StaticConstant<RewardType::Creatures>)
  {
    static constexpr RewardType kRewardType = TestType::value;
    const TestCaseData<kRewardType>& test_case_data = kTestCases<kRewardType>;

    SECTION("Reward")
    {
      const Reward reward = { .details = test_case_data.details };
      const std::string binary_data = std::string({ static_cast<char>(kRewardType), '\0', '\0', '\0' }) +
                                      std::string(test_case_data.binary_data);

      REQUIRE(asByteVector(encodeViaH3SVGWriter(reward)) == asByteVector(binary_data));
      REQUIRE(H3SVGReaderAdapter(binary_data).readReward() == reward);
      REQUIRE(encodeAndDecodeJson(reward) == reward);
    }

    SECTION("RewardDetails")
    {
      const RewardDetails<kRewardType>& reward_details = test_case_data.details;
      const std::string_view binary_data = test_case_data.binary_data;

      REQUIRE(asByteVector(encodeViaH3SVGWriter(reward_details)) == asByteVector(binary_data));
      REQUIRE(H3SVGReaderAdapter(binary_data).readRewardDetails<kRewardType>() == reward_details);
      REQUIRE(encodeAndDecodeJson(reward_details) == reward_details);
    }
  }
}
