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
  struct QuestDetailsSvg<QuestType::None>
  {};

  template<>
  struct QuestDetailsSvg<QuestType::Level>
  {
    // Note that the level is stored as a 16-bit integer here - in H3M it's stored as a 32-bit integer.
    std::int16_t level {};
  };

  // Identical to QuestDetails<QuestType::PrimarySkills>.
  template<>
  struct QuestDetailsSvg<QuestType::PrimarySkills> : h3m::QuestDetails<QuestType::PrimarySkills>
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
    // Absolutely idiotic format - X is 16-bit, Y is 8-bit and Z is Bool.
    std::uint16_t x {};
    std::uint8_t y {};
    // Not necessarily 0 or 1 - apparently, 0x04 is usually used for subterranean.
    Bool z {};
    CreatureType creature_type {};
    std::byte unknown {};
  };

  // Identical to QuestDetails<QuestType::Artifacts>.
  template<>
  struct QuestDetailsSvg<QuestType::Artifacts> : h3m::QuestDetails<QuestType::Artifacts>
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
  struct QuestDetailsSvg<QuestType::Resources> : h3m::QuestDetails<QuestType::Resources>
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
  struct QuestDetailsSvg<QuestType::BePlayer> : h3m::QuestDetails<QuestType::BePlayer>
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

  constexpr QuestType QuestSvg::type() const noexcept
  {
    return static_cast<QuestType>(details.index());
  }
}
