#pragma once

#include <h3mparser/Constants/LossConditionType.h>

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

  // Get the details of the loss condition.
  // \param T - type of the loss condition.
  // \return the details of the loss condition, nullptr if T doesn't match the type returned by type().
  template<LossConditionType T>
  constexpr const LossConditionDetails<T>* details() const noexcept;

private:
  std::variant<
    LossConditionDetails<LossConditionType::LoseTown>,
    LossConditionDetails<LossConditionType::LoseHero>,
    LossConditionDetails<LossConditionType::TimeExpires>,
    LossConditionDetails<LossConditionType::Normal>
  > details_ {};
};

constexpr LossCondition::LossCondition() noexcept:
  details_(LossConditionDetails<LossConditionType::Normal>{})
{}

template<LossConditionType T>
constexpr LossCondition::template LossCondition(LossConditionDetails<T> details) noexcept:
  details_(std::move(details))
{}

constexpr LossConditionType LossCondition::type() const noexcept
{
  const std::size_t index = details_.index();
  // Hack to avoid writing a switch statement over all loss condition types.
  if (index == 3)
  {
    return LossConditionType::Normal;
  }
  return static_cast<LossConditionType>(index);
}

template<LossConditionType T>
constexpr const LossConditionDetails<T>* LossCondition::details() const noexcept
{
  return std::get_if<LossConditionDetails<T>>(details_);
}

}
