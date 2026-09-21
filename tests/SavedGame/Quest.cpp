#include "TestingUtils_H3SVG.h"

#include <h3mtxt/SavedGame/Quest.h>

#include <catch2/catch_test_macros.hpp>

#include <string_view>

using namespace std::string_view_literals;
using ::Testing_NS::asByteVector;
using ::Testing_NS::encodeAndDecodeJson;
using ::Testing_NS::encodeViaH3SVGWriter;
using ::Testing_NS::H3SVGReaderAdapter;

namespace h3svg
{
  TEST_CASE("H3SVG.Quest.None", "[H3SVG]")
  {
    const Quest kQuest = {
      .details = QuestDetails<QuestType::None>{}
    };
    static constexpr std::string_view kBinaryData = "\x00"sv;

    REQUIRE(kQuest.type() == QuestType::None);
    REQUIRE(asByteVector(encodeViaH3SVGWriter(kQuest)) == asByteVector(kBinaryData));
    REQUIRE(H3SVGReaderAdapter(kBinaryData).readQuest() == kQuest);
    REQUIRE(encodeAndDecodeJson(kQuest) == kQuest);
  }

  TEST_CASE("H3SVG.Quest.Level", "[H3SVG]")
  {
    const Quest kQuest = {
      .details = QuestDetails<QuestType::Level>{
        .level = 42
      },
      .unknown = {11, 88},
      .deadline = 100,
      .proposal = "Proposal message",
      .progress = "Progress message",
      .completion = "Completion message"
    };
    static constexpr std::string_view kBinaryData =
      "\x01"
      "\x2a\x00"
      "\x0b\x58"
      "\x64\x00\x00\x00"
      "\x10\x00\x00\x00" "Proposal message"
      "\x10\x00\x00\x00" "Progress message"
      "\x12\x00\x00\x00" "Completion message"
      ""sv;

    REQUIRE(kQuest.type() == QuestType::Level);
    REQUIRE(asByteVector(encodeViaH3SVGWriter(kQuest)) == asByteVector(kBinaryData));
    REQUIRE(H3SVGReaderAdapter(kBinaryData).readQuest() == kQuest);
    REQUIRE(encodeAndDecodeJson(kQuest) == kQuest);
  }

  TEST_CASE("H3SVG.Quest.PrimarySkills", "[H3SVG]")
  {
    const Quest kQuest = {
      .details = QuestDetails<QuestType::PrimarySkills>{
        h3m::QuestDetails<QuestType::PrimarySkills>{
          .skills = { 10, 20, 30, 40 }
        }
      },
      .unknown = {11, 88},
      .deadline = 100,
      .proposal = "Proposal message",
      .progress = "Progress message",
      .completion = "Completion message"
    };
    static constexpr std::string_view kBinaryData =
      "\x02"
      "\x0a\x14\x1e\x28"
      "\x0b\x58"
      "\x64\x00\x00\x00"
      "\x10\x00\x00\x00" "Proposal message"
      "\x10\x00\x00\x00" "Progress message"
      "\x12\x00\x00\x00" "Completion message"
      ""sv;

    REQUIRE(kQuest.type() == QuestType::PrimarySkills);
    REQUIRE(asByteVector(encodeViaH3SVGWriter(kQuest)) == asByteVector(kBinaryData));
    REQUIRE(H3SVGReaderAdapter(kBinaryData).readQuest() == kQuest);
    REQUIRE(encodeAndDecodeJson(kQuest) == kQuest);
  }

  TEST_CASE("H3SVG.Quest.DefeatHero", "[H3SVG]")
  {
    const Quest kQuest = {
      .details = QuestDetails<QuestType::DefeatHero>{
        .hero = HeroType::Gunnar,
        .unknown = 42,
        .completed_by = []() consteval {
          PlayersBitmask bitmask;
          bitmask.set(PlayerColor::Green, true);
          bitmask.set(PlayerColor::Teal, true);
          return bitmask;
        }()
      },
      .unknown = {11, 88},
      .deadline = 100,
      .proposal = "Proposal message",
      .progress = "Progress message",
      .completion = "Completion message"
    };
    static constexpr std::string_view kBinaryData =
      "\x03"
      "\x55" "\x2a" "\x48"
      "\x0b\x58"
      "\x64\x00\x00\x00"
      "\x10\x00\x00\x00" "Proposal message"
      "\x10\x00\x00\x00" "Progress message"
      "\x12\x00\x00\x00" "Completion message"
      ""sv;

    REQUIRE(kQuest.type() == QuestType::DefeatHero);
    REQUIRE(asByteVector(encodeViaH3SVGWriter(kQuest)) == asByteVector(kBinaryData));
    REQUIRE(H3SVGReaderAdapter(kBinaryData).readQuest() == kQuest);
    REQUIRE(encodeAndDecodeJson(kQuest) == kQuest);
  }

  TEST_CASE("H3SVG.Quest.DefeatMonster", "[H3SVG]")
  {
    const Quest kQuest = {
      .details = QuestDetails<QuestType::DefeatMonster>{
        .coordinates = {.x = 12, .y = 44, .z = 1},
        .creature_type = CreatureType::AzureDragon,
        .completed_by = PlayerColor::None
      },
      .unknown = {11, 88},
      .deadline = 100,
      .proposal = "Proposal message",
      .progress = "Progress message",
      .completion = "Completion message"
    };
    static constexpr std::string_view kBinaryData =
      "\x04"
      "\x0c\x00\x2c\x04" "\x84\x00" "\xff"
      "\x0b\x58"
      "\x64\x00\x00\x00"
      "\x10\x00\x00\x00" "Proposal message"
      "\x10\x00\x00\x00" "Progress message"
      "\x12\x00\x00\x00" "Completion message"
      ""sv;

    REQUIRE(kQuest.type() == QuestType::DefeatMonster);
    REQUIRE(asByteVector(encodeViaH3SVGWriter(kQuest)) == asByteVector(kBinaryData));
    REQUIRE(H3SVGReaderAdapter(kBinaryData).readQuest() == kQuest);
    REQUIRE(encodeAndDecodeJson(kQuest) == kQuest);
  }

  TEST_CASE("H3SVG.Quest.Artifacts", "[H3SVG]")
  {
    const Quest kQuest = {
      .details = QuestDetails<QuestType::Artifacts>{
        h3m::QuestDetails<QuestType::Artifacts>{
          .artifacts = {ArtifactType::ArmageddonsBlade, ArtifactType::AngelWings, ArtifactType::BootsOfSpeed}
        }
      },
      .unknown = {11, 88},
      .deadline = 100,
      .proposal = "Proposal message",
      .progress = "Progress message",
      .completion = "Completion message"
    };
    static constexpr std::string_view kBinaryData =
      "\x05"
      "\x03" "\x80\x00" "\x48\x00" "\x62\x00"
      "\x0b\x58"
      "\x64\x00\x00\x00"
      "\x10\x00\x00\x00" "Proposal message"
      "\x10\x00\x00\x00" "Progress message"
      "\x12\x00\x00\x00" "Completion message"
      ""sv;

    REQUIRE(kQuest.type() == QuestType::Artifacts);
    REQUIRE(asByteVector(encodeViaH3SVGWriter(kQuest)) == asByteVector(kBinaryData));
    REQUIRE(H3SVGReaderAdapter(kBinaryData).readQuest() == kQuest);
    REQUIRE(encodeAndDecodeJson(kQuest) == kQuest);
  }

  TEST_CASE("H3SVG.Quest.Creatures", "[H3SVG]")
  {
    const Quest kQuest = {
      .details = QuestDetails<QuestType::Creatures>{
        .creatures = {
          TypedQuantity<CreatureType, std::int32_t>{.type = CreatureType::AzureDragon, .quantity = 1},
          TypedQuantity<CreatureType, std::int32_t>{.type = CreatureType::CrystalDragon, .quantity = 2},
          TypedQuantity<CreatureType, std::int32_t>{.type = CreatureType::RustDragon, .quantity = 3},
          TypedQuantity<CreatureType, std::int32_t>{.type = CreatureType::FaerieDragon, .quantity = 4},
        }
      },
      .unknown = {11, 88},
      .deadline = 100,
      .proposal = "Proposal message",
      .progress = "Progress message",
      .completion = "Completion message"
    };
    static constexpr std::string_view kBinaryData =
      "\x06"
      "\x04" "\x84\x00\x01\x00\x00\x00" "\x85\x00\x02\x00\x00\x00" "\x87\x00\x03\x00\x00\x00" "\x86\x00\x04\x00\x00\x00"
      "\x0b\x58"
      "\x64\x00\x00\x00"
      "\x10\x00\x00\x00" "Proposal message"
      "\x10\x00\x00\x00" "Progress message"
      "\x12\x00\x00\x00" "Completion message"
      ""sv;

    REQUIRE(kQuest.type() == QuestType::Creatures);
    REQUIRE(asByteVector(encodeViaH3SVGWriter(kQuest)) == asByteVector(kBinaryData));
    REQUIRE(H3SVGReaderAdapter(kBinaryData).readQuest() == kQuest);
    REQUIRE(encodeAndDecodeJson(kQuest) == kQuest);
  }

  TEST_CASE("H3SVG.Quest.Resources", "[H3SVG]")
  {
    const Quest kQuest = {
      .details = QuestDetails<QuestType::Resources>{
        h3m::QuestDetails<QuestType::Resources>{
          // Wood, Mercury, Ore, Sulfur, Crystal, Gems, Gold
          .resources = Resources{15, 10, 15, 10, 10, 10, 1000}
        }
      },
      .unknown = {11, 88},
      .deadline = 100,
      .proposal = "Proposal message",
      .progress = "Progress message",
      .completion = "Completion message"
    };
    static constexpr std::string_view kBinaryData =
      "\x07"
      "\x0f\x00\x00\x00" "\x0a\x00\x00\x00" "\x0f\x00\x00\x00" "\x0a\x00\x00\x00" "\x0a\x00\x00\x00" "\x0a\x00\x00\x00" "\xe8\x03\x00\x00"
      "\x0b\x58"
      "\x64\x00\x00\x00"
      "\x10\x00\x00\x00" "Proposal message"
      "\x10\x00\x00\x00" "Progress message"
      "\x12\x00\x00\x00" "Completion message"
      ""sv;

    REQUIRE(kQuest.type() == QuestType::Resources);
    REQUIRE(asByteVector(encodeViaH3SVGWriter(kQuest)) == asByteVector(kBinaryData));
    REQUIRE(H3SVGReaderAdapter(kBinaryData).readQuest() == kQuest);
    REQUIRE(encodeAndDecodeJson(kQuest) == kQuest);
  }

  TEST_CASE("H3SVG.Quest.BeHero", "[H3SVG]")
  {
    const Quest kQuest = {
      .details = QuestDetails<QuestType::BeHero>{
        .hero = HeroType::Gunnar,
        .unknown = 42
      },
      .unknown = {11, 88},
      .deadline = 100,
      .proposal = "Proposal message",
      .progress = "",
      .completion = "Completion message"
    };
    static constexpr std::string_view kBinaryData =
      "\x08"
      "\x55" "\x2a"
      "\x0b\x58"
      "\x64\x00\x00\x00"
      "\x10\x00\x00\x00" "Proposal message"
      "\x00\x00\x00\x00"
      "\x12\x00\x00\x00" "Completion message"
      ""sv;

    REQUIRE(kQuest.type() == QuestType::BeHero);
    REQUIRE(asByteVector(encodeViaH3SVGWriter(kQuest)) == asByteVector(kBinaryData));
    REQUIRE(H3SVGReaderAdapter(kBinaryData).readQuest() == kQuest);
    REQUIRE(encodeAndDecodeJson(kQuest) == kQuest);
  }

  TEST_CASE("H3SVG.Quest.BePlayer", "[H3SVG]")
  {
    const Quest kQuest = {
      .details = QuestDetails<QuestType::BePlayer>{
        h3m::QuestDetails<QuestType::BePlayer>{
          .player = PlayerColor::Teal
        }
      },
      .unknown = {11, 88},
      .deadline = static_cast<std::uint32_t>(-1),
      .proposal = "",
      .progress = "",
      .completion = ""
    };
    static constexpr std::string_view kBinaryData =
      "\x09"
      "\x06"
      "\x0b\x58"
      "\xff\xff\xff\xff"
      "\x00\x00\x00\x00"
      "\x00\x00\x00\x00"
      "\x00\x00\x00\x00"
      ""sv;

    REQUIRE(kQuest.type() == QuestType::BePlayer);
    REQUIRE(asByteVector(encodeViaH3SVGWriter(kQuest)) == asByteVector(kBinaryData));
    REQUIRE(H3SVGReaderAdapter(kBinaryData).readQuest() == kQuest);
    REQUIRE(encodeAndDecodeJson(kQuest) == kQuest);
  }
}
