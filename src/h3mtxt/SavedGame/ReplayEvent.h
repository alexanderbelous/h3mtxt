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
  struct ReplayEventDetailsBase
  {
    // Player for which this event was recorded.
    PlayerColor player{};
  };

  template<>
  struct ReplayEventDetails<ReplayEventType::MoveHero> : ReplayEventDetailsBase
  {
    std::uint32_t hero {};
    CompassPoint direction {}; // TODO: rename to orientation -> this only affects the rendered sprite.
    CoordinatesPacked from;
    CoordinatesPacked to;
  };

  template<>
  struct ReplayEventDetails<ReplayEventType::TeleportHero> : ReplayEventDetailsBase
  {
    std::uint32_t hero{};
    CompassPoint orientation {};
    CoordinatesPacked from;
    CoordinatesPacked to;
  };

  template<>
  struct ReplayEventDetails<ReplayEventType::FlagMine> : ReplayEventDetailsBase
  {
    // 0-based index of the flagged object from ObjectPropertiesTables::mines_and_lighthouses.
    std::uint32_t id {};
    PlayerColor owner_old = PlayerColor::None;
    PlayerColor owner_new = PlayerColor::None;
  };

  template<>
  struct ReplayEventDetails<ReplayEventType::CaptureTown> : ReplayEventDetailsBase
  {
    // ID of the town (see Town::id).
    std::uint32_t town_id {};
    PlayerColor owner_old = PlayerColor::None;
    PlayerColor owner_new = PlayerColor::None;
  };

  template<>
  struct ReplayEventDetails<ReplayEventType::HideBoat> : ReplayEventDetailsBase
  {
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
  struct ReplayEventDetails<ReplayEventType::ShowBoat> : ReplayEventDetailsBase
  {
    // unknown[0] is probably Boat::id
    // The rest is smth like boarded_hero, owner_hero_old, owner_hero_new
    std::array<std::uint8_t, 7> unknown {};
    // The new coordinates of the boat.
    CoordinatesPacked coordinates_new;
    // The old coordinates of the boat ((-1, -1, -1) if the boat has just been constructed).
    CoordinatesPacked coordinates_old = { .x = -1, .y = -1, .z = -1 };
  };

  template<>
  struct ReplayEventDetails<ReplayEventType::RemoveMapItem> : ReplayEventDetailsBase
  {
    // Coordinates of the actionable tile.
    CoordinatesPacked coordinates;
    // 0-based index of the object in SavedGame::objects.
    std::uint32_t object_idx {};
    std::array<std::uint8_t, 8> unknown{};
  };

  template<>
  struct ReplayEventDetails<ReplayEventType::HideHero> : ReplayEventDetailsBase
  {
    std::uint32_t hero {};
    // None if the hero is dismissed / defeated.
    PlayerColor owner_new = PlayerColor::None;
    PlayerColor owner_old {};
  };

  template<>
  struct ReplayEventDetails<ReplayEventType::ShowHero> : ReplayEventDetailsBase
  {
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
  struct ReplayEventDetails<ReplayEventType::Unknown10> : ReplayEventDetailsBase
  {
    std::uint8_t unknown{};
  };

  template<>
  struct ReplayEventDetails<ReplayEventType::ChangeTerrainVisibility> : ReplayEventDetailsBase
  {
    struct TileVisiblityChange
    {
      CoordinatesPacked coordinates;
      TileVisibility visibility_old;
      TileVisibility visibility_new;
    };

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
      ReplayEventDetails<ReplayEventType::Unknown10>,
      ReplayEventDetails<ReplayEventType::ChangeTerrainVisibility>
    >;

    // \return ReplayEventType of this event.
    constexpr ReplayEventType type() const noexcept;

    // Returns the 0-based index of the alternative corresponding to the given ReplayEventType.
    // \param event_type - type of the event.
    // \return 0-based index of the alternative from ReplayEvent::Details that has the type
    //         ReplayEventDetails<event_type>, or std::variant_npos if there is no such alternative.
    static constexpr std::size_t getAlternativeIdx(ReplayEventType event_type) noexcept;

    // \return a mutable reference to ReplayEventDetailsBase of the alternative currently stored in @details.
    constexpr ReplayEventDetailsBase& base() noexcept;

    // \return a const reference to ReplayEventDetailsBase of the alternative currently stored in @details.
    constexpr const ReplayEventDetailsBase& base() const noexcept;

    Details details;
  };

  constexpr ReplayEventType ReplayEvent::type() const noexcept
  {
    const std::size_t index = details.index();
    return static_cast<ReplayEventType>(index + 1);
  }

  constexpr std::size_t ReplayEvent::getAlternativeIdx(ReplayEventType event_type) noexcept
  {
    if ((1 <= static_cast<std::size_t>(event_type)) && (static_cast<std::size_t>(event_type) <= 11))
    {
      return static_cast<std::size_t>(event_type) - 1;
    }
    return std::variant_npos;
  }

  constexpr ReplayEventDetailsBase& ReplayEvent::base() noexcept
  {
    return const_cast<ReplayEventDetailsBase&>(const_cast<const ReplayEvent&>(*this).base());
  }

  constexpr const ReplayEventDetailsBase& ReplayEvent::base() const noexcept
  {
    return std::visit([] <ReplayEventType T> (const ReplayEventDetails<T>& details) -> const ReplayEventDetailsBase&
                      {
                        return details;
                      },
                      details);
  }
}
