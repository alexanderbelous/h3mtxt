#pragma once

#include <h3mtxt/SavedGame/SavedGameFwd.h>

#include <h3mtxt/Map/Constants/PlayerColor.h>
#include <h3mtxt/SavedGame/Constants/ReplayEventType.h>
#include <h3mtxt/SavedGame/CoordinatesPacked.h>
#include <h3mtxt/SavedGame/TileVisibility.h>

#include <array>
#include <variant>
#include <vector>

namespace h3svg
{
  template<>
  struct ReplayEventDetails<ReplayEventType::MoveHero>
  {
    PlayerColor player {};
    std::uint32_t hero {};
    std::uint8_t unknown {}; // Looks like CompassPoint
    CoordinatesPacked from;
    CoordinatesPacked to;
  };

  template<>
  struct ReplayEventDetails<ReplayEventType::TeleportHero>
  {
    PlayerColor player{};
    std::uint32_t hero{};
    std::uint8_t unknown{};
    CoordinatesPacked from;
    CoordinatesPacked to;
  };

  template<>
  struct ReplayEventDetails<ReplayEventType::FlagMine>
  {
    PlayerColor player {};
    // 0-based index of the flagged object from ObjectPropertiesTables::mines_and_lighthouses.
    std::uint32_t id {};
    PlayerColor owner_old = PlayerColor::None;
    PlayerColor owner_new = PlayerColor::None;
  };

  template<>
  struct ReplayEventDetails<ReplayEventType::CaptureTown>
  {
    PlayerColor player{};
    // ID of the town (see Town::id).
    std::uint32_t town_id {};
    PlayerColor owner_old = PlayerColor::None;
    PlayerColor owner_new = PlayerColor::None;
  };

  template<>
  struct ReplayEventDetails<ReplayEventType::ScuttleBoat>
  {
    PlayerColor player{};
    // ID of the boat (see Boat::id).
    std::uint8_t boat_id {};
    std::array<std::uint8_t, 4> unknown1 {};
    HeroType hero {};
    std::uint8_t unknown2 {};
  };

  template<>
  struct ReplayEventDetails<ReplayEventType::BuildBoat>
  {
    PlayerColor player{};
    // unknown[0] is probably Boat::id
    std::array<std::uint8_t, 7> unknown1 {};
    // Coordinates of the boat.
    CoordinatesPacked coordinates;
    std::array<std::uint8_t, 4> unknown2 {};
  };

  template<>
  struct ReplayEventDetails<ReplayEventType::RemoveMapItem>
  {
    PlayerColor player{};
    // Coordinates of the actionable tile.
    CoordinatesPacked coordinates;
    std::array<std::uint8_t, 12> unknown{}; // The first bytes are probably object_idx;
  };

  template<>
  struct ReplayEventDetails<ReplayEventType::HideHero>
  {
    PlayerColor player {};
    std::uint32_t hero {};
    std::uint16_t unknown {}; // Probably should be interpreted as 2 8-bit integers.
  };

  template<>
  struct ReplayEventDetails<ReplayEventType::ShowHero>
  {
    PlayerColor player{};
    std::uint32_t hero{};
    std::array<std::uint8_t, 2> unknown1{}; // unknown1[0] duplicates player?
    CoordinatesPacked coordinates;
    std::array<std::uint8_t, 6> unknown2{}; // bytes [0; 3] look like CoordinatesPacked.
  };

  template<>
  struct ReplayEventDetails<ReplayEventType::ChangeTerrainVisibility>
  {
    struct TileVisiblityChange
    {
      CoordinatesPacked coordinates;
      TileVisibility visibility_old;
      TileVisibility visibility_new;
    };

    PlayerColor player{};
    // Size is serialized as a 16-bit integer.
    std::vector<TileVisiblityChange> changes;
  };

  // Represents a single event on the Adventure Map that should be displayed
  // when replaying the last turn.
  struct ReplayEvent
  {
    using Details = std::variant<
      ReplayEventDetails<ReplayEventType::MoveHero>,
      ReplayEventDetails<ReplayEventType::TeleportHero>,
      ReplayEventDetails<ReplayEventType::FlagMine>,
      ReplayEventDetails<ReplayEventType::CaptureTown>,
      ReplayEventDetails<ReplayEventType::ScuttleBoat>,
      ReplayEventDetails<ReplayEventType::BuildBoat>,
      ReplayEventDetails<ReplayEventType::RemoveMapItem>,
      ReplayEventDetails<ReplayEventType::HideHero>,
      ReplayEventDetails<ReplayEventType::ShowHero>,
      ReplayEventDetails<ReplayEventType::ChangeTerrainVisibility>
    >;

    constexpr ReplayEventType type() const noexcept;

    Details details;
  };

  constexpr ReplayEventType ReplayEvent::type() const noexcept
  {
    const std::size_t index = details.index();
    switch (index)
    {
    case 0: return ReplayEventType::MoveHero;
    case 1: return ReplayEventType::TeleportHero;
    case 2: return ReplayEventType::FlagMine;
    case 3: return ReplayEventType::CaptureTown;
    case 4: return ReplayEventType::ScuttleBoat;
    case 5: return ReplayEventType::BuildBoat;
    case 6: return ReplayEventType::RemoveMapItem;
    case 7: return ReplayEventType::HideHero;
    case 8: return ReplayEventType::ShowHero;
    case 9: return ReplayEventType::ChangeTerrainVisibility;
    default:
      // Unreachable.
      return static_cast<ReplayEventType>(-1);
    }
  }
}
