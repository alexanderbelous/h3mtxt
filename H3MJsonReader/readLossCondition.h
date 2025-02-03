#pragma once

#include <h3mtxt/H3MJsonReader/JsonReader.h>
#include <h3mtxt/Map/LossCondition.h>

namespace h3m
{
  template<>
  struct JsonReader<LossConditionDetails<LossConditionType::LoseTown>>
  {
    LossConditionDetails<LossConditionType::LoseTown> operator()(const Json::Value& value) const
    {
      LossConditionDetails<LossConditionType::LoseTown> details;
      details.x = readField<std::uint8_t>(value, "x");
      details.y = readField<std::uint8_t>(value, "y");
      details.z = readField<std::uint8_t>(value, "z");
      return details;
    }
  };

  template<>
  struct JsonReader<LossConditionDetails<LossConditionType::LoseHero>>
  {
    LossConditionDetails<LossConditionType::LoseHero> operator()(const Json::Value& value) const
    {
      LossConditionDetails<LossConditionType::LoseHero> details;
      details.x = readField<std::uint8_t>(value, "x");
      details.y = readField<std::uint8_t>(value, "y");
      details.z = readField<std::uint8_t>(value, "z");
      return details;
    }
  };

  template<>
  struct JsonReader<LossConditionDetails<LossConditionType::TimeExpires>>
  {
    LossConditionDetails<LossConditionType::TimeExpires> operator()(const Json::Value& value) const
    {
      LossConditionDetails<LossConditionType::TimeExpires> details;
      details.days = readField<std::uint16_t>(value, "days");
      return details;
    }
  };

  template<>
  struct JsonReader<LossCondition>
  {
    LossCondition operator()(const Json::Value& value) const
    {
      const LossConditionType loss_condition_type = readField<LossConditionType>(value, "type");
      switch (loss_condition_type)
      {
      case LossConditionType::LoseTown:
        return readField<LossConditionDetails<LossConditionType::LoseTown>>(value, "details");
      case LossConditionType::LoseHero:
        return readField<LossConditionDetails<LossConditionType::LoseHero>>(value, "details");
      case LossConditionType::TimeExpires:
        return readField<LossConditionDetails<LossConditionType::TimeExpires>>(value, "details");
      case LossConditionType::Normal:
        return LossCondition();
      default:
        throw std::runtime_error("JsonReader<LossCondition>: invalid loss_condition_type");
      }
    }
  };
}
