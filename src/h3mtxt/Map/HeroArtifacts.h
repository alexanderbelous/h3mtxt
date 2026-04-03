#pragma once

#include <h3mtxt/Map/Constants/ArtifactSlot.h>
#include <h3mtxt/Map/Constants/ArtifactType.h>
#include <h3mtxt/Map/Utils/EnumIndexedArray.h>

#include <vector>

namespace h3m
{
  struct HeroArtifacts
  {
    constexpr bool operator==(const HeroArtifacts&) const = default;
    constexpr bool operator!=(const HeroArtifacts&) const = default;

    static constexpr EnumIndexedArray<ArtifactSlot, ArtifactType, kNumArtifactSlots> kNoEquippedArtifacts =
      []() consteval
      {
        EnumIndexedArray<ArtifactSlot, ArtifactType, kNumArtifactSlots> artifacts;
        for (ArtifactType& artifact : artifacts.data)
        {
          artifact = ArtifactType::None;
        }
        return artifacts;
      }();

    EnumIndexedArray<ArtifactSlot, ArtifactType, kNumArtifactSlots> equipped = kNoEquippedArtifacts;
    std::vector<ArtifactType> backpack;
  };
}
