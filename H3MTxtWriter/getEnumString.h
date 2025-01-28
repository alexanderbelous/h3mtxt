#pragma once

// TODO: use forward declarations instead.
#include <h3mtxt/Map/Constants/MetaObjectType.h>
#include <h3mtxt/Map/Constants/ObjectClass.h>
#include <h3mtxt/Map/Constants/RewardType.h>
#include <h3mtxt/Map/Constants/TerrainType.h>
#include <h3mtxt/Map/Constants/QuestType.h>

#include <string_view>

namespace h3m
{
  // Returns a human-readable name for the given enum constant.
  // \param value - input MetaObjectType.
  // \return a human-readable name for @value,
  //         or an empty string_view if @value is not a known MetaObjectType.
  std::string_view getEnumString(MetaObjectType value) noexcept;

  std::string_view getEnumString(ObjectClass value) noexcept;

  std::string_view getEnumString(RewardType value) noexcept;

  std::string_view getEnumString(TerrainType value) noexcept;

  std::string_view getEnumString(QuestType value) noexcept;
}