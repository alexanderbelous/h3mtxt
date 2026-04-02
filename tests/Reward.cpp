#include <h3mtxt/H3Reader/H3MReader/H3MReader.h>
#include <h3mtxt/H3Writer/H3MWriter/H3MWriter.h>
#include <h3mtxt/Map/Reward.h>

#include <catch2/catch_test_macros.hpp>

#include <iterator>
#include <sstream>
#include <string>
#include <string_view>
#include <utility>

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
    static constexpr char kBinaryDataCStr[] = "\x00";
    static constexpr std::string_view kBinaryData{ kBinaryDataCStr, std::size(kBinaryDataCStr) - 1 };

    static_assert(kReward.type() == RewardType::None);
    REQUIRE(encodeReward(kReward) == kBinaryData);
    REQUIRE(decodeReward(kBinaryData) == kReward);
  }

  TEST_CASE("H3M.Reward.Experience", "[H3M]")
  {
    constexpr Reward kReward = {
      .details = RewardDetails<RewardType::Experience>{
        .experience = 5000
      }
    };
    static constexpr char kBinaryDataCStr[] = "\x01" "\x88\x13\x00\x00";
    static constexpr std::string_view kBinaryData{ kBinaryDataCStr, std::size(kBinaryDataCStr) - 1 };

    static_assert(kReward.type() == RewardType::Experience);
    REQUIRE(encodeReward(kReward) == kBinaryData);
    REQUIRE(decodeReward(kBinaryData) == kReward);
  }

  TEST_CASE("H3M.Reward.SpellPoints", "[H3M]")
  {
    constexpr Reward kReward = {
      .details = RewardDetails<RewardType::SpellPoints>{
        .spell_points = 500
      }
    };
    static constexpr char kBinaryDataCStr[] = "\x02" "\xf4\x01\x00\x00";
    static constexpr std::string_view kBinaryData{ kBinaryDataCStr, std::size(kBinaryDataCStr) - 1 };

    static_assert(kReward.type() == RewardType::SpellPoints);
    REQUIRE(encodeReward(kReward) == kBinaryData);
    REQUIRE(decodeReward(kBinaryData) == kReward);
  }

  TEST_CASE("H3M.Reward.Morale", "[H3M]")
  {
    constexpr Reward kReward = {
      .details = RewardDetails<RewardType::Morale>{
        .morale = 2
      }
    };
    static constexpr char kBinaryDataCStr[] = "\x03" "\x02";
    static constexpr std::string_view kBinaryData{ kBinaryDataCStr, std::size(kBinaryDataCStr) - 1 };

    static_assert(kReward.type() == RewardType::Morale);
    REQUIRE(encodeReward(kReward) == kBinaryData);
    REQUIRE(decodeReward(kBinaryData) == kReward);
  }

  TEST_CASE("H3M.Reward.Luck", "[H3M]")
  {
    constexpr Reward kReward = {
      .details = RewardDetails<RewardType::Luck>{
        .luck = 2
      }
    };
    static constexpr char kBinaryDataCStr[] = "\x04" "\x02";
    static constexpr std::string_view kBinaryData{ kBinaryDataCStr, std::size(kBinaryDataCStr) - 1 };

    static_assert(kReward.type() == RewardType::Luck);
    REQUIRE(encodeReward(kReward) == kBinaryData);
    REQUIRE(decodeReward(kBinaryData) == kReward);
  }

  TEST_CASE("H3M.Reward.Resource", "[H3M]")
  {
    constexpr Reward kReward = {
      .details = RewardDetails<RewardType::Resource>{
        .type = ResourceType::Gold,
        .amount = 10000
      }
    };
    static constexpr char kBinaryDataCStr[] = "\x05" "\x06" "\x10\x27\x00\x00";
    static constexpr std::string_view kBinaryData{ kBinaryDataCStr, std::size(kBinaryDataCStr) - 1 };

    static_assert(kReward.type() == RewardType::Resource);
    REQUIRE(encodeReward(kReward) == kBinaryData);
    REQUIRE(decodeReward(kBinaryData) == kReward);
  }

  TEST_CASE("H3M.Reward.PrimarySkill", "[H3M]")
  {
    constexpr Reward kReward = {
      .details = RewardDetails<RewardType::PrimarySkill>{
        .type = PrimarySkillType::Knowledge,
        .value = 5
      }
    };
    static constexpr char kBinaryDataCStr[] = "\x06" "\x03" "\x05";
    static constexpr std::string_view kBinaryData{ kBinaryDataCStr, std::size(kBinaryDataCStr) - 1 };

    static_assert(kReward.type() == RewardType::PrimarySkill);
    REQUIRE(encodeReward(kReward) == kBinaryData);
    REQUIRE(decodeReward(kBinaryData) == kReward);
  }

  TEST_CASE("H3M.Reward.SecondarySkill", "[H3M]")
  {
    constexpr Reward kReward = {
      .details = RewardDetails<RewardType::SecondarySkill>{
        SecondarySkill{
          .type = SecondarySkillType::EarthMagic,
          .level = 3
        }
      }
    };
    static constexpr char kBinaryDataCStr[] = "\x07" "\x11" "\x03";
    static constexpr std::string_view kBinaryData{ kBinaryDataCStr, std::size(kBinaryDataCStr) - 1 };

    static_assert(kReward.type() == RewardType::SecondarySkill);
    REQUIRE(encodeReward(kReward) == kBinaryData);
    REQUIRE(decodeReward(kBinaryData) == kReward);
  }

  TEST_CASE("H3M.Reward.Artifact", "[H3M]")
  {
    constexpr Reward kReward = {
      .details = RewardDetails<RewardType::Artifact>{
        .artifact = ArtifactType::ElixirOfLife
      }
    };
    static constexpr char kBinaryDataCStr[] = "\x08" "\x83\x00";
    static constexpr std::string_view kBinaryData{ kBinaryDataCStr, std::size(kBinaryDataCStr) - 1 };

    static_assert(kReward.type() == RewardType::Artifact);
    REQUIRE(encodeReward(kReward) == kBinaryData);
    REQUIRE(decodeReward(kBinaryData) == kReward);
  }

  TEST_CASE("H3M.Reward.Spell", "[H3M]")
  {
    constexpr Reward kReward = {
      .details = RewardDetails<RewardType::Spell>{
        .spell = SpellType::ForceField
      }
    };
    static constexpr char kBinaryDataCStr[] = "\x09" "\x0c";
    static constexpr std::string_view kBinaryData{ kBinaryDataCStr, std::size(kBinaryDataCStr) - 1 };

    static_assert(kReward.type() == RewardType::Spell);
    REQUIRE(encodeReward(kReward) == kBinaryData);
    REQUIRE(decodeReward(kBinaryData) == kReward);
  }

  TEST_CASE("H3M.Reward.Creature", "[H3M]")
  {
    constexpr Reward kReward = {
      .details = RewardDetails<RewardType::Creature>{
        CreatureStack{
          .type = CreatureType::Sharpshooter,
          .count = 100
        }
      }
    };
    static constexpr char kBinaryDataCStr[] = "\x0a" "\x89\x00" "\x64\x00";
    static constexpr std::string_view kBinaryData{ kBinaryDataCStr, std::size(kBinaryDataCStr) - 1 };

    static_assert(kReward.type() == RewardType::Creature);
    REQUIRE(encodeReward(kReward) == kBinaryData);
    REQUIRE(decodeReward(kBinaryData) == kReward);
  }
}
