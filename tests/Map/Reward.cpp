#include "TestUtils_H3M.h"

#include <h3mtxt/Map/Reward.h>

#include <catch2/catch_test_macros.hpp>

#include <string_view>

using namespace std::string_view_literals;
using ::Testing_NS::asByteVector;
using ::Testing_NS::encodeAndDecodeJson;
using ::Testing_NS::encodeViaH3MWriter;
using ::Testing_NS::H3MReaderAdapter;

namespace h3m
{
  TEST_CASE("H3M.Reward.None", "[H3M]")
  {
    constexpr Reward kReward = {
      .details = RewardDetails<RewardType::None>{}
    };
    static constexpr std::string_view kBinaryData = "\x00"sv;

    static_assert(kReward.type() == RewardType::None);
    REQUIRE(asByteVector(encodeViaH3MWriter(kReward)) == asByteVector(kBinaryData));
    REQUIRE(H3MReaderAdapter(kBinaryData).readReward() == kReward);
    REQUIRE(encodeAndDecodeJson(kReward) == kReward);
  }

  TEST_CASE("H3M.Reward.Experience", "[H3M]")
  {
    constexpr Reward kReward = {
      .details = RewardDetails<RewardType::Experience>{
        .experience = 5000
      }
    };
    static constexpr std::string_view kBinaryData = "\x01" "\x88\x13\x00\x00" ""sv;

    static_assert(kReward.type() == RewardType::Experience);
    REQUIRE(asByteVector(encodeViaH3MWriter(kReward)) == asByteVector(kBinaryData));
    REQUIRE(H3MReaderAdapter(kBinaryData).readReward() == kReward);
    REQUIRE(encodeAndDecodeJson(kReward) == kReward);
  }

  TEST_CASE("H3M.Reward.SpellPoints", "[H3M]")
  {
    constexpr Reward kReward = {
      .details = RewardDetails<RewardType::SpellPoints>{
        .spell_points = 500
      }
    };
    static constexpr std::string_view kBinaryData = "\x02" "\xf4\x01\x00\x00" ""sv;

    static_assert(kReward.type() == RewardType::SpellPoints);
    REQUIRE(asByteVector(encodeViaH3MWriter(kReward)) == asByteVector(kBinaryData));
    REQUIRE(H3MReaderAdapter(kBinaryData).readReward() == kReward);
    REQUIRE(encodeAndDecodeJson(kReward) == kReward);
  }

  TEST_CASE("H3M.Reward.Morale", "[H3M]")
  {
    constexpr Reward kReward = {
      .details = RewardDetails<RewardType::Morale>{
        .morale = 2
      }
    };
    static constexpr std::string_view kBinaryData = "\x03" "\x02" ""sv;

    static_assert(kReward.type() == RewardType::Morale);
    REQUIRE(asByteVector(encodeViaH3MWriter(kReward)) == asByteVector(kBinaryData));
    REQUIRE(H3MReaderAdapter(kBinaryData).readReward() == kReward);
    REQUIRE(encodeAndDecodeJson(kReward) == kReward);
  }

  TEST_CASE("H3M.Reward.Luck", "[H3M]")
  {
    constexpr Reward kReward = {
      .details = RewardDetails<RewardType::Luck>{
        .luck = 2
      }
    };
    static constexpr std::string_view kBinaryData = "\x04" "\x02" ""sv;

    static_assert(kReward.type() == RewardType::Luck);
    REQUIRE(asByteVector(encodeViaH3MWriter(kReward)) == asByteVector(kBinaryData));
    REQUIRE(H3MReaderAdapter(kBinaryData).readReward() == kReward);
    REQUIRE(encodeAndDecodeJson(kReward) == kReward);
  }

  TEST_CASE("H3M.Reward.Resource", "[H3M]")
  {
    constexpr Reward kReward = {
      .details = RewardDetails<RewardType::Resource>{
        .resource = {
          .type = ResourceType::Gold,
          .quantity = 10000
        }
      }
    };
    static constexpr std::string_view kBinaryData = "\x05" "\x06" "\x10\x27\x00\x00" ""sv;

    static_assert(kReward.type() == RewardType::Resource);
    REQUIRE(asByteVector(encodeViaH3MWriter(kReward)) == asByteVector(kBinaryData));
    REQUIRE(H3MReaderAdapter(kBinaryData).readReward() == kReward);
    REQUIRE(encodeAndDecodeJson(kReward) == kReward);
  }

  TEST_CASE("H3M.Reward.PrimarySkill", "[H3M]")
  {
    constexpr Reward kReward = {
      .details = RewardDetails<RewardType::PrimarySkill>{
        .type = PrimarySkillType::Knowledge,
        .value = 5
      }
    };
    static constexpr std::string_view kBinaryData = "\x06" "\x03" "\x05" ""sv;

    static_assert(kReward.type() == RewardType::PrimarySkill);
    REQUIRE(asByteVector(encodeViaH3MWriter(kReward)) == asByteVector(kBinaryData));
    REQUIRE(H3MReaderAdapter(kBinaryData).readReward() == kReward);
    REQUIRE(encodeAndDecodeJson(kReward) == kReward);
  }

  TEST_CASE("H3M.Reward.SecondarySkill", "[H3M]")
  {
    constexpr Reward kReward = {
      .details = RewardDetails<RewardType::SecondarySkill>{
        .secondary_skill = {
          .type = SecondarySkillType::EarthMagic,
          .level = 3
        }
      }
    };
    static constexpr std::string_view kBinaryData = "\x07" "\x11" "\x03" ""sv;

    static_assert(kReward.type() == RewardType::SecondarySkill);
    REQUIRE(asByteVector(encodeViaH3MWriter(kReward)) == asByteVector(kBinaryData));
    REQUIRE(H3MReaderAdapter(kBinaryData).readReward() == kReward);
    REQUIRE(encodeAndDecodeJson(kReward) == kReward);
  }

  TEST_CASE("H3M.Reward.Artifact", "[H3M]")
  {
    constexpr Reward kReward = {
      .details = RewardDetails<RewardType::Artifact>{
        .artifact = ArtifactType::ElixirOfLife
      }
    };
    static constexpr std::string_view kBinaryData = "\x08" "\x83\x00" ""sv;

    static_assert(kReward.type() == RewardType::Artifact);
    REQUIRE(asByteVector(encodeViaH3MWriter(kReward)) == asByteVector(kBinaryData));
    REQUIRE(H3MReaderAdapter(kBinaryData).readReward() == kReward);
    REQUIRE(encodeAndDecodeJson(kReward) == kReward);
  }

  TEST_CASE("H3M.Reward.Spell", "[H3M]")
  {
    constexpr Reward kReward = {
      .details = RewardDetails<RewardType::Spell>{
        .spell = SpellType::ForceField
      }
    };
    static constexpr std::string_view kBinaryData = "\x09" "\x0c" ""sv;

    static_assert(kReward.type() == RewardType::Spell);
    REQUIRE(asByteVector(encodeViaH3MWriter(kReward)) == asByteVector(kBinaryData));
    REQUIRE(H3MReaderAdapter(kBinaryData).readReward() == kReward);
    REQUIRE(encodeAndDecodeJson(kReward) == kReward);
  }

  TEST_CASE("H3M.Reward.Creatures", "[H3M]")
  {
    constexpr Reward kReward = {
      .details = RewardDetails<RewardType::Creatures>{
        .creatures = {
          .type = CreatureType::Sharpshooter,
          .quantity = 100
        }
      }
    };
    static constexpr std::string_view kBinaryData = "\x0a" "\x89\x00" "\x64\x00" ""sv;

    static_assert(kReward.type() == RewardType::Creatures);
    REQUIRE(asByteVector(encodeViaH3MWriter(kReward)) == asByteVector(kBinaryData));
    REQUIRE(H3MReaderAdapter(kBinaryData).readReward() == kReward);
    REQUIRE(encodeAndDecodeJson(kReward) == kReward);
  }
}
