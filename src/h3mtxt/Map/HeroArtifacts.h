#pragma once

#include <h3mtxt/Map/Constants/ArtifactSlot.h>
#include <h3mtxt/Map/Constants/ArtifactType.h>
#include <h3mtxt/Map/Utils/EnumIndexedArray.h>
#include <h3mtxt/Map/Utils/makeArrayOfDuplicates.h>

#include <vector>

namespace h3m
{
  struct HeroArtifacts
  {
    constexpr bool operator==(const HeroArtifacts&) const noexcept = default;

    // The default value for HeroArtifacts::equipped: all slots are empty.
    static constexpr EnumIndexedArray<ArtifactSlot, ArtifactType, kNumArtifactSlots> kNoEquippedArtifacts = {
      .data = Detail_NS::makeArrayOfDuplicates<kNumArtifactSlots>(ArtifactType::None)
    };

    // FYI: ArtifactSlot::Misc5 is only meaningful for MapFormat::ShadowOfDeath.
    EnumIndexedArray<ArtifactSlot, ArtifactType, kNumArtifactSlots> equipped = kNoEquippedArtifacts;
    std::vector<ArtifactType> backpack;
  };
}
