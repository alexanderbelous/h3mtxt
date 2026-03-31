#pragma once

#include <h3mtxt/SavedGame/SavedGameFwd.h>

#include <h3mtxt/Map/Constants/LossConditionType.h>
#include <h3mtxt/Map/LossCondition.h>

#include <cstdint>
#include <variant>

namespace h3svg
{
  // Specialization for LoseTown.
  // Identical to H3M.
  template<>
  struct LossConditionDetails<LossConditionType::LoseTown> : h3m::LossConditionDetails<LossConditionType::LoseTown>
  {};

  // Specialization for LoseHero.
  template<>
  struct LossConditionDetails<LossConditionType::LoseHero>
  {
    HeroType16 hero {};
  };

  // Specialization for TimeExpires.
  // Identical to H3M.
  template<>
  struct LossConditionDetails<LossConditionType::TimeExpires> : h3m::LossConditionDetails<LossConditionType::TimeExpires>
  {};

  // Specialization for Normal.
  template<>
  struct LossConditionDetails<LossConditionType::Normal>
  {};

  // Loss condition for the map.
  //
  // This is an aggregate type; the default-constructed LossCondition represents LossConditionType::Normal.
  struct LossCondition
  {
    using Details = std::variant<
      LossConditionDetails<LossConditionType::LoseTown>,
      LossConditionDetails<LossConditionType::LoseHero>,
      LossConditionDetails<LossConditionType::TimeExpires>,
      LossConditionDetails<LossConditionType::Normal>
    >;

    // \return the type of the loss condition.
    constexpr LossConditionType type() const noexcept;

    // Get the 0-based index of the alternative corresponding to the given LossConditionType.
    // \param loss_condition_type - input LossConditionType.
    // \return 0-based index of the alternative from LossCondition::Details that has the type
    //         LossConditionDetails<loss_condition_type>, or std::variant_npos if there is no such alternative.
    static constexpr std::size_t getAlternativeIdx(LossConditionType loss_condition_type) noexcept;

    // Details of the loss condition.
    Details details = LossConditionDetails<LossConditionType::Normal>{};
  };

  constexpr LossConditionType LossCondition::type() const noexcept
  {
    constexpr std::size_t kNormalDetailsIndex = 3;
    static_assert(std::is_same_v<std::variant_alternative_t<kNormalDetailsIndex, Details>,
                                 LossConditionDetails<LossConditionType::Normal>>,
                  "kNormalDetailsIndex must be the index of the alternative for Normal loss condition.");

    const std::size_t index = details.index();
    // Hack to avoid writing a switch statement over all loss condition types.
    if (index == kNormalDetailsIndex)
    {
      return LossConditionType::Normal;
    }
    return static_cast<LossConditionType>(index);
  }

  // Get the 0-based index of the alternative corresponding to the given LossConditionType.
  // \param loss_condition_type - input LossConditionType.
  // \return 0-based index of the alternative from LossCondition::Details that has the type
  //         LossConditionDetails<loss_condition_type>, or std::variant_npos if there is no such alternative.
  constexpr std::size_t LossCondition::getAlternativeIdx(LossConditionType loss_condition_type) noexcept
  {
    if (loss_condition_type == LossConditionType::Normal)
    {
      return 3;
    }
    const std::size_t idx = static_cast<std::size_t>(loss_condition_type);
    return idx < 3 ? idx : std::variant_npos;
  }
}
