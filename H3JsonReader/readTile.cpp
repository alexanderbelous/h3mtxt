#include <h3mtxt/H3JsonReader/Utils.h>
#include <h3mtxt/JsonCommon/FieldName.h>
#include <h3mtxt/Map/Tile.h>

namespace h3m::H3JsonReader_NS
{
  TileFlags JsonReader<TileFlags>::operator()(const Json::Value& value) const
  {
    TileFlags flags;
    flags.bitset.data[0] = fromJson<std::uint8_t>(value);
    return flags;
  }

  Tile JsonReader<Tile>::operator()(const Json::Value& value) const
  {
    using Fields = FieldNames<Tile>;
    Tile tile{};
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
