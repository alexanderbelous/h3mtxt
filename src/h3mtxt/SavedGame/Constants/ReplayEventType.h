#pragma once

#include <h3mtxt/SavedGame/SavedGameFwd.h>

#include <cstdint>

namespace h3svg
{
  enum class ReplayEventType : std::uint8_t
  {
    MoveHero                = 1,
    TeleportHero            = 2, // A hero teleports via Monolith, Town Portal, Dimension Door, etc.
    FlagMine                = 3, // Flag mine/lighthouse (NOT garrison/dwelling)
    CaptureTown             = 4,
    ScuttleBoat             = 5, // TODO: rename to HideBoat. This is also recorded when a hero boards a boat.
    BuildBoat               = 6,
    RemoveMapItem           = 7, // Defeat monster, pick up resource, pick up artifact.
    HideHero                = 8, // A hero was dismissed/garrisoned or retreated from a battle.
    ShowHero                = 9, // A hero was hired/de-garrisoned.
    ChangeTerrainVisibility = 11 // Changes in terrain visibility due to hero movement / Cover of Darkness, etc.
  };
}
