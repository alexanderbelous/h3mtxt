#pragma once

#include <h3mtxt/Map/Constants/MetaObjectType.h>

#include <string_view>

namespace h3m
{
  // Returns a human-readable name for the given enum constant.
  // \param value - input MetaObjectType.
  // \return a human-readable name for @value,
  //         or an empty string_view if @value is not a known MetaObjectType.
  std::string_view getEnumString(MetaObjectType value) noexcept;
}