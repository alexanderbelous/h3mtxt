#pragma once

#include <h3mtxt/Map/MapFwd.h>

#include <h3mtxt/Map/Constants/Constants.h>
#include <h3mtxt/Map/Constants/PlayerColor.h>
#include <h3mtxt/Map/Utils/EnumIndexedArray.h>

#include <cstdint>

namespace h3m
{
  struct Teams
  {
    // Equality comparison.
    //
    // FYI: if this->num_teams == 0 && other.num_teams == 0, then
    // the objects are considered equal regardless of what's stored in team_for_player.
    //
    // This reflects the "conditional" nature of team_for_player:
    // ideally, this member shouldn't even exist if num_teams == 0.
    //
    // \param other - Teams to compare with.
    // \return true if @this and @other represent the same Teams setup, false otherwise.
    constexpr bool operator==(const Teams& other) const noexcept;

    std::uint8_t num_teams = 0;
    // This field is only read/written if num_teams != 0.
    // Each value should be < num_teams.
    EnumIndexedArray<PlayerColor, std::uint8_t, kMaxPlayers> team_for_player;
  };

  constexpr bool Teams::operator==(const Teams& other) const noexcept
  {
    return (num_teams == other.num_teams) &&
           ((num_teams == 0) || (team_for_player == other.team_for_player));
  }
}
