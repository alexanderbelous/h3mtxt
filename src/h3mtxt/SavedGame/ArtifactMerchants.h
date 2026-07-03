#pragma once

#include <h3mtxt/SavedGame/SavedGameFwd.h>

#include <h3mtxt/Map/Constants/ArtifactType.h>

#include <array>

namespace h3svg
{
  // Represents the state of Artifact Merchants or a Black Market on the Adventure Map.
  struct ArtifactMerchants
  {
    // Each element should be either a valid ArtifactType constant or -1 if the slot is empty.
    std::array<ArtifactType32, 7> artifacts =
      []() consteval
      {
        std::array<ArtifactType32, 7> result {};
        result.fill(static_cast<ArtifactType32>(ArtifactType::None));
        return result;
      }();
  };
}
