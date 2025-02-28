#include <h3mtxt/H3JsonReader/H3JsonReader.h>
#include <h3mtxt/H3JsonReader/Utils.h>
#include <h3mtxt/JsonCommon/FieldName.h>
#include <h3mtxt/Map/Map.h>

#include <stdexcept>

namespace h3m::H3JsonReader_NS
{
  namespace
  {
    Object readObject(const Json::Value& value, const std::vector<ObjectTemplate>& objects_templates)
    {
      using Fields = FieldNames<Object>;
      Object object;
      readField(object.x, value, Fields::kX);
      readField(object.y, value, Fields::kY);
      readField(object.z, value, Fields::kZ);
      readField(object.template_idx, value, Fields::kTemplateIdx);
      readField(object.unknown, value, Fields::kUnknown);

      const ObjectTemplate& object_template = objects_templates.at(object.template_idx);
      const h3m::MetaObjectType meta_object_type = getMetaObjectType(object_template.object_class);

      if (meta_object_type != h3m::MetaObjectType::GENERIC_NO_PROPERTIES)
      {
        const Json::Value* details_json = value.find(Fields::kDetails.data(),
                                                     Fields::kDetails.data() + Fields::kDetails.size());
        if (!details_json)
        {
          throw MissingJsonFieldError(Fields::kDetails);
        }
        object.details = readObjectDetailsVariant(*details_json, meta_object_type);
      }
      return object;
    }

    void readObjects(std::vector<Object>& objects,
                     const Json::Value& value,
                     const std::vector<ObjectTemplate>& objects_templates)
    {
      if (!value.isArray())
      {
        throw std::runtime_error("readH3mJson(): expected array, got " + value.toStyledString());
      }
      const std::size_t num_elements = value.size();
      objects.reserve(objects.size() + num_elements);
      for (std::size_t i = 0; i < num_elements; ++i)
      {
        const Json::Value& object_details_json = value[static_cast<Json::ArrayIndex>(i)];
        objects.push_back(readObject(object_details_json, objects_templates));
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
    readField(map.objects_templates, value, Fields::kObjectsTemplates);
    {
      const Json::Value* objects_json =
        value.find(Fields::kObjects.data(), Fields::kObjects.data() + Fields::kObjects.size());
      if (!objects_json)
      {
        throw MissingJsonFieldError(Fields::kObjects);
      }
      readObjects(map.objects, *objects_json, map.objects_templates);
    }
    readField(map.global_events, value, Fields::kGlobalEvents);
    readField(map.padding, value, Fields::kPadding);
    return map;
  }
}
