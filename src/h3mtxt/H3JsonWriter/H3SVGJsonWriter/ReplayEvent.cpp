#include <h3mtxt/H3JsonWriter/H3SVGJsonWriter/H3SVGJsonWriter.h>

#include <h3mtxt/H3JsonWriter/H3MJsonWriter/Utils.h>
#include <h3mtxt/JsonCommon/FieldNamesH3SVG.h>
#include <h3mtxt/Medea/Medea.h>
#include <h3mtxt/SavedGame/ReplayEvent.h>

using ::h3svg::ReplayEvent;
using ::h3svg::ReplayEventDetailsBase;
using ::h3svg::ReplayEventDetails;
using ::h3svg::ReplayEventType;

namespace Medea_NS
{
  template<>
  void JsonObjectWriter<ReplayEventDetailsBase>::operator()(FieldsWriter& out,
                                                            const ReplayEventDetailsBase& base) const
  {
    using Fields = h3json::FieldNames<ReplayEventDetailsBase>;
    out.writeField(Fields::kPlayer, base.player);
  }

  template<>
  void JsonObjectWriter<ReplayEventDetails<ReplayEventType::ChangeTerrainVisibility>::TileVisiblityChange>::operator()(
    FieldsWriter& out,
    const ReplayEventDetails<ReplayEventType::ChangeTerrainVisibility>::TileVisiblityChange& change) const
  {
    out.writeField("coordinates", change.coordinates);
    out.writeField("visibility_old", change.visibility_old);
    out.writeField("visibility_new", change.visibility_new);
  }

  template<ReplayEventType T>
  void JsonObjectWriter<ReplayEventDetails<T>>::operator()(FieldsWriter& out,
                                                           const ReplayEventDetails<T>& details) const
  {
    using Fields = h3json::FieldNames<ReplayEventDetails<T>>;
    JsonObjectWriter<ReplayEventDetailsBase>{}(out, details);
    if constexpr (T == ReplayEventType::MoveHero)
    {
      out.writeField(Fields::kHero, details.hero);
      out.writeField(Fields::kDirection, details.direction);
      out.writeField(Fields::kFrom, details.from);
      out.writeField(Fields::kTo, details.to);
    }
    else if constexpr (T == ReplayEventType::TeleportHero)
    {
      out.writeField(Fields::kHero, details.hero);
      out.writeField(Fields::kOrientation, details.orientation);
      out.writeField(Fields::kFrom, details.from);
      out.writeField(Fields::kTo, details.to);
    }
    else if constexpr (T == ReplayEventType::FlagMine)
    {
      out.writeField(Fields::kId, details.id);
      out.writeField(Fields::kOwnerOld, details.owner_old);
      out.writeField(Fields::kOwnerNew, details.owner_new);
    }
    else if constexpr (T == ReplayEventType::CaptureTown)
    {
      out.writeField(Fields::kTownId, details.town_id);
      out.writeField(Fields::kOwnerOld, details.owner_old);
      out.writeField(Fields::kOwnerNew, details.owner_new);
    }
    else if constexpr (T == ReplayEventType::HideBoat)
    {
      out.writeField(Fields::kBoatId, details.boat_id);
      out.writeField(Fields::kUnknown, details.unknown);
      out.writeField(Fields::kOwnerOld, details.owner_old);
      out.writeField(Fields::kOwnerNew, details.owner_new);
    }
    else if constexpr (T == ReplayEventType::ShowBoat)
    {
      out.writeField(Fields::kUnknown, details.unknown);
      out.writeField(Fields::kCoordinatesNew, details.coordinates_new);
      out.writeField(Fields::kCoordinatesOld, details.coordinates_old);
    }
    else if constexpr (T == ReplayEventType::RemoveMapItem)
    {
      out.writeField(Fields::kCoordinates, details.coordinates);
      out.writeField(Fields::kObjectIdx, details.object_idx);
      out.writeField(Fields::kUnknown, details.unknown);
    }
    else if constexpr (T == ReplayEventType::HideHero)
    {
      out.writeField(Fields::kHero, details.hero);
      out.writeField(Fields::kOwnerNew, details.owner_new);
      out.writeField(Fields::kOwnerOld, details.owner_old);
    }
    else if constexpr (T == ReplayEventType::ShowHero)
    {
      out.writeField(Fields::kHero, details.hero);
      out.writeField(Fields::kOwnerNew, details.owner_new);
      out.writeField(Fields::kOwnerOld, details.owner_old);
      out.writeField(Fields::kCoordinatesNew, details.coordinates_new);
      out.writeField(Fields::kCoordinatesOld, details.coordinates_old);
      out.writeField(Fields::kUnknown, details.unknown);
    }
    else if constexpr (T == ReplayEventType::DefeatPlayer)
    {
      out.writeField(Fields::kUnknown, details.unknown);
    }
    else if constexpr (T == ReplayEventType::ChangeTerrainVisibility)
    {
      out.writeField(Fields::kChanges, details.changes);
    }
    else
    {
      static_assert(false, "Invalid ReplayEventType.");
    }
  }

  template<>
  void JsonObjectWriter<ReplayEvent>::operator()(FieldsWriter& out, const ReplayEvent& replay_event) const
  {
    using Fields = h3json::FieldNames<ReplayEvent>;
    out.writeField(Fields::kType, replay_event.type());
    std::visit([&out] <ReplayEventType T> (const ReplayEventDetails<T>& details)
               {
                 out.writeField(Fields::kDetails, details);
               },
               replay_event.details);
  }
}
