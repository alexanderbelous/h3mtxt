#pragma once

#include <h3mtxt/SavedGame/SavedGameFwd.h>

#include <h3mtxt/Map/Quest.h>

#include <array>
#include <cstddef>
#include <cstdint>
#include <string>
#include <variant>
#include <vector>

namespace h3svg
{
  template<>
  struct QuestDetails<QuestType::None>
  {};

  template<>
  struct QuestDetails<QuestType::Level>
  {
    // Note that the level is stored as a 16-bit integer here - in H3M it's stored as a 32-bit integer.
    std::int16_t level {};
  };

  // Identical to h3m::QuestDetails<QuestType::PrimarySkills>.
  template<>
  struct QuestDetails<QuestType::PrimarySkills> : h3m::QuestDetails<QuestType::PrimarySkills>
  {};

  template<>
  struct QuestDetails<QuestType::DefeatHero>
  {
    // Note that the hero is represented here by their HeroType - H3M uses absod_id instead.
    HeroType hero {};
    // TODO: maybe hero should be treated as a 16-bit enum instead.
    std::array<std::byte, 2> unknown {};
  };

  template<>
  struct QuestDetails<QuestType::DefeatMonster>
  {
    // Absolutely idiotic format - X is 16-bit, Y is 8-bit and Z is Bool.
    std::uint16_t x {};
    std::uint8_t y {};
    // Not necessarily 0 or 1 - apparently, 0x04 is usually used for subterranean.
    Bool z {};
    CreatureType creature_type {};
    // Player who defeated this monster, or 0xFF if no one has yet.
    PlayerColor completed_by {};
  };

  // Identical to h3m::QuestDetails<QuestType::Artifacts>.
  template<>
  struct QuestDetails<QuestType::Artifacts> : h3m::QuestDetails<QuestType::Artifacts>
  {};

  template<>
  struct QuestDetails<QuestType::Creatures>
  {
    struct Creature
    {
      CreatureType type {};
      std::int32_t count {};
    };
    // Size is serialized as an 8-bit integer.
    std::vector<Creature> creatures;
  };

  // Identical to h3m::QuestDetails<QuestType::Resources>.
  template<>
  struct QuestDetails<QuestType::Resources> : h3m::QuestDetails<QuestType::Resources>
  {};

  template<>
  struct QuestDetails<QuestType::BeHero>
  {
    HeroType hero {};
    // TODO: maybe hero should be treated as a 16-bit enum instead. 
    std::byte unknown {};
  };

  // Identical to h3m::QuestDetails<QuestType::BePlayer>.
  template<>
  struct QuestDetails<QuestType::BePlayer> : h3m::QuestDetails<QuestType::BePlayer>
  {};

  // The equivalent of h3m::Quest stored in saved games.
  struct Quest
  {
    using Details = std::variant<
      QuestDetails<QuestType::None>,
      QuestDetails<QuestType::Level>,
      QuestDetails<QuestType::PrimarySkills>,
      QuestDetails<QuestType::DefeatHero>,
      QuestDetails<QuestType::DefeatMonster>,
      QuestDetails<QuestType::Artifacts>,
      QuestDetails<QuestType::Creatures>,
      QuestDetails<QuestType::Resources>,
      QuestDetails<QuestType::BeHero>,
      QuestDetails<QuestType::BePlayer>
    >;

    // \return the type of the quest.
    constexpr QuestType type() const noexcept;

    Details details {};
    // The fiels below are only read/written if type() != QuestType::None.
    std::array<std::byte, 2> unknown {};
    // 0 - impossible to fulfill; 0xFFFFFFFF - none.
    std::uint32_t deadline = 0xFFFFFFFF;
    std::string proposal {};
    std::string progress {};
    std::string completion {};
  };

  constexpr QuestType Quest::type() const noexcept
  {
    return static_cast<QuestType>(details.index());
  }
}
