#pragma once

#include <h3mtxt/SavedGame/SavedGameFwd.h>

#include <h3mtxt/Map/Utils/EnumBitmask.h>
#include <h3mtxt/Map/Utils/TypedQuantity.h>
#include <h3mtxt/Map/Quest.h>
#include <h3mtxt/SavedGame/CoordinatesPacked.h>

#include <array>
#include <cstdint>
#include <string>
#include <variant>
#include <vector>

namespace h3svg
{
  // The default implementation reuses h3m::QuestDetails.
  template<QuestType T>
  struct QuestDetails : h3m::QuestDetails<T>
  {
    constexpr bool operator==(const QuestDetails&) const noexcept = default;
  };

  template<>
  struct QuestDetails<QuestType::Level>
  {
    constexpr bool operator==(const QuestDetails&) const noexcept = default;

    // Note that the level is stored as a 16-bit integer here - in H3M it's stored as a 32-bit integer.
    std::int16_t level {};
  };

  template<>
  struct QuestDetails<QuestType::DefeatHero>
  {
    constexpr bool operator==(const QuestDetails&) const noexcept = default;

    // Note that the hero is represented here by their HeroType - H3M uses absod_id instead.
    HeroType hero {};
    // TODO: maybe hero should be treated as a 16-bit enum instead.
    std::uint8_t unknown {};
    PlayersBitmask completed_by;
  };

  template<>
  struct QuestDetails<QuestType::DefeatMonster>
  {
    constexpr bool operator==(const QuestDetails&) const noexcept = default;

    // Coordinates of the monster on the Adventure Map.
    CoordinatesPacked coordinates;
    CreatureType creature_type {};
    // Player who defeated this monster, or 0xFF if no one has yet.
    PlayerColor completed_by = PlayerColor::None;
  };

  template<>
  struct QuestDetails<QuestType::Creatures>
  {
    using Creature = TypedQuantity<CreatureType, std::int32_t>;

    constexpr bool operator==(const QuestDetails&) const noexcept = default;

    // Size is serialized as an 8-bit integer.
    std::vector<Creature> creatures;
  };

  template<>
  struct QuestDetails<QuestType::BeHero>
  {
    constexpr bool operator==(const QuestDetails&) const noexcept = default;

    HeroType hero {};
    // TODO: maybe hero should be treated as a 16-bit enum instead. 
    std::uint8_t unknown {};
  };

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

    constexpr bool operator==(const Quest&) const noexcept = default;

    // \return the type of the quest.
    constexpr QuestType type() const noexcept;

    Details details;
    // The fiels below are only read/written if type() != QuestType::None.
    std::array<std::uint8_t, 2> unknown {};
    // 0 - impossible to fulfill; 0xFFFFFFFF - none.
    std::uint32_t deadline = 0xFFFFFFFF;
    std::string proposal;
    std::string progress;
    std::string completion;
  };

  constexpr QuestType Quest::type() const noexcept
  {
    return static_cast<QuestType>(details.index());
  }
}
