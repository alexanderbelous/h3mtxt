#include <h3mtxt/H3MJsonReader/readH3mJson.h>

#include <h3mtxt/JsonCommon/FieldName.h>
#include <h3mtxt/H3MJsonReader/JsonReader.h>
#include <h3mtxt/H3MJsonReader/readMapAdditionalInfo.h>
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
      using Fields = FieldNames<MapBasicInfo>;
      MapBasicInfo basic_info{};
      readField(basic_info.is_playable, value, Fields::kIsPlayable);
      readField(basic_info.map_size, value, Fields::kMapSize);
      readField(basic_info.has_two_levels, value, Fields::kHasTwoLevels);
      readField(basic_info.name, value, Fields::kName);
      readField(basic_info.description, value, Fields::kDescription);
      readField(basic_info.difficulty, value, Fields::kDifficulty);
      readField(basic_info.max_hero_level, value, Fields::kMaxHeroLevel);
      return basic_info;
    }
  };

  template<>
  struct JsonReader<Tile>
  {
    Tile operator()(const Json::Value& value) const
    {
      using Fields = FieldNames<Tile>;
      Tile tile {};
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

  template<>
  struct JsonReader<ObjectAttributes>
  {
    ObjectAttributes operator()(const Json::Value& value) const
    {
      ObjectAttributes object_attributes {};
      object_attributes.def = readField<std::string>(value, "def");
      object_attributes.passability = readField<std::array<std::uint8_t, 6>>(value, "passability");
      object_attributes.actionability = readField<std::array<std::uint8_t, 6>>(value, "actionability");
      object_attributes.allowed_landscapes = readField<std::uint16_t>(value, "allowed_landscapes");
      object_attributes.landscape_group = readField<std::uint16_t>(value, "landscape_group");
      object_attributes.object_class = readField<ObjectClass>(value, "object_class");
      object_attributes.object_number = readField<std::uint32_t>(value, "object_number");
      object_attributes.object_group = readField<ObjectGroup>(value, "object_group");
      object_attributes.is_ground = readField<Bool>(value, "is_ground");
      object_attributes.unknown = readField<ReservedData<16>>(value, "unknown");
      return object_attributes;
    }
  };

  template<>
  struct JsonReader<Map>
  {
    Map operator()(const Json::Value& value) const
    {
      using Fields = FieldNames<Map>;

      Map map;
      readField(map.format, value, Fields::kFormat);
      readField(map.basic_info, value, Fields::kBasicInfo);
      readField(map.players, value, Fields::kPlayers);
      readField(map.additional_info, value, Fields::kAdditionalInfo);
      readField(map.tiles, value, Fields::kTiles);
      readField(map.objects_attributes, value, Fields::kObjectsAttributes);
      readField(map.padding, value, Fields::kPadding);
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
