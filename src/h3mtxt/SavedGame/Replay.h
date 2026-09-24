#pragma once

#include <h3mtxt/SavedGame/SavedGameFwd.h>

#include <h3mtxt/Map/Constants/PlayerColor.h>
#include <h3mtxt/SavedGame/Constants/CompassPoint.h>
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
    CompassPoint direction {};
    CoordinatesPacked from;
    CoordinatesPacked to;
  };

  template<>
  struct ReplayEventDetails<ReplayEventType::TeleportHero>
  {
    PlayerColor player{};
    std::uint32_t hero{};
    CompassPoint orientation {};
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
  struct ReplayEventDetails<ReplayEventType::HideBoat>
  {
    PlayerColor player{};
    // ID of the boat (see Boat::id).
    std::uint8_t boat_id {};
    std::array<std::uint8_t, 2> unknown {};
    // The previous owner or 0xFFFF if there was none.
    HeroType16 owner_old = static_cast<HeroType16>(-1);
    // The new owner.
    // Note that when a hero scuttles a neutral boat they still become an owner of that boat.
    HeroType16 owner_new {};
  };

  template<>
  struct ReplayEventDetails<ReplayEventType::ShowBoat>
  {
    PlayerColor player{};
    // unknown[0] is probably Boat::id
    // The rest is smth like boarded_hero, owner_hero_old, owner_hero_new
    std::array<std::uint8_t, 7> unknown {};
    // The new coordinates of the boat.
    CoordinatesPacked coordinates_new;
    // The old coordinates of the boat ((-1, -1, -1) if the boat has just been constructed).
    CoordinatesPacked coordinates_old = { .x = -1, .y = -1, .z = -1 };
  };

  template<>
  struct ReplayEventDetails<ReplayEventType::RemoveMapItem>
  {
    PlayerColor player{};
    // Coordinates of the actionable tile.
    CoordinatesPacked coordinates;
    std::array<std::uint8_t, 12> unknown{}; // The first 4? bytes are object_idx;
  };

  template<>
  struct ReplayEventDetails<ReplayEventType::HideHero>
  {
    PlayerColor player {};
    std::uint32_t hero {};
    // None if the hero is dismissed / defeated.
    PlayerColor owner_new = PlayerColor::None;
    PlayerColor owner_old {};
  };

  template<>
  struct ReplayEventDetails<ReplayEventType::ShowHero>
  {
    PlayerColor player{};
    std::uint32_t hero{};
    PlayerColor owner_new {};
    // None if the hero has just been hired.
    PlayerColor owner_old = PlayerColor::None;
    CoordinatesPacked coordinates_new;
    // (-1, -1, -1) if the hero wasn't present on the map before.
    CoordinatesPacked coordinates_old = { .x = -1, .y = -1, .z = -1 };
    std::array<std::uint8_t, 2> unknown{};
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
      ReplayEventDetails<ReplayEventType::HideBoat>,
      ReplayEventDetails<ReplayEventType::ShowBoat>,
      ReplayEventDetails<ReplayEventType::RemoveMapItem>,
      ReplayEventDetails<ReplayEventType::HideHero>,
      ReplayEventDetails<ReplayEventType::ShowHero>,
      ReplayEventDetails<ReplayEventType::ChangeTerrainVisibility>
    >;

    // \return ReplayEventType of this event.
    constexpr ReplayEventType type() const noexcept;

    // Returns the 0-based index of the alternative corresponding to the given ReplayEventType.
    // \param event_type - type of the event.
    // \return 0-based index of the alternative from ReplayEvent::Details that has the type
    //         ReplayEventDetails<event_type>, or std::variant_npos if there is no such alternative.
    static constexpr std::size_t getAlternativeIdx(ReplayEventType event_type) noexcept;

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
    case 4: return ReplayEventType::HideBoat;
    case 5: return ReplayEventType::ShowBoat;
    case 6: return ReplayEventType::RemoveMapItem;
    case 7: return ReplayEventType::HideHero;
    case 8: return ReplayEventType::ShowHero;
    case 9: return ReplayEventType::ChangeTerrainVisibility;
    default:
      // Unreachable.
      return static_cast<ReplayEventType>(-1);
    }
  }

  constexpr std::size_t ReplayEvent::getAlternativeIdx(ReplayEventType event_type) noexcept
  {
    switch (event_type)
    {
    case ReplayEventType::MoveHero:                return 0;
    case ReplayEventType::TeleportHero:            return 1;
    case ReplayEventType::FlagMine:                return 2;
    case ReplayEventType::CaptureTown:             return 3;
    case ReplayEventType::HideBoat:                return 4;
    case ReplayEventType::ShowBoat:                return 5;
    case ReplayEventType::RemoveMapItem:           return 6;
    case ReplayEventType::HideHero:                return 7;
    case ReplayEventType::ShowHero:                return 8;
    case ReplayEventType::ChangeTerrainVisibility: return 9;
    default:                                       return std::variant_npos;
    }
  }
}
