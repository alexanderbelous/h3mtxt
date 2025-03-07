#pragma once

#include <h3mtxt/Map/Constants/LossConditionType.h>

#include <cstdint>
#include <variant>

namespace h3m
{
  // Template class for storing details of a loss condition.
  template<LossConditionType T, class Enable = void>
  struct LossConditionDetails;

  // Specialization for LoseTown and LoseHero.
  template<LossConditionType T>
  struct LossConditionDetails<T, std::enable_if_t<T == LossConditionType::LoseTown ||
                                                  T == LossConditionType::LoseHero>>
  {
    // Coordinates of the actionable spot.
    // FYI: apparently, if it's LoseHero and the coordinates do not refer to any hero,
    // the game will ignore them and assume that LossConditionType::Normal is set.
    // If it's LoseTown and the coordinates don't refer to any town, the game will crash
    // at start.
    std::uint8_t x {};
    std::uint8_t y {};
    std::uint8_t z {};
  };

  // Specialization for TimeExpires.
  template<>
  struct LossConditionDetails<LossConditionType::TimeExpires>
  {
    // The Map Editor only allows a number from a small set (2-6 days, 1-7 weeks, 2-12 months),
    // but any signed 16-bit integer can be used here. The Map Editor will freeze when viewing the
    // details of the Loss Condition if a value outside of the above-mentioned set is used, but
    // the game handles them correctly.
    std::int16_t days {};
  };

  // Specialization for Normal.
  template<>
  struct LossConditionDetails<LossConditionType::Normal>
  {
  };

  // Loss condition for the map.
  //
  // This is an aggregate type; the default-constructed LossCondition represents LossConditionType::Normal.
  class LossCondition
  {
  public:
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
