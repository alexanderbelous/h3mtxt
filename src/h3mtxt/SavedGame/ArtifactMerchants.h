#pragma once

#include <h3mtxt/SavedGame/SavedGameFwd.h>

#include <h3mtxt/Map/Constants/ArtifactType.h>
#include <h3mtxt/Map/Utils/makeArrayOfDuplicates.h>

#include <array>

namespace h3svg
{
  // Represents the state of Artifact Merchants or a Black Market on the Adventure Map.
  struct ArtifactMerchants
  {
    // The number of slots in Artifact Merchants / Black Market.
    static constexpr std::size_t kNumSlots = 7;

    // Each element should be either a valid ArtifactType constant or -1 if the slot is empty.
    std::array<ArtifactType32, kNumSlots> artifacts =
      h3m::Detail_NS::makeArrayOfDuplicates<kNumSlots>(static_cast<ArtifactType32>(ArtifactType::None));
  };
}
