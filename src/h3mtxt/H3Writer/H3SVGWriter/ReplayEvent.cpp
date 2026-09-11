#include <h3mtxt/H3Writer/H3SVGWriter/H3SVGWriter.h>

#include <h3mtxt/SavedGame/Replay.h>

namespace h3svg
{
  template<>
  void H3SVGWriter::writeData(const ReplayEventDetails<ReplayEventType::MoveHero>& details) const
  {
    writeData(details.player);
    writeData(details.hero);
    writeData(details.direction);
    writeData(details.from);
    writeData(details.to);
  }

  template<>
  void H3SVGWriter::writeData(const ReplayEventDetails<ReplayEventType::TeleportHero>& details) const
  {
    writeData(details.player);
    writeData(details.hero);
    writeData(details.orientation);
    writeData(details.from);
    writeData(details.to);
  }

  template<>
  void H3SVGWriter::writeData(const ReplayEventDetails<ReplayEventType::FlagMine>& details) const
  {
    writeData(details.player);
    writeData(details.id);
    writeData(details.owner_old);
    writeData(details.owner_new);
  }

  template<>
  void H3SVGWriter::writeData(const ReplayEventDetails<ReplayEventType::CaptureTown>& details) const
  {
    writeData(details.player);
    writeData(details.town_id);
    writeData(details.owner_old);
    writeData(details.owner_new);
  }

  template<>
  void H3SVGWriter::writeData(const ReplayEventDetails<ReplayEventType::HideBoat>& details) const
  {
    writeData(details.player);
    writeData(details.boat_id);
    writeData(details.unknown);
    writeData(details.owner_old);
    writeData(details.owner_new);
  }

  template<>
  void H3SVGWriter::writeData(const ReplayEventDetails<ReplayEventType::ShowBoat>& details) const
  {
    writeData(details.player);
    writeData(details.unknown1);
    writeData(details.coordinates_new);
    writeData(details.coordinates_old);
  }

  template<>
  void H3SVGWriter::writeData(const ReplayEventDetails<ReplayEventType::RemoveMapItem>& details) const
  {
    writeData(details.player);
    writeData(details.coordinates);
    writeData(details.unknown);
  }

  template<>
  void H3SVGWriter::writeData(const ReplayEventDetails<ReplayEventType::HideHero>& details) const
  {
    writeData(details.player);
    writeData(details.hero);
    writeData(details.owner_new);
    writeData(details.owner_old);
  }

  template<>
  void H3SVGWriter::writeData(const ReplayEventDetails<ReplayEventType::ShowHero>& details) const
  {
    writeData(details.player);
    writeData(details.hero);
    writeData(details.owner_new);
    writeData(details.owner_old);
    writeData(details.coordinates_new);
    writeData(details.coordinates_old);
    writeData(details.unknown);
  }

  template<>
  void H3SVGWriter::writeData(const ReplayEventDetails<ReplayEventType::ChangeTerrainVisibility>& details) const
  {
    writeData(details.player);
    writeData(safeCastVectorSize<std::uint16_t>(details.changes.size()));
    for (const auto& tile : details.changes)
    {
      writeData(tile.coordinates);
      writeData(tile.visibility_old);
      writeData(tile.visibility_new);
    }
  }

  void H3SVGWriter::writeData(const ReplayEvent& event) const
  {
    writeData(event.type());
    std::visit([this] <ReplayEventType T> (const ReplayEventDetails<T>& details)
               { writeData(details); },
               event.details);
  }
}
