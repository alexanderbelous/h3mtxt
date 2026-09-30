#include <h3mtxt/H3Writer/H3SVGWriter/H3SVGWriter.h>

#include <h3mtxt/SavedGame/ReplayEvent.h>

namespace h3svg
{
  template<>
  void H3SVGWriter::writeData(const ReplayEventDetails<ReplayEventType::MoveHero>& details) const
  {
    writeData(static_cast<const ReplayEventDetailsBase&>(details));
    writeData(details.hero);
    writeData(details.direction);
    writeData(details.from);
    writeData(details.to);
  }

  template<>
  void H3SVGWriter::writeData(const ReplayEventDetails<ReplayEventType::TeleportHero>& details) const
  {
    writeData(static_cast<const ReplayEventDetailsBase&>(details));
    writeData(details.hero);
    writeData(details.orientation);
    writeData(details.from);
    writeData(details.to);
  }

  template<>
  void H3SVGWriter::writeData(const ReplayEventDetails<ReplayEventType::FlagMine>& details) const
  {
    writeData(static_cast<const ReplayEventDetailsBase&>(details));
    writeData(details.id);
    writeData(details.owner_old);
    writeData(details.owner_new);
  }

  template<>
  void H3SVGWriter::writeData(const ReplayEventDetails<ReplayEventType::CaptureTown>& details) const
  {
    writeData(static_cast<const ReplayEventDetailsBase&>(details));
    writeData(details.town_id);
    writeData(details.owner_old);
    writeData(details.owner_new);
  }

  template<>
  void H3SVGWriter::writeData(const ReplayEventDetails<ReplayEventType::HideBoat>& details) const
  {
    writeData(static_cast<const ReplayEventDetailsBase&>(details));
    writeData(details.boat_id);
    writeData(details.unknown);
    writeData(details.owner_old);
    writeData(details.owner_new);
  }

  template<>
  void H3SVGWriter::writeData(const ReplayEventDetails<ReplayEventType::ShowBoat>& details) const
  {
    writeData(static_cast<const ReplayEventDetailsBase&>(details));
    writeData(details.unknown);
    writeData(details.coordinates_new);
    writeData(details.coordinates_old);
  }

  template<>
  void H3SVGWriter::writeData(const ReplayEventDetails<ReplayEventType::RemoveMapItem>& details) const
  {
    writeData(static_cast<const ReplayEventDetailsBase&>(details));
    writeData(details.coordinates);
    writeData(details.object_idx);
    writeData(details.unknown);
  }

  template<>
  void H3SVGWriter::writeData(const ReplayEventDetails<ReplayEventType::HideHero>& details) const
  {
    writeData(static_cast<const ReplayEventDetailsBase&>(details));
    writeData(details.hero);
    writeData(details.owner_new);
    writeData(details.owner_old);
  }

  template<>
  void H3SVGWriter::writeData(const ReplayEventDetails<ReplayEventType::ShowHero>& details) const
  {
    writeData(static_cast<const ReplayEventDetailsBase&>(details));
    writeData(details.hero);
    writeData(details.owner_new);
    writeData(details.owner_old);
    writeData(details.coordinates_new);
    writeData(details.coordinates_old);
    writeData(details.unknown);
  }

  template<>
  void H3SVGWriter::writeData(const ReplayEventDetails<ReplayEventType::DefeatPlayer>& details) const
  {
    writeData(static_cast<const ReplayEventDetailsBase&>(details));
    writeData(details.unknown);
  }

  template<>
  void H3SVGWriter::writeData(const ReplayEventDetails<ReplayEventType::ChangeTerrainVisibility>& details) const
  {
    writeData(static_cast<const ReplayEventDetailsBase&>(details));
    writeData(safeCastVectorSize<std::uint16_t>(details.changes.size()));
    for (const auto& tile : details.changes)
    {
      writeData(tile.coordinates);
      writeData(tile.visibility_old);
      writeData(tile.visibility_new);
    }
  }

  void H3SVGWriter::writeData(const ReplayEventDetailsBase& base) const
  {
    writeData(base.player);
  }

  void H3SVGWriter::writeData(const ReplayEvent& event) const
  {
    writeData(event.type());
    std::visit([this] <ReplayEventType T> (const ReplayEventDetails<T>& details)
               { writeData(details); },
               event.details);
  }
}
