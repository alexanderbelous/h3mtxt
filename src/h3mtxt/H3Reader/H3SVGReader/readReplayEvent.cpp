#include <h3mtxt/H3Reader/H3SVGReader/H3SVGReader.h>

#include <h3mtxt/SavedGame/Replay.h>

#include <stdexcept>
#include <string> // For debugging

namespace h3svg
{
  ReplayEvent H3SVGReader::readReplayEvent() const
  {
    const ReplayEventType event_type = readEnum<ReplayEventType>();
    switch (event_type)
    {
    case ReplayEventType::MoveHero:
    {
      ReplayEventDetails<ReplayEventType::MoveHero> details;
      details.player = readEnum<PlayerColor>();
      details.hero = readInt<std::uint32_t>();
      details.unknown = readInt<std::uint8_t>();
      details.from = readCoordinatesPacked();
      details.to = readCoordinatesPacked();
      return ReplayEvent{ .details = details };
    }
    case ReplayEventType::TeleportHero:
    {
      ReplayEventDetails<ReplayEventType::TeleportHero> details;
      details.player = readEnum<PlayerColor>();
      details.hero = readInt<std::uint32_t>();
      details.unknown = readInt<std::uint8_t>();
      details.from = readCoordinatesPacked();
      details.to = readCoordinatesPacked();
      return ReplayEvent{ .details = details };
    }
    case ReplayEventType::FlagMine:
    {
      ReplayEventDetails<ReplayEventType::FlagMine> details;
      details.player = readEnum<PlayerColor>();
      details.id = readInt<std::uint32_t>();
      details.owner_old = readEnum<PlayerColor>();
      details.owner_new = readEnum<PlayerColor>();
      return ReplayEvent{ .details = details };
    }
    case ReplayEventType::CaptureTown:
    {
      ReplayEventDetails<ReplayEventType::CaptureTown> details;
      details.player = readEnum<PlayerColor>();
      details.town_id = readInt<std::uint32_t>();
      details.owner_old = readEnum<PlayerColor>();
      details.owner_new = readEnum<PlayerColor>();
      return ReplayEvent{ .details = details };
    }
    case ReplayEventType::ScuttleBoat:
    {
      ReplayEventDetails<ReplayEventType::ScuttleBoat> details;
      details.player = readEnum<PlayerColor>();
      details.boat_id = readInt<std::uint8_t>();
      details.unknown1 = readByteArray<4>();
      details.hero = readEnum<HeroType>();
      details.unknown2 = readInt<std::uint8_t>();
      return ReplayEvent{ .details = details };
    }
    case ReplayEventType::BuildBoat:
    {
      ReplayEventDetails<ReplayEventType::BuildBoat> details;
      details.player = readEnum<PlayerColor>();
      details.unknown1 = readByteArray<7>();
      details.coordinates = readCoordinatesPacked();
      details.unknown2 = readByteArray<4>();
      return ReplayEvent{ .details = details };
    }
    case ReplayEventType::RemoveMapItem:
    {
      ReplayEventDetails<ReplayEventType::RemoveMapItem> details;
      details.player = readEnum<PlayerColor>();
      details.coordinates = readCoordinatesPacked();
      details.unknown = readByteArray<12>();
      return ReplayEvent{ .details = details };
    }
    case ReplayEventType::HideHero:
    {
      ReplayEventDetails<ReplayEventType::HideHero> details;
      details.player = readEnum<PlayerColor>();
      details.hero = readInt<std::uint32_t>();
      details.unknown = readInt<std::uint16_t>();
      return ReplayEvent{ .details = details };
    }
    case ReplayEventType::ShowHero:
    {
      ReplayEventDetails<ReplayEventType::ShowHero> details;
      details.player = readEnum<PlayerColor>();
      details.hero = readInt<std::uint32_t>();
      details.unknown1 = readByteArray<2>();
      details.coordinates = readCoordinatesPacked();
      details.unknown2 = readByteArray<6>();
      return ReplayEvent{ .details = details };
    }
    case ReplayEventType::ChangeTerrainVisibility:
    {
      ReplayEventDetails<ReplayEventType::ChangeTerrainVisibility> details;
      details.player = readEnum<PlayerColor>();
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
      return ReplayEvent{ .details = details };
    }
    default:
      throw std::logic_error("Unsupported ReplayEventType " + std::to_string(static_cast<std::uint8_t>(event_type)));
    }
  }
}
