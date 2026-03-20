#include <h3mtxt/H3JsonReader/H3MJsonReader/H3MJsonReader.h>

#include <h3mtxt/H3JsonReader/H3JsonReaderBase/H3JsonReaderBase.h>
#include <h3mtxt/JsonCommon/FieldNamesH3M.h>
#include <h3mtxt/Map/Tile.h>

namespace h3json
{
  h3m::Tile JsonReader<h3m::Tile>::operator()(const Json::Value& value) const
  {
    using Fields = FieldNames<h3m::Tile>;
    h3m::Tile tile{};
    readField(tile.terrain_type, value, Fields::kTerrainType);
    readField(tile.terrain_sprite, value, Fields::kTerrainSprite);
    readField(tile.river_type, value, Fields::kRiverType);
    readField(tile.river_sprite, value, Fields::kRiverSprite);
    readField(tile.road_type, value, Fields::kRoadType);
    readField(tile.road_sprite, value, Fields::kRoadSprite);
    readField(tile.flags, value, Fields::kFlags);
    return tile;
  }
}
