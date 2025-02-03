#pragma once

#include <h3mtxt/Map/Constants/PlayerColor.h>

#include <array>
#include <string_view>

namespace h3m
{
  namespace Detail_NS
  {
    inline constexpr std::array<std::string_view, 8> kPlayersNames = {
      "red", "blue", "tan", "green", "orange", "purple", "teal", "pink"
    };
  }

  // Returns the name of the field for the specified player in PlayersBitmask.
  //
  // PlayersBitmask is stored as 1 byte in .h3m, but in JSON it's serialized as
  // 8 boolean fields (1 per player).
  // \param player - input PlayerColor.
  // \return the name of the field for @player in PlayersBitmask.
  // \throw std::out_of_range if int(player) >= 8.
  constexpr std::string_view getFieldNameForPlayersBitmask(PlayerColor player)
  {
    return Detail_NS::kPlayersNames.at(static_cast<std::size_t>(player));
  }
}
