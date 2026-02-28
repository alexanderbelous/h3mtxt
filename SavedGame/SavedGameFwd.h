#pragma once

#include <cstddef>
#include <cstdint>

// Forward declarations of some types used in h3m::SavedGame.
namespace h3m
{
  enum class ArtifactType32 : std::int32_t;

  enum class TownType32 : std::int32_t;

  struct Alignments;

  template<class Enum, std::size_t NumElements>
  struct EnumBoolmask;

  struct BlackMarket;

  struct Coordinates;

  struct ObjectTemplateSvg;

  struct PlayerSpecsSvg;

  struct RumorSvg;

  struct SavedGame;

  struct TileSvg;
}