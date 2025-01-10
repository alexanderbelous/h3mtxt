#pragma once

#include <h3mparser/Constants/LossConditionType.h>

#include <cstdint>
#include <variant>

namespace h3m
{

// Template class for storing details of a loss condition.
// The default implementation stores no details.
template<LossConditionType T>
struct LossConditionDetails
{
};

// Specialization for LoseTown.
template<>
struct LossConditionDetails<LossConditionType::LoseTown>
{
  std::uint8_t x {};
  std::uint8_t y {};
  std::uint8_t z {};
};

// Specialization for LoseHero.
template<>
struct LossConditionDetails<LossConditionType::LoseHero>
{
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

class LossCondition
{
public:
  // Constructs a loss condition.
  // \param T - type of the loss condition.
  // \param details - details of the loss condition.
  // \return the constructed loss condition.
  template<LossConditionType T>
  static LossConditionType makeLossCondition(LossConditionDetails<T> details);

  // \return the type of the loss condition.
  LossConditionType type() const;

  // Get the details of the loss condition.
  // \param T - type of the loss condition.
  // \return the details of the loss condition, nullptr if T doesn't match the type returned by type().
  template<LossConditionType T>
  const LossConditionDetails<T>* details() const;

private:
  std::variant<
    LossConditionDetails<LossConditionType::LoseTown>,
    LossConditionDetails<LossConditionType::LoseHero>,
    LossConditionDetails<LossConditionType::TimeExpires>,
    LossConditionDetails<LossConditionType::Normal>
  > details_ {};
};

}
