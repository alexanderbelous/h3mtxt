#pragma once

#include <h3mtxt/SavedGame/SavedGameFwd.h>

#include <h3mtxt/Map/Constants/PlayerColor.h>
#include <h3mtxt/Map/Utils/EnumBitmask.h>

namespace h3svg
{
  // Information about the visibility of a single tile on the Adventure Map.
  struct TileVisibility
  {
    // 1 bit per player, indicating if the player can see this tile (i.e. it's not obscured by the Fog of War).
    PlayersBitmask visibility;
    // 1 if there is a wandering creature on this tile or an adjacent tile, 0 otherwise.
    // In this case a sword will be rendered when you hover the mouse over this tile, even
    // if the wandering creature is not visible. Note, however, that no sword will be rendered
    // for players for which this tile is still hidden by the Fog of War.
    Bool has_adjacent_monster {};
  };
}
