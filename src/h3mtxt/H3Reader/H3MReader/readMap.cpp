#include <h3mtxt/H3Reader/H3MReader/H3MReader.h>
#include <h3mtxt/Map/Map.h>

namespace h3m
{
  MapBasicInfo H3MReader::readMapBasicInfo() const
  {
    MapBasicInfo basic_info;
    basic_info.is_playable = readBool();
    basic_info.map_size = readInt<std::uint32_t>();
    basic_info.has_two_levels = readBool();
    basic_info.name = readString32();
    basic_info.description = readString32();
    basic_info.difficulty = readEnum<MapDifficulty>();
    basic_info.max_hero_level = readInt<std::uint8_t>();
    return basic_info;
  }

  Tile H3MReader::readTile() const
  {
    Tile tile;
    tile.terrain_type = readEnum<TerrainType>();
    tile.terrain_sprite = readInt<std::uint8_t>();
    tile.river_type = readEnum<RiverType>();
    tile.river_sprite = readInt<std::uint8_t>();
    tile.road_type = readEnum<RoadType>();
    tile.road_sprite = readInt<std::uint8_t>();
    tile.flags = readEnumBitmask<TileFlag, 1>();
    return tile;
  }

  SpriteTilesBitmask H3MReader::readSpriteTilesBitmask() const
  {
    return SpriteTilesBitmask{ .data = readByteArray<6>() };
  }

  ObjectTemplate H3MReader::readObjectTemplate() const
  {
    ObjectTemplate result;
    result.def = readString32();
    result.passability = readSpriteTilesBitmask();
    result.actionability = readSpriteTilesBitmask();
    result.allowed_landscapes = readEnumBitmask<TerrainType, 2>();
    result.landscape_group = readEnumBitmask<TerrainType, 2>();
    result.object_class = readEnum<ObjectClass>();
    result.object_subclass = readInt<std::uint32_t>();
    result.object_group = readEnum<ObjectGroup>();
    result.is_ground = readBool();
    result.unknown = readReservedData<16>();
    return result;
  }

  Map H3MReader::readMap() const
  {
    Map map;
    map.format = readEnum<MapFormat>();
    if (map.format != MapFormat::ShadowOfDeath)
    {
      throw std::runtime_error("Unsupported MapFormat. Only ShadowOfDeath is supported.");
    }
    map.basic_info = readMapBasicInfo();
    for (int i = 0; i < kMaxPlayers; ++i)
    {
      map.players.data[i] = readPlayerSpecs();
    }
    map.additional_info = readMapAdditionalInfo();
    // Read tiles.
    const std::size_t num_tiles = countTiles(map.basic_info);
    map.tiles.reserve(num_tiles);
    for (std::size_t i = 0; i < num_tiles; ++i)
    {
      map.tiles.push_back(readTile());
    }
    // Read objects' templates.
    const std::uint32_t num_objects_templates = readInt<std::uint32_t>();
    map.objects_templates.reserve(num_objects_templates);
    for (std::uint32_t i = 0; i < num_objects_templates; ++i)
    {
      map.objects_templates.push_back(readObjectTemplate());
    }
    // Read objects' details.
    const std::uint32_t num_objects = readInt<std::uint32_t>();
    map.objects.reserve(num_objects);
    for (std::uint32_t i = 0; i < num_objects; ++i)
    {
      map.objects.push_back(readObject(map.objects_templates.data(), map.objects_templates.size()));
    }
    // Read global events.
    const std::uint32_t num_global_events = readInt<std::uint32_t>();
    map.global_events.reserve(num_global_events);
    for (std::uint32_t i = 0; i < num_global_events; ++i)
    {
      map.global_events.push_back(readTimedEvent());
    }
    // Read padding data.
    map.padding = readReservedData<124>();
    return map;
  }
}
