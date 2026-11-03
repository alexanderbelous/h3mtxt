#include <h3mtxt/H3JsonReader/H3SVGJsonReader/H3SVGJsonReader.h>

#include <h3mtxt/H3JsonReader/H3JsonReaderBase/H3JsonReaderBase.h>
#include <h3mtxt/H3JsonReader/H3JsonReaderBase/VariantJsonReader.h>
#include <h3mtxt/JsonCommon/FieldNamesH3SVG.h>
#include <h3mtxt/SavedGame/ReplayEvent.h>

using ::h3svg::ReplayEvent;
using ::h3svg::ReplayEventDetails;
using ::h3svg::ReplayEventDetailsBase;
using ::h3svg::ReplayEventType;

namespace h3json
{
  // TODO: unnest TileVisiblityChange and add a declaration for this template specialization
  // to H3SVGJsonReader.h.
  template<>
  ReplayEventDetails<ReplayEventType::ChangeTerrainVisibility>::TileVisiblityChange
  JsonReader2<ReplayEventDetails<ReplayEventType::ChangeTerrainVisibility>::TileVisiblityChange>::operator()() const
  {
    ReplayEventDetails<ReplayEventType::ChangeTerrainVisibility>::TileVisiblityChange change;
    readField("coordinates", change.coordinates);
    readField("visibility_old", change.visibility_old);
    readField("visibility_new", change.visibility_new);
    return change;
  }

  template<ReplayEventType T>
  ReplayEventDetails<T> JsonReader2<ReplayEventDetails<T>>::operator()() const
  {
    using Fields = FieldNames<ReplayEventDetails<T>>;
    ReplayEventDetails<T> details{ fromJson<ReplayEventDetailsBase>(value()) };
    if constexpr (T == ReplayEventType::MoveHero)
    {
      readField(Fields::kHero, details.hero);
      readField(Fields::kDirection, details.direction);
      readField(Fields::kFrom, details.from);
      readField(Fields::kTo, details.to);
    }
    else if constexpr (T == ReplayEventType::TeleportHero)
    {
      readField(Fields::kHero, details.hero);
      readField(Fields::kOrientation, details.orientation);
      readField(Fields::kFrom, details.from);
      readField(Fields::kTo, details.to);
    }
    else if constexpr (T == ReplayEventType::FlagMine)
    {
      readField(Fields::kId, details.id);
      readField(Fields::kOwnerOld, details.owner_old);
      readField(Fields::kOwnerNew, details.owner_new);
    }
    else if constexpr (T == ReplayEventType::CaptureTown)
    {
      readField(Fields::kTownId, details.town_id);
      readField(Fields::kOwnerOld, details.owner_old);
      readField(Fields::kOwnerNew, details.owner_new);
    }
    else if constexpr (T == ReplayEventType::HideBoat)
    {
      readField(Fields::kBoatId, details.boat_id);
      readField(Fields::kUnknown, details.unknown);
      readField(Fields::kOwnerOld, details.owner_old);
      readField(Fields::kOwnerNew, details.owner_new);
    }
    else if constexpr (T == ReplayEventType::ShowBoat)
    {
      readField(Fields::kUnknown, details.unknown);
      readField(Fields::kCoordinatesNew, details.coordinates_new);
      readField(Fields::kCoordinatesOld, details.coordinates_old);
    }
    else if constexpr (T == ReplayEventType::RemoveMapItem)
    {
      readField(Fields::kCoordinates, details.coordinates);
      readField(Fields::kObjectIdx, details.object_idx);
      readField(Fields::kUnknown, details.unknown);
    }
    else if constexpr (T == ReplayEventType::HideHero)
    {
      readField(Fields::kHero, details.hero);
      readField(Fields::kOwnerNew, details.owner_new);
      readField(Fields::kOwnerOld, details.owner_old);
    }
    else if constexpr (T == ReplayEventType::ShowHero)
    {
      readField(Fields::kHero, details.hero);
      readField(Fields::kOwnerNew, details.owner_new);
      readField(Fields::kOwnerOld, details.owner_old);
      readField(Fields::kCoordinatesNew, details.coordinates_new);
      readField(Fields::kCoordinatesOld, details.coordinates_old);
      readField(Fields::kUnknown, details.unknown);
    }
    else if constexpr (T == ReplayEventType::DefeatPlayer)
    {
      readField(Fields::kUnknown, details.unknown);
    }
    else if constexpr (T == ReplayEventType::ChangeTerrainVisibility)
    {
      readField(Fields::kChanges, details.changes);
    }
    else
    {
      static_assert(false, "Invalid ReplayEventType.");
    }
    return details;
  }

  template<>
  ReplayEventDetailsBase JsonReader2<ReplayEventDetailsBase>::operator()() const
  {
    using Fields = FieldNames<ReplayEventDetailsBase>;
    ReplayEventDetailsBase base;
    readField(Fields::kPlayer, base.player);
    return base;
  }

  template<>
  ReplayEvent JsonReader2<ReplayEvent>::operator()() const
  {
    using Fields = FieldNames<ReplayEvent>;
    const ReplayEventType event_type = readField<ReplayEventType>(Fields::kType);
    return ReplayEvent{
      .details = VariantJsonReader<ReplayEvent::Details>{}(getField(Fields::kDetails),
                                                           ReplayEvent::getAlternativeIdx(event_type))
    };
  }
}
