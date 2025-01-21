#pragma once

#include <h3mtxt/Map/Constants/ArtifactType.h>
#include <h3mtxt/Map/Constants/HeroType.h>
#include <h3mtxt/Map/Constants/PlayerColor.h>
#include <h3mtxt/Map/Constants/QuestType.h>
#include <h3mtxt/Map/CreatureStack.h>
#include <h3mtxt/Map/PrimarySkills.h>
#include <h3mtxt/Map/Resources.h>

#include <array>
#include <cstdint>
#include <string>
#include <variant>
#include <vector>

namespace h3m
{
  // Details specific for a QuestType.
  template<QuestType T>
  struct QuestDetails;

  template<>
  struct QuestDetails<QuestType::None>
  {};

  template<>
  struct QuestDetails<QuestType::Level>
  {
    std::uint32_t level {};
  };

  template<>
  struct QuestDetails<QuestType::PrimarySkills>
  {
    PrimarySkills skills;
  };

  template<>
  struct QuestDetails<QuestType::DefeatHero>
  {
    std::uint32_t absod_id {};
  };

  template<>
  struct QuestDetails<QuestType::DefeatMonster>
  {
    std::uint32_t absod_id{};
  };

  template<>
  struct QuestDetails<QuestType::Artifacts>
  {
    std::vector<ArtifactType> artifacts;
  };

  template<>
  struct QuestDetails<QuestType::Creatures>
  {
    std::vector<CreatureStack> creatures;
  };

  template<>
  struct QuestDetails<QuestType::Resources>
  {
    Resources<std::uint32_t> resources {};
  };

  template<>
  struct QuestDetails<QuestType::BeHero>
  {
    HeroType hero {};
  };

  template<>
  struct QuestDetails<QuestType::BePlayer>
  {
    PlayerColor player {};
  };

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

    // The fields below should not be read/written if type() == QuestType::None.
    // I couldn't really think of a way to express this in the type system:
    // * The naive approach is to move it to QuestDetails for every QuestType except None;
    //   however, that violates DRY principle.
    // * I could introduce one more layer of abstraction: define some QuestDetailsAndInfo,
    //   which inherits/stores both QuestDetails and Info for all QuestTypes except None.
    //   However, this is too complicated.
    // So screw it. The fields below will just be ignored during reading/writing if type() is None.

    // 0 - impossible to fulfill; 0xFFFFFFFF - none.
    std::uint32_t deadline{};
    std::string proposal{};
    std::string progress{};
    std::string completion{};
  };

  constexpr QuestType Quest::type() const noexcept
  {
    return static_cast<QuestType>(details.index());
  }
}
