#include <h3mtxt/H3MJsonReader/readH3mJson.h>

#include <h3mtxt/H3MJsonReader/JsonReader.h>
#include <h3mtxt/H3MJsonReader/readPlayerSpecs.h>

#include <istream>
#include <stdexcept>

namespace h3m
{
  template<>
  struct JsonReader<MapBasicInfo>
  {
    MapBasicInfo operator()(const Json::Value& value) const
    {
      MapBasicInfo basic_info{};
      basic_info.is_playable = readField<Bool>(value, "is_playable");
      basic_info.map_size = readField<std::uint32_t>(value, "map_size");
      basic_info.has_two_levels = readField<Bool>(value, "has_two_levels");
      basic_info.name = readField<std::string>(value, "name");
      basic_info.description = readField<std::string>(value, "description");
      basic_info.difficulty = readField<MapDifficulty>(value, "difficulty");
      basic_info.max_hero_level = readField<std::uint8_t>(value, "max_hero_level");
      return basic_info;
    }
  };

  template<>
  struct JsonReader<Tile>
  {
    Tile operator()(const Json::Value& value) const
    {
      Tile tile {};
      tile.terrain_type = readField<TerrainType>(value, "terrain_type");
      tile.terrain_sprite = readField<std::uint8_t>(value, "terrain_sprite");
      tile.river_type = readField<RiverType>(value, "river_type");
      tile.river_sprite = readField<std::uint8_t>(value, "river_sprite");
      tile.road_type = readField<RoadType>(value, "road_type");
      tile.road_sprite = readField<std::uint8_t>(value, "road_sprite");
      tile.mirroring = readField<std::uint8_t>(value, "mirroring");
      return tile;
    }
  };

  template<>
  struct JsonReader<Map>
  {
    Map operator()(const Json::Value& value) const
    {
      Map map;
      map.format = readField<MapFormat>(value, "format");
      map.basic_info = readField<MapBasicInfo>(value, "basic_info");
      map.players = readField<std::array<PlayerSpecs, kMaxPlayers>>(value, "players");
      map.tiles = readField<std::vector<Tile>>(value, "tiles");
      // TODO: read the rest of the fields.
      return map;
    }
  };

  Map readH3mJson(std::istream& stream)
  {
    Json::Value root;
    {
      Json::CharReaderBuilder builder;
      builder["collectComments"] = false;
      Json::String errs;
      if (!parseFromStream(builder, stream, &root, &errs))
      {
        throw std::runtime_error("readH3mJson(): " + errs);
      }
    }
    return fromJson<Map>(root);
  }
}
