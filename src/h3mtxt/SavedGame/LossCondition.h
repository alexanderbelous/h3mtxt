#pragma once

#include <h3mtxt/SavedGame/SavedGameFwd.h>

#include <h3mtxt/Map/Constants/LossConditionType.h>
#include <h3mtxt/Map/LossCondition.h>

#include <variant>

namespace h3svg
{
  // The default implementation reuses h3m::LossConditionDetails.
  template<LossConditionType T>
  struct LossConditionDetails : h3m::LossConditionDetails<T>
  {};

  // Specialization for LoseHero.
  template<>
  struct LossConditionDetails<LossConditionType::LoseHero>
  {
    HeroType16 hero {};
  };

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

    // Returns the 0-based index of the alternative corresponding to the given LossConditionType.
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

  constexpr std::size_t LossCondition::getAlternativeIdx(LossConditionType loss_condition_type) noexcept
  {
    // Reuse h3m::LossCondition::getAlternativeIdx().
    return h3m::LossCondition::getAlternativeIdx(loss_condition_type);
  }
}
