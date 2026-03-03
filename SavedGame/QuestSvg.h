#pragma once

#include <h3mtxt/SavedGame/SavedGameFwd.h>

#include <h3mtxt/Map/Quest.h>

#include <array>
#include <cstddef>
#include <cstdint>
#include <string>
#include <variant>
#include <vector>

namespace h3m
{
  template<>
  struct QuestDetailsSvg<QuestType::None>
  {
    // TODO: check that there are no padding bytes here.
  };

  template<>
  struct QuestDetailsSvg<QuestType::Level>
  {
    // Note that the level is stored as a 16-bit integer here - in H3M it's stored as a 32-bit integer.
    std::int16_t level {};
  };

  // Identical to QuestDetails<QuestType::PrimarySkills>.
  template<>
  struct QuestDetailsSvg<QuestType::PrimarySkills> : QuestDetails<QuestType::PrimarySkills>
  {};

  template<>
  struct QuestDetailsSvg<QuestType::DefeatHero>
  {
    // Note that the hero is represented here by their HeroType - H3M uses absod_id instead.
    HeroType hero {};
    // TODO: maybe hero should be treated as a 16-bit enum instead.
    std::array<std::byte, 2> unknown {};
  };

  template<>
  struct QuestDetailsSvg<QuestType::DefeatMonster>
  {
    // Absolutely idiotic format.
    std::uint8_t x {};
    std::byte unknown1 {};
    std::uint8_t y {};
    // Not necessarily 0 or 1 - e.g., I've seen 0x04 being used for subterranean.
    Bool z {};
    // TODO: double-check the width.
    CreatureType creature_type {};
    std::array<std::byte, 2> unknown2 {};
  };

  // Identical to QuestDetails<QuestType::Artifacts>.
  template<>
  struct QuestDetailsSvg<QuestType::Artifacts> : QuestDetails<QuestType::Artifacts>
  {};

  template<>
  struct QuestDetailsSvg<QuestType::Creatures>
  {
    struct Creature
    {
      CreatureType type {};
      std::int32_t count {};
    };
    // Size is serialized as an 8-bit integer.
    std::vector<Creature> creatures;
  };

  // Identical to QuestDetails<QuestType::Resources>.
  template<>
  struct QuestDetailsSvg<QuestType::Resources> : QuestDetails<QuestType::Resources>
  {};

  template<>
  struct QuestDetailsSvg<QuestType::BeHero>
  {
    HeroType hero {};
    // TODO: maybe hero should be treated as a 16-bit enum instead. 
    std::byte unknown {};
  };

  // Identical to QuestDetails<QuestType::BePlayer>.
  template<>
  struct QuestDetailsSvg<QuestType::BePlayer> : QuestDetails<QuestType::BePlayer>
  {};

  // The equivalent of h3m::Quest stored in saved games.
  struct QuestSvg
  {
    using Details = std::variant<
      QuestDetailsSvg<QuestType::None>,
      QuestDetailsSvg<QuestType::Level>,
      QuestDetailsSvg<QuestType::PrimarySkills>,
      QuestDetailsSvg<QuestType::DefeatHero>,
      QuestDetailsSvg<QuestType::DefeatMonster>,
      QuestDetailsSvg<QuestType::Artifacts>,
      QuestDetailsSvg<QuestType::Creatures>,
      QuestDetailsSvg<QuestType::Resources>,
      QuestDetailsSvg<QuestType::BeHero>,
      QuestDetailsSvg<QuestType::BePlayer>
    >;

    Details details {};
    std::array<std::byte, 2> unknown {};
    // 0 - impossible to fulfill; 0xFFFFFFFF - none.
    std::uint32_t deadline = 0xFFFFFFFF;
    std::string proposal {};
    std::string progress {};
    std::string completion {};
  };
}
