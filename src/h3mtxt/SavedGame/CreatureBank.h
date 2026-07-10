#pragma once

#include <h3mtxt/SavedGame/SavedGame.h>

#include <h3mtxt/Map/Constants/CreatureType.h>
#include <h3mtxt/Map/Constants/ResourceType.h>
#include <h3mtxt/Map/Utils/TypedQuantity.h>
#include <h3mtxt/SavedGame/Troops.h>

#include <cstdint>
#include <vector>

namespace h3svg
{
  struct CreatureBank
  {
    Troops guards;
    // Resources given as a reward.
    Resources resources;
    // Creatures given as a reward.
    // TODO: check if the quantity is signed.
    TypedQuantity<CreatureType32, std::uint8_t> creatures;
    // Artifacts given as a reward.
    // The length is serialized as a 16-bit integer.
    std::vector<ArtifactType32> artifacts;
  };
}
