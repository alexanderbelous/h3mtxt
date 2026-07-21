#include "Utils.h"

#include <h3mtxt/H3JsonReader/H3MJsonReader/H3MJsonReader.h>
#include <h3mtxt/H3JsonWriter/H3MJsonWriter/H3MJsonWriter.h>
#include <h3mtxt/H3Reader/H3MReader/H3MReader.h>
#include <h3mtxt/H3Writer/H3MWriter/H3MWriter.h>
#include <h3mtxt/Map/Reward.h>

#include <catch2/catch_test_macros.hpp>

#include <sstream>
#include <string>
#include <string_view>
#include <utility>

using namespace std::string_view_literals;
using ::Testing_NS::asByteVector;
using ::Testing_NS::encodeAndDecodeJson;

namespace h3m
{
  namespace
  {
    // Encodes h3m::Reward via H3MWriter.
    // \param reward - input Reward.
    // \return std::string storing the encoded data.
    std::string encodeReward(const Reward& reward)
    {
      std::ostringstream stream;
      H3MWriter{ stream }.writeData(reward);
      return std::move(stream).str();
    }

    // Decodes h3m::Reward via H3MReader.
    // \param encoded_data - input binary data.
    // \return h3m::Reward decoded from @encoded_data.
    Reward decodeReward(std::string_view encoded_data)
    {
      std::istringstream stream{ std::string{encoded_data} };
      return H3MReader{ stream }.readReward();
    }
  }

  TEST_CASE("H3M.Reward.None", "[H3M]")
  {
    constexpr Reward kReward = {
      .details = RewardDetails<RewardType::None>{}
    };
    static constexpr std::string_view kBinaryData = "\x00"sv;

    static_assert(kReward.type() == RewardType::None);
    REQUIRE(asByteVector(encodeReward(kReward)) == asByteVector(kBinaryData));
    REQUIRE(decodeReward(kBinaryData) == kReward);
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
    REQUIRE(asByteVector(encodeReward(kReward)) == asByteVector(kBinaryData));
    REQUIRE(decodeReward(kBinaryData) == kReward);
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
    REQUIRE(asByteVector(encodeReward(kReward)) == asByteVector(kBinaryData));
    REQUIRE(decodeReward(kBinaryData) == kReward);
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
    REQUIRE(asByteVector(encodeReward(kReward)) == asByteVector(kBinaryData));
    REQUIRE(decodeReward(kBinaryData) == kReward);
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
    REQUIRE(asByteVector(encodeReward(kReward)) == asByteVector(kBinaryData));
    REQUIRE(decodeReward(kBinaryData) == kReward);
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
    REQUIRE(asByteVector(encodeReward(kReward)) == asByteVector(kBinaryData));
    REQUIRE(decodeReward(kBinaryData) == kReward);
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
    REQUIRE(asByteVector(encodeReward(kReward)) == asByteVector(kBinaryData));
    REQUIRE(decodeReward(kBinaryData) == kReward);
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
    REQUIRE(asByteVector(encodeReward(kReward)) == asByteVector(kBinaryData));
    REQUIRE(decodeReward(kBinaryData) == kReward);
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
    REQUIRE(asByteVector(encodeReward(kReward)) == asByteVector(kBinaryData));
    REQUIRE(decodeReward(kBinaryData) == kReward);
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
    REQUIRE(asByteVector(encodeReward(kReward)) == asByteVector(kBinaryData));
    REQUIRE(decodeReward(kBinaryData) == kReward);
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
    REQUIRE(asByteVector(encodeReward(kReward)) == asByteVector(kBinaryData));
    REQUIRE(decodeReward(kBinaryData) == kReward);
    REQUIRE(encodeAndDecodeJson(kReward) == kReward);
  }
}
