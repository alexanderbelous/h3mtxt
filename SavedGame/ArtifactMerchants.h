#pragma once

#include <h3mtxt/SavedGame/SavedGameFwd.h>

#include <array>

namespace h3svg
{
  // Represents the state of Artifact Merchants or a Black Market on the Adventure Map.
  struct ArtifactMerchants
  {
    // Each element should be either a valid ArtifactType constant or -1 if the slot is empty.
    std::array<ArtifactType32, 7> artifacts {};
  };
}
