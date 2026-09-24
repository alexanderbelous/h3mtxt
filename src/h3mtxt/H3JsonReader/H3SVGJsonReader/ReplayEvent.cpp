#include <h3mtxt/H3JsonReader/H3SVGJsonReader/H3SVGJsonReader.h>

#include <h3mtxt/H3JsonReader/H3JsonReaderBase/H3JsonReaderBase.h>
#include <h3mtxt/H3JsonReader/H3JsonReaderBase/VariantJsonReader.h>
#include <h3mtxt/JsonCommon/FieldNamesH3SVG.h>
#include <h3mtxt/SavedGame/Replay.h>

namespace h3json
{
  // TODO: unnest TileVisiblityChange and add a declaration for this template specialization
  // to H3SVGJsonReader.h.
  template<>
  h3svg::ReplayEventDetails<h3svg::ReplayEventType::ChangeTerrainVisibility>::TileVisiblityChange
  JsonReader<h3svg::ReplayEventDetails<h3svg::ReplayEventType::ChangeTerrainVisibility>::TileVisiblityChange>::operator()(
    const Json::Value& value) const
  {
    h3svg::ReplayEventDetails<h3svg::ReplayEventType::ChangeTerrainVisibility>::TileVisiblityChange change;
    readField(change.coordinates, value, "coordinates");
    readField(change.visibility_old, value, "visibility_old");
    readField(change.visibility_new, value, "visibility_new");
    return change;
  }

  // This template is implicitly instantiated for all valid ReplayEventType
  // in JsonReader<h3svg::ReplayEvent>::operator().
  template<h3svg::ReplayEventType T>
  h3svg::ReplayEventDetails<T>
  JsonReader<h3svg::ReplayEventDetails<T>>::operator()(const Json::Value& value) const
  {
    using Fields = h3json::FieldNames<h3svg::ReplayEventDetails<T>>;
    h3svg::ReplayEventDetails<T> details;
    if constexpr (T == h3svg::ReplayEventType::MoveHero)
    {
      readField(details.player, value, Fields::kPlayer);
      readField(details.hero, value, Fields::kHero);
      readField(details.direction, value, Fields::kDirection);
      readField(details.from, value, Fields::kFrom);
      readField(details.to, value, Fields::kTo);
    }
    else if constexpr (T == h3svg::ReplayEventType::TeleportHero)
    {
      readField(details.player, value, Fields::kPlayer);
      readField(details.hero, value, Fields::kHero);
      readField(details.orientation, value, Fields::kOrientation);
      readField(details.from, value, Fields::kFrom);
      readField(details.to, value, Fields::kTo);
    }
    else if constexpr (T == h3svg::ReplayEventType::FlagMine)
    {
      readField(details.player, value, Fields::kPlayer);
      readField(details.id, value, Fields::kId);
      readField(details.owner_old, value, Fields::kOwnerOld);
      readField(details.owner_new, value, Fields::kOwnerNew);
    }
    else if constexpr (T == h3svg::ReplayEventType::CaptureTown)
    {
      readField(details.player, value, Fields::kPlayer);
      readField(details.town_id, value, Fields::kTownId);
      readField(details.owner_old, value, Fields::kOwnerOld);
      readField(details.owner_new, value, Fields::kOwnerNew);
    }
    else if constexpr (T == h3svg::ReplayEventType::HideBoat)
    {
      readField(details.player, value, Fields::kPlayer);
      readField(details.boat_id, value, Fields::kBoatId);
      readField(details.unknown, value, Fields::kUnknown);
      readField(details.owner_old, value, Fields::kOwnerOld);
      readField(details.owner_new, value, Fields::kOwnerNew);
    }
    else if constexpr (T == h3svg::ReplayEventType::ShowBoat)
    {
      readField(details.player, value, Fields::kPlayer);
      readField(details.unknown, value, Fields::kUnknown);
      readField(details.coordinates_new, value, Fields::kCoordinatesNew);
      readField(details.coordinates_old, value, Fields::kCoordinatesOld);
    }
    else if constexpr (T == h3svg::ReplayEventType::RemoveMapItem)
    {
      readField(details.player, value, Fields::kPlayer);
      readField(details.coordinates, value, Fields::kCoordinates);
      readField(details.unknown, value, Fields::kUnknown);
    }
    else if constexpr (T == h3svg::ReplayEventType::HideHero)
    {
      readField(details.player, value, Fields::kPlayer);
      readField(details.hero, value, Fields::kHero);
      readField(details.owner_new, value, Fields::kOwnerNew);
      readField(details.owner_old, value, Fields::kOwnerOld);
    }
    else if constexpr (T == h3svg::ReplayEventType::ShowHero)
    {
      readField(details.player, value, Fields::kPlayer);
      readField(details.hero, value, Fields::kHero);
      readField(details.owner_new, value, Fields::kOwnerNew);
      readField(details.owner_old, value, Fields::kOwnerOld);
      readField(details.coordinates_new, value, Fields::kCoordinatesNew);
      readField(details.coordinates_old, value, Fields::kCoordinatesOld);
      readField(details.unknown, value, Fields::kUnknown);
    }
    else if constexpr (T == h3svg::ReplayEventType::ChangeTerrainVisibility)
    {
      readField(details.player, value, Fields::kPlayer);
      readField(details.changes, value, Fields::kChanges);
    }
    else
    {
      static_assert(false, "Invalid ReplayEventType.");
    }
    return details;
  }

  template<>
  h3svg::ReplayEvent JsonReader<h3svg::ReplayEvent>::operator()(const Json::Value& value) const
  {
    using Fields = h3json::FieldNames<h3svg::ReplayEvent>;
    const h3svg::ReplayEventType event_type = readField<h3svg::ReplayEventType>(value, Fields::kType);
    return h3svg::ReplayEvent{
      .details = VariantJsonReader<h3svg::ReplayEvent::Details>{}(getJsonField(value, Fields::kDetails),
                                                                  h3svg::ReplayEvent::getAlternativeIdx(event_type))
    };
  }
}
