#pragma once

#include <h3mtxt/Map/Constants/ArtifactType.h>

#include <vector>

namespace h3m
{
  // 0xFFFF implies "default" (generally empty) for any slot.
  struct HeroArtifacts
  {
    ArtifactType head {0xFFFF};
    ArtifactType shoulders {0xFFFF};
    ArtifactType neck {0xFFFF};
    ArtifactType right_hand {0xFFFF};
    ArtifactType left_hand {0xFFFF};
    ArtifactType torso {0xFFFF};
    ArtifactType right_ring {0xFFFF};
    ArtifactType left_ring {0xFFFF};
    ArtifactType feet {0xFFFF};
    ArtifactType misc1 {0xFFFF};
    ArtifactType misc2 {0xFFFF};
    ArtifactType misc3 {0xFFFF};
    ArtifactType misc4 {0xFFFF};
    ArtifactType device1 {0xFFFF};  // TODO: rename to war_machine_1
    ArtifactType device2 {0xFFFF};
    ArtifactType device3 {0xFFFF};
    // Catapult's slot, not accessible via the Editor, always empty.
    ArtifactType device4 {0xFFFF};
    ArtifactType spellbook {0xFFFF};
    ArtifactType misc5 {0xFFFF};
    std::vector<ArtifactType> backpack;
  };
}
