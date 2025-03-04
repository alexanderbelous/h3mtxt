#pragma once

#include <h3mtxt/Map/MapFwd.h>
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
    // Nonpositive values are ignored: e.g., even if the hero's Attack is -128, and the
    // Quest requires achieving -10 Attack, the game will consider that the hero has
    // completed the quest.
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
    // The Editor doesn't allow an empty array here. If you set it manually:
    // * The Editor will freeze when you try to view the properties of this Quest Guard / Seer's Hut.
    // * The game will not crash, but the quest will be impossible to complete.
    std::vector<ArtifactType> artifacts;
  };

  template<>
  struct QuestDetails<QuestType::Creatures>
  {
    // The Editor doesn't allow an empty array here. If you set it manually:
    // * The Editor will freeze when you try to view the properties of this Quest Guard / Seer's Hut.
    // * The game will not crash, but the quest will be impossible to complete.
    std::vector<CreatureStack> creatures;
  };

  template<>
  struct QuestDetails<QuestType::Resources>
  {
    // * If the amount is negative for some resource, it won't be displayed as a part of the quest
    //   (equivalent to 0), but once you complete the quest your amount will increase.
    // * If all amounts are <= 0, it is considered that you have completed the quest.
    Resources resources {};
  };

  template<>
  struct QuestDetails<QuestType::BeHero>
  {
    // Must be a valid HeroType from [0; 156).
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

    // Get the 0-based index of the alternative corresponding to the given QuestType.
    // \param quest_type - type of the quest.
    // \return 0-based index of the alternative from Quest::Details that has the type
    //         QuestDetails<quest_type>, or std::variant_npos if there is no such alternative.
    static constexpr std::size_t getAlternativeIdx(QuestType quest_type) noexcept;

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
    std::uint32_t deadline = 0xFFFFFFFF;
    std::string proposal{};
    std::string progress{};
    std::string completion{};
  };

  constexpr QuestType Quest::type() const noexcept
  {
    return static_cast<QuestType>(details.index());
  }

  constexpr std::size_t Quest::getAlternativeIdx(QuestType quest_type) noexcept
  {
    const std::size_t idx = static_cast<std::size_t>(quest_type);
    return idx < std::variant_size_v<Details> ? idx : std::variant_npos;
  }
}
