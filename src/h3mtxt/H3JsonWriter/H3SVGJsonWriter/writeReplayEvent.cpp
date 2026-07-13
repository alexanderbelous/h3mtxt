#include <h3mtxt/H3JsonWriter/H3SVGJsonWriter/H3SVGJsonWriter.h>

#include <h3mtxt/H3JsonWriter/H3MJsonWriter/H3MJsonWriter.h>
#include <h3mtxt/H3JsonWriter/H3MJsonWriter/Utils.h>
#include <h3mtxt/JsonCommon/FieldNamesH3M.h>
#include <h3mtxt/JsonCommon/FieldNamesH3SVG.h>
#include <h3mtxt/Medea/Medea.h>
#include <h3mtxt/SavedGame/Replay.h>

namespace Medea_NS
{
  template<>
  void JsonObjectWriter<h3svg::ReplayEventDetails<h3svg::ReplayEventType::MoveHero>>::operator()(
    FieldsWriter& out, const h3svg::ReplayEventDetails<h3svg::ReplayEventType::MoveHero>& details) const
  {
    out.writeField("player", details.player);
    out.writeField("hero", details.hero);
    out.writeField("direction", details.direction);
    out.writeField("from", details.from);
    out.writeField("to", details.to);
  }

  template<>
  void JsonObjectWriter<h3svg::ReplayEventDetails<h3svg::ReplayEventType::TeleportHero>>::operator()(
    FieldsWriter& out, const h3svg::ReplayEventDetails<h3svg::ReplayEventType::TeleportHero>& details) const
  {
    out.writeField("player", details.player);
    out.writeField("hero", details.hero);
    out.writeField("orientation", details.orientation);
    out.writeField("from", details.from);
    out.writeField("to", details.to);
  }

  template<>
  void JsonObjectWriter<h3svg::ReplayEventDetails<h3svg::ReplayEventType::FlagMine>>::operator()(
    FieldsWriter& out, const h3svg::ReplayEventDetails<h3svg::ReplayEventType::FlagMine>& details) const
  {
    out.writeField("player", details.player);
    out.writeField("id", details.id);
    out.writeField("owner_old", details.owner_old);
    out.writeField("owner_new", details.owner_new);
  }

  template<>
  void JsonObjectWriter<h3svg::ReplayEventDetails<h3svg::ReplayEventType::CaptureTown>>::operator()(
    FieldsWriter& out, const h3svg::ReplayEventDetails<h3svg::ReplayEventType::CaptureTown>& details) const
  {
    out.writeField("player", details.player);
    out.writeField("town_id", details.town_id);
    out.writeField("owner_old", details.owner_old);
    out.writeField("owner_new", details.owner_new);
  }

  template<>
  void JsonObjectWriter<h3svg::ReplayEventDetails<h3svg::ReplayEventType::HideBoat>>::operator()(
    FieldsWriter& out, const h3svg::ReplayEventDetails<h3svg::ReplayEventType::HideBoat>& details) const
  {
    out.writeField("player", details.player);
    out.writeField("boat_id", details.boat_id);
    out.writeField("unknown1", details.unknown1);
    out.writeField("hero", details.hero);
    out.writeField("unknown2", details.unknown2);
  }

  template<>
  void JsonObjectWriter<h3svg::ReplayEventDetails<h3svg::ReplayEventType::ShowBoat>>::operator()(
    FieldsWriter& out, const h3svg::ReplayEventDetails<h3svg::ReplayEventType::ShowBoat>& details) const
  {
    out.writeField("player", details.player);
    out.writeField("unknown1", details.unknown1);
    out.writeField("coordinates_new", details.coordinates_new);
    out.writeField("coordinates_old", details.coordinates_old);
  }

  template<>
  void JsonObjectWriter<h3svg::ReplayEventDetails<h3svg::ReplayEventType::RemoveMapItem>>::operator()(
    FieldsWriter& out, const h3svg::ReplayEventDetails<h3svg::ReplayEventType::RemoveMapItem>& details) const
  {
    out.writeField("player", details.player);
    out.writeField("coordinates", details.coordinates);
    out.writeField("unknown", details.unknown);
  }

  template<>
  void JsonObjectWriter<h3svg::ReplayEventDetails<h3svg::ReplayEventType::HideHero>>::operator()(
    FieldsWriter& out, const h3svg::ReplayEventDetails<h3svg::ReplayEventType::HideHero>& details) const
  {
    out.writeField("player", details.player);
    out.writeField("hero", details.hero);
    out.writeField("owner_new", details.owner_new);
    out.writeField("owner_old", details.owner_old);
  }

  template<>
  void JsonObjectWriter<h3svg::ReplayEventDetails<h3svg::ReplayEventType::ShowHero>>::operator()(
    FieldsWriter& out, const h3svg::ReplayEventDetails<h3svg::ReplayEventType::ShowHero>& details) const
  {
    out.writeField("player", details.player);
    out.writeField("hero", details.hero);
    out.writeField("owner_new", details.owner_new);
    out.writeField("owner_old", details.owner_old);
    out.writeField("coordinates_new", details.coordinates_new);
    out.writeField("coordinates_old", details.coordinates_old);
    out.writeField("unknown", details.unknown);
  }

  template<>
  void JsonObjectWriter<h3svg::ReplayEventDetails<h3svg::ReplayEventType::ChangeTerrainVisibility>::TileVisiblityChange>::operator()(
    FieldsWriter& out,
    const h3svg::ReplayEventDetails<h3svg::ReplayEventType::ChangeTerrainVisibility>::TileVisiblityChange & change) const
  {
    out.writeField("coordinates", change.coordinates);
    out.writeField("visibility_old", change.visibility_old);
    out.writeField("visibility_new", change.visibility_new);
  }

  template<>
  void JsonObjectWriter<h3svg::ReplayEventDetails<h3svg::ReplayEventType::ChangeTerrainVisibility>>::operator()(
    FieldsWriter& out, const h3svg::ReplayEventDetails<h3svg::ReplayEventType::ChangeTerrainVisibility>& details) const
  {
    out.writeField("player", details.player);
    out.writeField("changes", details.changes);
  }

  template<>
  void JsonObjectWriter<h3svg::ReplayEvent>::operator()(FieldsWriter& out,
                                                        const h3svg::ReplayEvent& replay_event) const
  {
    out.writeField("type", replay_event.type());
    std::visit([&out] <h3svg::ReplayEventType T> (const h3svg::ReplayEventDetails<T>& details)
               {
                 out.writeField("details", details);
               },
               replay_event.details);
  }
}
