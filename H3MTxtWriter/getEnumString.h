#pragma once

#include <h3mtxt/Map/MapFwd.h>

#include <string_view>

namespace h3m
{
  std::string_view getEnumString(h3m::Disposition value) noexcept;

  // Returns a human-readable name for the given enum constant.
  // \param value - input MetaObjectType.
  // \return a human-readable name for @value,
  //         or an empty string_view if @value is not a known MetaObjectType.
  std::string_view getEnumString(MetaObjectType value) noexcept;

  std::string_view getEnumString(ObjectClass value) noexcept;

  std::string_view getEnumString(QuestType value) noexcept;

  std::string_view getEnumString(RewardType value) noexcept;

  std::string_view getEnumString(RiverType value) noexcept;

  std::string_view getEnumString(RoadType value) noexcept;

  std::string_view getEnumString(SecondarySkillType value) noexcept;

  std::string_view getEnumString(TerrainType value) noexcept;

  std::string_view getEnumString(VictoryConditionType value) noexcept;
}