#include <h3mtxt/H3MJsonReader/readH3mJson.h>

#include <h3mtxt/JsonCommon/FieldName.h>
#include <h3mtxt/H3MJsonReader/JsonReader.h>
#include <h3mtxt/H3MJsonReader/readGlobalEvent.h>
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
      using Fields = FieldNames<ObjectAttributes>;
      ObjectAttributes object_attributes {};
      readField(object_attributes.def, value, Fields::kDef);
      readField(object_attributes.passability, value, Fields::kPassability);
      readField(object_attributes.actionability, value, Fields::kActionability);
      readField(object_attributes.allowed_landscapes, value, Fields::kAllowedLandscapes);
      readField(object_attributes.landscape_group, value, Fields::kLandscapeGroup);
      readField(object_attributes.object_class, value, Fields::kObjectClass);
      readField(object_attributes.object_number, value, Fields::kObjectNumber);
      readField(object_attributes.object_group, value, Fields::kObjectGroup);
      readField(object_attributes.is_ground, value, Fields::kIsGround);
      readField(object_attributes.unknown, value, Fields::kUnknown);
      return object_attributes;
    }
  };

  // TODO: return as ObjectDetails, not as std::optional.
  static std::optional<ObjectDetails> tryReadObjectDetails(
    const Json::Value& value,
    const std::vector<ObjectAttributes>& objects_attributes)
  {
    using Fields = FieldNames<ObjectDetails>;
    ObjectDetails object_details;
    readField(object_details.x, value, Fields::kX);
    readField(object_details.y, value, Fields::kY);
    readField(object_details.z, value, Fields::kZ);
    readField(object_details.kind, value, Fields::kKind);
    readField(object_details.unknown, value, Fields::kUnknown);

    const ObjectAttributes& object_attributes = objects_attributes.at(object_details.kind);
    const h3m::MetaObjectType meta_object_type = getMetaObjectType(object_attributes.object_class);
    if (meta_object_type == h3m::MetaObjectType::GENERIC_NO_PROPERTIES)
    {
      return object_details;
    }
    // TODO: read details.
    return std::nullopt;
  }

  static void readObjectsDetails(std::vector<ObjectDetails>& objects_details,
                                 const Json::Value& value,
                                 const std::vector<ObjectAttributes>& objects_attributes)
  {
    if (!value.isArray())
    {
      throw std::runtime_error("readH3mJson(): expected array, got " + value.toStyledString());
    }
    const std::size_t num_elements = value.size();
    objects_details.reserve(objects_details.size() + num_elements);
    for (std::size_t i = 0; i < num_elements; ++i)
    {
      const Json::Value& object_details_json = value[static_cast<Json::ArrayIndex>(i)];
      std::optional<ObjectDetails> object_details = tryReadObjectDetails(object_details_json, objects_attributes);
      if (object_details)
      {
        objects_details.push_back(std::move(*object_details));
      }
    }
  }

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
      {
        const Json::Value* objects_details_json =
          value.find(Fields::kObjectsDetails.data(), Fields::kObjectsDetails.data() + Fields::kObjectsDetails.size());
        if (!objects_details_json)
        {
          throw MissingJsonFieldError(Fields::kObjectsDetails);
        }
        readObjectsDetails(map.objects_details, *objects_details_json, map.objects_attributes);
      }
      readField(map.global_events, value, Fields::kGlobalEvents);
      readField(map.padding, value, Fields::kPadding);
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
