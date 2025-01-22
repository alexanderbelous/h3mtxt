#pragma once

#include <h3mtxt/Map/Constants/ArtifactType.h>

#include <cstdint>
#include <vector>

namespace h3m
{
  // 0xFFFF implies "default" for any slot, whatever that means (empty?).
  struct HeroArtifacts
  {
    ArtifactType headwear {};
    ArtifactType shoulders {};
    ArtifactType neck {};
    ArtifactType right_hand {};
    ArtifactType left_hand {};
    ArtifactType torso {};
    ArtifactType right_ring {};
    ArtifactType left_ring {};
    ArtifactType feet {};
    ArtifactType misc1 {};
    ArtifactType misc2 {};
    ArtifactType misc3 {};
    ArtifactType misc4 {};
    ArtifactType device1 {};
    ArtifactType device2 {};
    ArtifactType device3 {};
    // Catapult's slot, not accessible via the Editor, always empty.
    ArtifactType device4 {};
    ArtifactType spellbook {};
    ArtifactType misc5 {};
    std::vector<ArtifactType> backpack;
  };
}
