#pragma once

#include <h3mtxt/Map/MapFwd.h>

#include <cstdint>

namespace h3m
{
  enum class ArtifactSlot : std::uint8_t
  {
    Head        = 0,
    Shoulders   = 1,
    Neck        = 2,
    RightHand   = 3,
    LeftHand    = 4,
    Torso       = 5,
    RightRing   = 6,
    LeftRing    = 7,
    Feet        = 8,
    Misc1       = 9,
    Misc2       = 10,
    Misc3       = 11,
    Misc4       = 12,
    WarMachine1 = 13,  // Ballista
    WarMachine2 = 14,  // Ammo Cart
    WarMachine3 = 15,  // First Aid Tent
    WarMachine4 = 16,  // Catapult; not accessible via the Editor, always empty.
    Spellbook   = 17,
    Misc5       = 18
  };

  inline constexpr std::uint8_t kNumArtifactSlots = 19;
}
