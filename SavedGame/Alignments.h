#pragma once

#include <h3mtxt/SavedGame/SavedGameFwd.h>

#include <h3mtxt/Map/Constants/Constants.h>
#include <h3mtxt/Map/Constants/PlayerColor.h>
#include <h3mtxt/SavedGame/Constants/TownType32.h>

#include <array>
#include <cstddef>

namespace h3m
{
  // Actual alignment for each player (as opposed to potential alignments from PlayerSpecsSvg).
  struct Alignments
  {
    // Mutable access to alignment of the specified player.
    // \param player - input player.
    // \return a mutable reference to TownType32 for @player.
    // \throw std::out_of_range if @player is not a valid PlayerColor,
    //        i.e. if static_cast<int>(player) > 7.
    constexpr TownType32& operator[](PlayerColor player);

    // Read-only access to alignment of the specified player.
    // \param player - input player.
    // \return a const reference to TownType32 for @player.
    // \throw std::out_of_range if @player is not a valid PlayerColor,
    //        i.e. if static_cast<int>(player) > 7.
    constexpr const TownType32& operator[](PlayerColor player) const;

    // Alignment for each player, or 0xFFFFFFFF if the player is absent.
    std::array<TownType32, kMaxPlayers> data{};
  };

  constexpr TownType32& Alignments::operator[](PlayerColor player)
  {
    return data.at(static_cast<std::size_t>(player));
  }

  constexpr const TownType32& Alignments::operator[](PlayerColor player) const
  {
    return data.at(static_cast<std::size_t>(player));
  }
}
