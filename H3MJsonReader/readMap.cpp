#include <h3mtxt/JsonCommon/FieldName.h>
#include <h3mtxt/H3MJsonReader/H3JsonReader.h>
#include <h3mtxt/H3MJsonReader/Utils.h>
#include <h3mtxt/Map/Map.h>

#include <stdexcept>

namespace h3m
{
  namespace
  {
    ObjectDetails readObjectDetails(const Json::Value& value,
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

      if (meta_object_type != h3m::MetaObjectType::GENERIC_NO_PROPERTIES)
      {
        const Json::Value* details_json = value.find(Fields::kDetails.data(),
                                                     Fields::kDetails.data() + Fields::kDetails.size());
        if (!details_json)
        {
          throw MissingJsonFieldError(Fields::kDetails);
        }
        object_details.details = H3MJsonReader_NS::readObjectDetailsDataVariant(*details_json, meta_object_type);
      }
      return object_details;
    }

    void readObjectsDetails(std::vector<ObjectDetails>& objects_details,
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
        objects_details.push_back(readObjectDetails(object_details_json, objects_attributes));
      }
    }
  }

  Map JsonReader<Map>::operator()(const Json::Value& value) const
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
}
