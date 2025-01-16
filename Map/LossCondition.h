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
  std::uint8_t x {};
  std::uint8_t y {};
  std::uint8_t z {};
};

// Specialization for TimeExpires.
template<>
struct LossConditionDetails<LossConditionType::TimeExpires>
{
  std::uint16_t days {};
};

// Specialization for Normal.
template<>
struct LossConditionDetails<LossConditionType::Normal>
{
};

class LossCondition
{
public:
  // Constructs a normal loss condition.
  constexpr LossCondition() noexcept;

  // Constructs a loss condition.
  // \param details - details of the loss condition.
  template<LossConditionType T>
  constexpr LossCondition(LossConditionDetails<T> details) noexcept;

  // \return the type of the loss condition.
  constexpr LossConditionType type() const noexcept;

  // Details of the loss condition.
  std::variant<
    LossConditionDetails<LossConditionType::LoseTown>,
    LossConditionDetails<LossConditionType::LoseHero>,
    LossConditionDetails<LossConditionType::TimeExpires>,
    LossConditionDetails<LossConditionType::Normal>
  > details;
};

constexpr LossCondition::LossCondition() noexcept:
  details(LossConditionDetails<LossConditionType::Normal>{})
{}

template<LossConditionType T>
constexpr LossCondition::template LossCondition(LossConditionDetails<T> details) noexcept:
  details(std::move(details))
{}

constexpr LossConditionType LossCondition::type() const noexcept
{
  constexpr std::size_t kNormalDetailsIndex = 3;
  using DetailsVariant = decltype(details);
  static_assert(std::is_same_v<std::variant_alternative_t<kNormalDetailsIndex, DetailsVariant>,
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

}
