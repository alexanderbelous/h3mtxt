#pragma once

#include <h3mtxt/H3MJsonReader/JsonReader.h>
#include <h3mtxt/JsonCommon/FieldName.h>
#include <h3mtxt/Map/Tile.h>

namespace h3m
{
  template<>
  struct JsonReader<Tile>
  {
    Tile operator()(const Json::Value& value) const
    {
      using Fields = FieldNames<Tile>;
      Tile tile{};
      readField(tile.terrain_type, value, Fields::kTerrainType);
      readField(tile.terrain_sprite, value, Fields::kTerrainSprite);
      readField(tile.river_type, value, Fields::kRiverType);
      readField(tile.river_sprite, value, Fields::kRiverSprite);
      readField(tile.road_type, value, Fields::kRoadType);
      readField(tile.road_sprite, value, Fields::kRoadSprite);
      readField(tile.mirroring, value, Fields::kMirroring);
      return tile;
    }
  };
}
