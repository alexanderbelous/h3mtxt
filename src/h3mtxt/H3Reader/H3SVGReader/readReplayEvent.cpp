#include <h3mtxt/H3Reader/H3SVGReader/H3SVGReader.h>

#include <h3mtxt/SavedGame/ReplayEvent.h>

#include <stdexcept>
#include <string> // For debugging
#include <utility>

namespace h3svg
{
  namespace
  {
    template<ReplayEventType T>
    ReplayEvent::Details readReplayDetailsAsVariant(const H3SVGReader& reader)
    {
      return reader.readReplayEventDetails<T>();
    }
  }

  ReplayEvent H3SVGReader::readReplayEvent() const
  {
    // The number of valid ReplayEventTypes (excluding ReplayEventType{0}, which is invalid).
    static constexpr std::size_t kNumReplayEventTypes = 11;
    using FunctionPtr = ReplayEvent::Details(*)(const H3SVGReader&);
    static constexpr std::array<FunctionPtr, kNumReplayEventTypes> kReaders =
      [] <std::size_t... Indices> (std::index_sequence<Indices...>) consteval
      {
        std::array<FunctionPtr, kNumReplayEventTypes> result = {
          &readReplayDetailsAsVariant<static_cast<ReplayEventType>(Indices + 1)>...
        };
        return result;
      }(std::make_index_sequence<kNumReplayEventTypes>{});

    const ReplayEventType event_type = readEnum<ReplayEventType>();
    if (static_cast<std::size_t>(event_type) < 1 || static_cast<std::size_t>(event_type) > kNumReplayEventTypes)
    {
      throw std::logic_error("Invalid ReplayEventType " + std::to_string(static_cast<std::uint8_t>(event_type)));
    }
    return ReplayEvent{
      .details = kReaders[static_cast<std::size_t>(event_type) - 1](*this)
    };
  }

  template<ReplayEventType T>
  ReplayEventDetails<T> H3SVGReader::readReplayEventDetails() const
  {
    ReplayEventDetails<T> details{ readReplayEventDetailsBase() };
    if constexpr (T == ReplayEventType::MoveHero)
    {
      details.hero = readInt<std::uint32_t>();
      details.direction = readEnum<CompassPoint>();
      details.from = readCoordinatesPacked();
      details.to = readCoordinatesPacked();
    }
    else if constexpr (T == ReplayEventType::TeleportHero)
    {
      details.hero = readInt<std::uint32_t>();
      details.orientation = readEnum<CompassPoint>();
      details.from = readCoordinatesPacked();
      details.to = readCoordinatesPacked();
    }
    else if constexpr (T == ReplayEventType::FlagMine)
    {
      details.id = readInt<std::uint32_t>();
      details.owner_old = readEnum<PlayerColor>();
      details.owner_new = readEnum<PlayerColor>();
    }
    else if constexpr (T == ReplayEventType::CaptureTown)
    {
      details.town_id = readInt<std::uint32_t>();
      details.owner_old = readEnum<PlayerColor>();
      details.owner_new = readEnum<PlayerColor>();
    }
    else if constexpr (T == ReplayEventType::HideBoat)
    {
      details.boat_id = readInt<std::uint8_t>();
      details.unknown = readByteArray<2>();
      details.owner_old = readEnum<HeroType16>();
      details.owner_new = readEnum<HeroType16>();
    }
    else if constexpr (T == ReplayEventType::ShowBoat)
    {
      details.unknown = readByteArray<7>();
      details.coordinates_new = readCoordinatesPacked();
      details.coordinates_old = readCoordinatesPacked();
    }
    else if constexpr (T == ReplayEventType::RemoveMapItem)
    {
      details.coordinates = readCoordinatesPacked();
      details.object_idx = readInt<std::uint32_t>();
      details.unknown = readByteArray<8>();
    }
    else if constexpr (T == ReplayEventType::HideHero)
    {
      details.hero = readInt<std::uint32_t>();
      details.owner_new = readEnum<PlayerColor>();
      details.owner_old = readEnum<PlayerColor>();
    }
    else if constexpr (T == ReplayEventType::ShowHero)
    {
      details.hero = readInt<std::uint32_t>();
      details.owner_new = readEnum<PlayerColor>();
      details.owner_old = readEnum<PlayerColor>();
      details.coordinates_new = readCoordinatesPacked();
      details.coordinates_old = readCoordinatesPacked();
      details.unknown = readByteArray<2>();
    }
    else if constexpr (T == ReplayEventType::DefeatPlayer)
    {
      details.unknown = readInt<std::uint8_t>();
    }
    else if constexpr (T == ReplayEventType::ChangeTerrainVisibility)
    {
      const std::uint16_t num_tiles = readInt<std::uint16_t>();
      details.changes.reserve(num_tiles);
      for (std::uint16_t i = 0; i < num_tiles; ++i)
      {
        ReplayEventDetails<ReplayEventType::ChangeTerrainVisibility>::TileVisiblityChange change;
        change.coordinates = readCoordinatesPacked();
        change.visibility_old = readTileVisibility();
        change.visibility_new = readTileVisibility();
        details.changes.push_back(change);
      }
    }
    else
    {
      static_assert(false, "Invalid ReplayEventType.");
    }
    return details;
  }

  ReplayEventDetailsBase H3SVGReader::readReplayEventDetailsBase() const
  {
    return ReplayEventDetailsBase{
      .player = readEnum<PlayerColor>()
    };
  }
}
