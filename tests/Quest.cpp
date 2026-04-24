#include "Utils.h"

#include <h3mtxt/H3JsonReader/H3MJsonReader/H3MJsonReader.h>
#include <h3mtxt/H3JsonWriter/H3MJsonWriter/H3MJsonWriter.h>
#include <h3mtxt/H3Reader/H3MReader/H3MReader.h>
#include <h3mtxt/H3Writer/H3MWriter/H3MWriter.h>
#include <h3mtxt/Map/Quest.h>

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
    // Encodes h3m::Quest via H3MWriter.
    // \param quest - input Quest.
    // \return std::string storing the encoded data.
    std::string encodeQuest(const Quest& quest)
    {
      std::ostringstream stream;
      H3MWriter{ stream }.writeData(quest);
      return std::move(stream).str();
    }

    // Decodes h3m::Quest via H3MReader.
    // \param encoded_data - input binary data.
    // \return h3m::Quest decoded from @encoded_data.
    Quest decodeQuest(std::string_view encoded_data)
    {
      std::istringstream stream{ std::string{encoded_data} };
      return H3MReader{ stream }.readQuest();
    }
  }

  TEST_CASE("H3M.Quest.None", "[H3M]")
  {
    const Quest kQuest = {
      .details = QuestDetails<QuestType::None>{}
    };
    static constexpr char kBinaryDataCStr[] = "\x00";
    static constexpr std::string_view kBinaryData{ kBinaryDataCStr, std::size(kBinaryDataCStr) - 1 };

    REQUIRE(kQuest.type() == QuestType::None);
    REQUIRE(asByteVector(encodeQuest(kQuest)) == asByteVector(kBinaryData));
    REQUIRE(decodeQuest(kBinaryData) == kQuest);
    REQUIRE(encodeAndDecodeJson(kQuest) == kQuest);
  }

  TEST_CASE("H3M.Quest.Level", "[H3M]")
  {
    const Quest kQuest = {
      .details = QuestDetails<QuestType::Level>{
        .level = 42
      },
      .deadline = 100,
      .proposal = "Proposal message",
      .progress = "Progress message",
      .completion = "Completion message"
    };
    static constexpr char kBinaryDataCStr[] =
      "\x01"
      "\x2a\x00\x00\x00"
      "\x64\x00\x00\x00"
      "\x10\x00\x00\x00" "Proposal message"
      "\x10\x00\x00\x00" "Progress message"
      "\x12\x00\x00\x00" "Completion message"
      ;
    static constexpr std::string_view kBinaryData{ kBinaryDataCStr, std::size(kBinaryDataCStr) - 1 };

    REQUIRE(kQuest.type() == QuestType::Level);
    REQUIRE(asByteVector(encodeQuest(kQuest)) == asByteVector(kBinaryData));
    REQUIRE(decodeQuest(kBinaryData) == kQuest);
    REQUIRE(encodeAndDecodeJson(kQuest) == kQuest);
  }

  TEST_CASE("H3M.Quest.PrimarySkills", "[H3M]")
  {
    const Quest kQuest = {
      .details = QuestDetails<QuestType::PrimarySkills>{
        .skills = { 10, 20, 30, 40 }
      },
      .deadline = 100,
      .proposal = "Proposal message",
      .progress = "Progress message",
      .completion = "Completion message"
    };
    static constexpr char kBinaryDataCStr[] =
      "\x02"
      "\x0a\x14\x1e\x28"
      "\x64\x00\x00\x00"
      "\x10\x00\x00\x00" "Proposal message"
      "\x10\x00\x00\x00" "Progress message"
      "\x12\x00\x00\x00" "Completion message"
      ;
    static constexpr std::string_view kBinaryData{ kBinaryDataCStr, std::size(kBinaryDataCStr) - 1 };

    REQUIRE(kQuest.type() == QuestType::PrimarySkills);
    REQUIRE(asByteVector(encodeQuest(kQuest)) == asByteVector(kBinaryData));
    REQUIRE(decodeQuest(kBinaryData) == kQuest);
    REQUIRE(encodeAndDecodeJson(kQuest) == kQuest);
  }

  TEST_CASE("H3M.Quest.DefeatHero", "[H3M]")
  {
    const Quest kQuest = {
      .details = QuestDetails<QuestType::DefeatHero>{
        .absod_id = 547403
      },
      .deadline = 100,
      .proposal = "Proposal message",
      .progress = "Progress message",
      .completion = "Completion message"
    };
    static constexpr char kBinaryDataCStr[] =
      "\x03"
      "\x4b\x5a\x08\x00"
      "\x64\x00\x00\x00"
      "\x10\x00\x00\x00" "Proposal message"
      "\x10\x00\x00\x00" "Progress message"
      "\x12\x00\x00\x00" "Completion message"
      ;
    static constexpr std::string_view kBinaryData{ kBinaryDataCStr, std::size(kBinaryDataCStr) - 1 };

    REQUIRE(kQuest.type() == QuestType::DefeatHero);
    REQUIRE(asByteVector(encodeQuest(kQuest)) == asByteVector(kBinaryData));
    REQUIRE(decodeQuest(kBinaryData) == kQuest);
    REQUIRE(encodeAndDecodeJson(kQuest) == kQuest);
  }

  TEST_CASE("H3M.Quest.DefeatMonster", "[H3M]")
  {
    const Quest kQuest = {
      .details = QuestDetails<QuestType::DefeatMonster>{
        .absod_id = 547403
      },
      .deadline = 100,
      .proposal = "Proposal message",
      .progress = "Progress message",
      .completion = "Completion message"
    };
    static constexpr char kBinaryDataCStr[] =
      "\x04"
      "\x4b\x5a\x08\x00"
      "\x64\x00\x00\x00"
      "\x10\x00\x00\x00" "Proposal message"
      "\x10\x00\x00\x00" "Progress message"
      "\x12\x00\x00\x00" "Completion message"
      ;
    static constexpr std::string_view kBinaryData{ kBinaryDataCStr, std::size(kBinaryDataCStr) - 1 };

    REQUIRE(kQuest.type() == QuestType::DefeatMonster);
    REQUIRE(asByteVector(encodeQuest(kQuest)) == asByteVector(kBinaryData));
    REQUIRE(decodeQuest(kBinaryData) == kQuest);
    REQUIRE(encodeAndDecodeJson(kQuest) == kQuest);
  }

  TEST_CASE("H3M.Quest.Artifacts", "[H3M]")
  {
    const Quest kQuest = {
      .details = QuestDetails<QuestType::Artifacts>{
        .artifacts = {ArtifactType::ArmageddonsBlade, ArtifactType::AngelWings, ArtifactType::BootsOfSpeed}
      },
      .deadline = 100,
      .proposal = "Proposal message",
      .progress = "Progress message",
      .completion = "Completion message"
    };
    static constexpr char kBinaryDataCStr[] =
      "\x05"
      "\x03" "\x80\x00" "\x48\x00" "\x62\x00"
      "\x64\x00\x00\x00"
      "\x10\x00\x00\x00" "Proposal message"
      "\x10\x00\x00\x00" "Progress message"
      "\x12\x00\x00\x00" "Completion message"
      ;
    static constexpr std::string_view kBinaryData{ kBinaryDataCStr, std::size(kBinaryDataCStr) - 1 };

    REQUIRE(kQuest.type() == QuestType::Artifacts);
    REQUIRE(asByteVector(encodeQuest(kQuest)) == asByteVector(kBinaryData));
    REQUIRE(decodeQuest(kBinaryData) == kQuest);
    REQUIRE(encodeAndDecodeJson(kQuest) == kQuest);
  }

  TEST_CASE("H3M.Quest.Creatures", "[H3M]")
  {
    const Quest kQuest = {
      .details = QuestDetails<QuestType::Creatures>{
        .creatures = {
          QuestDetails<QuestType::Creatures>::Creature{.type = CreatureType::AzureDragon, .count = 1},
          QuestDetails<QuestType::Creatures>::Creature{.type = CreatureType::CrystalDragon, .count = 2},
          QuestDetails<QuestType::Creatures>::Creature{.type = CreatureType::RustDragon, .count = 3},
          QuestDetails<QuestType::Creatures>::Creature{.type = CreatureType::FaerieDragon, .count = 4},
        }
      },
      .deadline = 100,
      .proposal = "Proposal message",
      .progress = "Progress message",
      .completion = "Completion message"
    };
    static constexpr char kBinaryDataCStr[] =
      "\x06"
      "\x04" "\x84\x00\x01\x00" "\x85\x00\x02\x00" "\x87\x00\x03\x00" "\x86\x00\x04\x00"
      "\x64\x00\x00\x00"
      "\x10\x00\x00\x00" "Proposal message"
      "\x10\x00\x00\x00" "Progress message"
      "\x12\x00\x00\x00" "Completion message"
      ;
    static constexpr std::string_view kBinaryData{ kBinaryDataCStr, std::size(kBinaryDataCStr) - 1 };

    REQUIRE(kQuest.type() == QuestType::Creatures);
    REQUIRE(asByteVector(encodeQuest(kQuest)) == asByteVector(kBinaryData));
    REQUIRE(decodeQuest(kBinaryData) == kQuest);
    REQUIRE(encodeAndDecodeJson(kQuest) == kQuest);
  }

  TEST_CASE("H3M.Quest.Resources", "[H3M]")
  {
    const Quest kQuest = {
      .details = QuestDetails<QuestType::Resources>{
        // Wood, Mercury, Ore, Sulfur, Crystal, Gems, Gold
        .resources = Resources{15, 10, 15, 10, 10, 10, 1000}
      },
      .deadline = 100,
      .proposal = "Proposal message",
      .progress = "Progress message",
      .completion = "Completion message"
    };
    static constexpr char kBinaryDataCStr[] =
      "\x07"
      "\x0f\x00\x00\x00" "\x0a\x00\x00\x00" "\x0f\x00\x00\x00" "\x0a\x00\x00\x00" "\x0a\x00\x00\x00" "\x0a\x00\x00\x00" "\xe8\x03\x00\x00"
      "\x64\x00\x00\x00"
      "\x10\x00\x00\x00" "Proposal message"
      "\x10\x00\x00\x00" "Progress message"
      "\x12\x00\x00\x00" "Completion message"
      ;
    static constexpr std::string_view kBinaryData{ kBinaryDataCStr, std::size(kBinaryDataCStr) - 1 };

    REQUIRE(kQuest.type() == QuestType::Resources);
    REQUIRE(asByteVector(encodeQuest(kQuest)) == asByteVector(kBinaryData));
    REQUIRE(decodeQuest(kBinaryData) == kQuest);
    REQUIRE(encodeAndDecodeJson(kQuest) == kQuest);
  }

  TEST_CASE("H3M.Quest.BeHero", "[H3M]")
  {
    const Quest kQuest = {
      .details = QuestDetails<QuestType::BeHero>{
        .hero = HeroType::Gunnar
      },
      .deadline = 100,
      .proposal = "Proposal message",
      .progress = "",
      .completion = "Completion message"
    };
    static constexpr char kBinaryDataCStr[] =
      "\x08"
      "\x55"
      "\x64\x00\x00\x00"
      "\x10\x00\x00\x00" "Proposal message"
      "\x00\x00\x00\x00"
      "\x12\x00\x00\x00" "Completion message"
      ;
    static constexpr std::string_view kBinaryData{ kBinaryDataCStr, std::size(kBinaryDataCStr) - 1 };

    REQUIRE(kQuest.type() == QuestType::BeHero);
    REQUIRE(asByteVector(encodeQuest(kQuest)) == asByteVector(kBinaryData));
    REQUIRE(decodeQuest(kBinaryData) == kQuest);
    REQUIRE(encodeAndDecodeJson(kQuest) == kQuest);
  }

  TEST_CASE("H3M.Quest.BePlayer", "[H3M]")
  {
    const Quest kQuest = {
      .details = QuestDetails<QuestType::BePlayer>{
        .player = PlayerColor::Teal
      },
      .deadline = static_cast<std::uint32_t>(-1),
      .proposal = "",
      .progress = "",
      .completion = ""
    };
    static constexpr char kBinaryDataCStr[] =
      "\x09"
      "\x06"
      "\xff\xff\xff\xff"
      "\x00\x00\x00\x00"
      "\x00\x00\x00\x00"
      "\x00\x00\x00\x00"
      ;
    static constexpr std::string_view kBinaryData{ kBinaryDataCStr, std::size(kBinaryDataCStr) - 1 };

    REQUIRE(kQuest.type() == QuestType::BePlayer);
    REQUIRE(asByteVector(encodeQuest(kQuest)) == asByteVector(kBinaryData));
    REQUIRE(decodeQuest(kBinaryData) == kQuest);
    REQUIRE(encodeAndDecodeJson(kQuest) == kQuest);
  }
}
