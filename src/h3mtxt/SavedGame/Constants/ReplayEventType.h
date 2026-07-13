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
    HideBoat                = 5, // A hero boards or scuttles a boat.
    ShowBoat                = 6, // A hero disembarks from a boat or a player builds a new boat.
    RemoveMapItem           = 7, // Defeat monster, pick up resource, pick up artifact.
    HideHero                = 8, // A hero was dismissed/garrisoned or retreated from a battle.
    ShowHero                = 9, // A hero was hired/de-garrisoned.
    ChangeTerrainVisibility = 11 // Changes in terrain visibility due to hero movement / Cover of Darkness, etc.
  };
}
