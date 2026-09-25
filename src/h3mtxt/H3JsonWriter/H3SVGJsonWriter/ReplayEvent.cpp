#include <h3mtxt/H3JsonWriter/H3SVGJsonWriter/H3SVGJsonWriter.h>

#include <h3mtxt/H3JsonWriter/H3MJsonWriter/Utils.h>
#include <h3mtxt/JsonCommon/FieldNamesH3SVG.h>
#include <h3mtxt/Medea/Medea.h>
#include <h3mtxt/SavedGame/Replay.h>

namespace Medea_NS
{
  template<>
  void JsonObjectWriter<h3svg::ReplayEventDetails<h3svg::ReplayEventType::MoveHero>>::operator()(
    FieldsWriter& out, const h3svg::ReplayEventDetails<h3svg::ReplayEventType::MoveHero>& details) const
  {
    using Fields = h3json::FieldNames<h3svg::ReplayEventDetails<h3svg::ReplayEventType::MoveHero>>;
    out.writeField(Fields::kPlayer, details.player);
    out.writeField(Fields::kHero, details.hero);
    out.writeField(Fields::kDirection, details.direction);
    out.writeField(Fields::kFrom, details.from);
    out.writeField(Fields::kTo, details.to);
  }

  template<>
  void JsonObjectWriter<h3svg::ReplayEventDetails<h3svg::ReplayEventType::TeleportHero>>::operator()(
    FieldsWriter& out, const h3svg::ReplayEventDetails<h3svg::ReplayEventType::TeleportHero>& details) const
  {
    using Fields = h3json::FieldNames<h3svg::ReplayEventDetails<h3svg::ReplayEventType::TeleportHero>>;
    out.writeField(Fields::kPlayer, details.player);
    out.writeField(Fields::kHero, details.hero);
    out.writeField(Fields::kOrientation, details.orientation);
    out.writeField(Fields::kFrom, details.from);
    out.writeField(Fields::kTo, details.to);
  }

  template<>
  void JsonObjectWriter<h3svg::ReplayEventDetails<h3svg::ReplayEventType::FlagMine>>::operator()(
    FieldsWriter& out, const h3svg::ReplayEventDetails<h3svg::ReplayEventType::FlagMine>& details) const
  {
    using Fields = h3json::FieldNames<h3svg::ReplayEventDetails<h3svg::ReplayEventType::FlagMine>>;
    out.writeField(Fields::kPlayer, details.player);
    out.writeField(Fields::kId, details.id);
    out.writeField(Fields::kOwnerOld, details.owner_old);
    out.writeField(Fields::kOwnerNew, details.owner_new);
  }

  template<>
  void JsonObjectWriter<h3svg::ReplayEventDetails<h3svg::ReplayEventType::CaptureTown>>::operator()(
    FieldsWriter& out, const h3svg::ReplayEventDetails<h3svg::ReplayEventType::CaptureTown>& details) const
  {
    using Fields = h3json::FieldNames<h3svg::ReplayEventDetails<h3svg::ReplayEventType::CaptureTown>>;
    out.writeField(Fields::kPlayer, details.player);
    out.writeField(Fields::kTownId, details.town_id);
    out.writeField(Fields::kOwnerOld, details.owner_old);
    out.writeField(Fields::kOwnerNew, details.owner_new);
  }

  template<>
  void JsonObjectWriter<h3svg::ReplayEventDetails<h3svg::ReplayEventType::HideBoat>>::operator()(
    FieldsWriter& out, const h3svg::ReplayEventDetails<h3svg::ReplayEventType::HideBoat>& details) const
  {
    using Fields = h3json::FieldNames<h3svg::ReplayEventDetails<h3svg::ReplayEventType::HideBoat>>;
    out.writeField(Fields::kPlayer, details.player);
    out.writeField(Fields::kBoatId, details.boat_id);
    out.writeField(Fields::kUnknown, details.unknown);
    out.writeField(Fields::kOwnerOld, details.owner_old);
    out.writeField(Fields::kOwnerNew, details.owner_new);
  }

  template<>
  void JsonObjectWriter<h3svg::ReplayEventDetails<h3svg::ReplayEventType::ShowBoat>>::operator()(
    FieldsWriter& out, const h3svg::ReplayEventDetails<h3svg::ReplayEventType::ShowBoat>& details) const
  {
    using Fields = h3json::FieldNames<h3svg::ReplayEventDetails<h3svg::ReplayEventType::ShowBoat>>;
    out.writeField(Fields::kPlayer, details.player);
    out.writeField(Fields::kUnknown, details.unknown);
    out.writeField(Fields::kCoordinatesNew, details.coordinates_new);
    out.writeField(Fields::kCoordinatesOld, details.coordinates_old);
  }

  template<>
  void JsonObjectWriter<h3svg::ReplayEventDetails<h3svg::ReplayEventType::RemoveMapItem>>::operator()(
    FieldsWriter& out, const h3svg::ReplayEventDetails<h3svg::ReplayEventType::RemoveMapItem>& details) const
  {
    using Fields = h3json::FieldNames<h3svg::ReplayEventDetails<h3svg::ReplayEventType::RemoveMapItem>>;
    out.writeField(Fields::kPlayer, details.player);
    out.writeField(Fields::kCoordinates, details.coordinates);
    out.writeField(Fields::kUnknown, details.unknown);
  }

  template<>
  void JsonObjectWriter<h3svg::ReplayEventDetails<h3svg::ReplayEventType::HideHero>>::operator()(
    FieldsWriter& out, const h3svg::ReplayEventDetails<h3svg::ReplayEventType::HideHero>& details) const
  {
    using Fields = h3json::FieldNames<h3svg::ReplayEventDetails<h3svg::ReplayEventType::HideHero>>;
    out.writeField(Fields::kPlayer, details.player);
    out.writeField(Fields::kHero, details.hero);
    out.writeField(Fields::kOwnerNew, details.owner_new);
    out.writeField(Fields::kOwnerOld, details.owner_old);
  }

  template<>
  void JsonObjectWriter<h3svg::ReplayEventDetails<h3svg::ReplayEventType::ShowHero>>::operator()(
    FieldsWriter& out, const h3svg::ReplayEventDetails<h3svg::ReplayEventType::ShowHero>& details) const
  {
    using Fields = h3json::FieldNames<h3svg::ReplayEventDetails<h3svg::ReplayEventType::ShowHero>>;
    out.writeField(Fields::kPlayer, details.player);
    out.writeField(Fields::kHero, details.hero);
    out.writeField(Fields::kOwnerNew, details.owner_new);
    out.writeField(Fields::kOwnerOld, details.owner_old);
    out.writeField(Fields::kCoordinatesNew, details.coordinates_new);
    out.writeField(Fields::kCoordinatesOld, details.coordinates_old);
    out.writeField(Fields::kUnknown, details.unknown);
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
    using Fields = h3json::FieldNames<h3svg::ReplayEventDetails<h3svg::ReplayEventType::ChangeTerrainVisibility>>;
    out.writeField(Fields::kPlayer, details.player);
    out.writeField(Fields::kChanges, details.changes);
  }

  template<>
  void JsonObjectWriter<h3svg::ReplayEvent>::operator()(FieldsWriter& out,
                                                        const h3svg::ReplayEvent& replay_event) const
  {
    using Fields = h3json::FieldNames<h3svg::ReplayEvent>;
    out.writeField(Fields::kType, replay_event.type());
    std::visit([&out] <h3svg::ReplayEventType T> (const h3svg::ReplayEventDetails<T>& details)
               {
                 out.writeField(Fields::kDetails, details);
               },
               replay_event.details);
  }
}
