#include <h3mtxt/H3JsonReader/H3MJsonReader/H3MJsonReader.h>

#include <h3mtxt/H3JsonReader/H3JsonReaderBase/H3JsonReaderBase.h>
#include <h3mtxt/JsonCommon/FieldNamesH3M.h>
#include <h3mtxt/Map/Tile.h>

namespace h3json
{
  template<>
  h3m::Tile JsonReader2<h3m::Tile>::operator()() const
  {
    using Fields = FieldNames<h3m::Tile>;
    h3m::Tile tile;
    readField(Fields::kTerrainType, tile.terrain_type);
    readField(Fields::kTerrainSprite, tile.terrain_sprite);
    readField(Fields::kRiverType, tile.river_type);
    readField(Fields::kRiverSprite, tile.river_sprite);
    readField(Fields::kRoadType, tile.road_type);
    readField(Fields::kRoadSprite, tile.road_sprite);
    readField(Fields::kFlags, tile.flags);
    return tile;
  }
}
