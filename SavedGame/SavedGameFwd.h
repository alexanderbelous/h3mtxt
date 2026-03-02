#pragma once

#include <cstddef>
#include <cstdint>

// Forward declarations of some types used in h3m::SavedGame.
namespace h3m
{
  enum class ArtifactType32 : std::int32_t;

  enum class PlayerControlType : std::int8_t;

  enum class PlayerStartingBonusType : std::uint8_t;

  enum class PlayerTurnDurationType : std::uint8_t;

  enum class TownType32 : std::int32_t;

  template<class Enum, class T, std::size_t NumElements>
  struct EnumIndexedArray;

  struct BlackMarket;

  struct ObjectSvg;

  struct ObjectTemplateSvg;

  struct PlayerSpecsSvg;

  struct RumorSvg;

  struct SavedGame;

  struct TileSvg;
}