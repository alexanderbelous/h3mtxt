#pragma once

#include <h3mtxt/Map/Constants/ArtifactType.h>

#include <vector>

namespace h3m
{
  struct HeroArtifacts
  {
    ArtifactType head = ArtifactType::None;
    ArtifactType shoulders = ArtifactType::None;
    ArtifactType neck = ArtifactType::None;
    ArtifactType right_hand = ArtifactType::None;
    ArtifactType left_hand = ArtifactType::None;
    ArtifactType torso = ArtifactType::None;
    ArtifactType right_ring = ArtifactType::None;
    ArtifactType left_ring = ArtifactType::None;
    ArtifactType feet = ArtifactType::None;
    ArtifactType misc1 = ArtifactType::None;
    ArtifactType misc2 = ArtifactType::None;
    ArtifactType misc3 = ArtifactType::None;
    ArtifactType misc4 = ArtifactType::None;
    ArtifactType war_machine1 = ArtifactType::None;
    ArtifactType war_machine2 = ArtifactType::None;
    ArtifactType war_machine3 = ArtifactType::None;
    // Catapult's slot, not accessible via the Editor, always empty.
    ArtifactType war_machine4 = ArtifactType::None;
    ArtifactType spellbook = ArtifactType::None;
    ArtifactType misc5 = ArtifactType::None;
    std::vector<ArtifactType> backpack;
  };
}
