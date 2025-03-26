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
      const h3m::MetaObjectType meta_object_type = getMetaObjectType(object_template.object_class,
                                                                     object_template.object_subclass);
      if (meta_object_type != h3m::MetaObjectType::GENERIC_NO_PROPERTIES)
      {
        const Json::Value& properties_json = getJsonField(value, Fields::kProperties);
        object.properties = readObjectPropertiesVariant(properties_json, meta_object_type);
      }
      return object;
    }

    std::vector<Object> readObjects(const Json::Value& value, const std::vector<ObjectTemplate>& objects_templates)
    {
      if (!value.isArray())
      {
        throw std::runtime_error("readH3mJson(): expected array, got " + value.toStyledString());
      }
      const std::size_t num_elements = value.size();
      std::vector<Object> objects;
      objects.reserve(num_elements);
      for (std::size_t i = 0; i < num_elements; ++i)
      {
        const Json::Value& object_json = value[static_cast<Json::ArrayIndex>(i)];
        objects.push_back(readObject(object_json, objects_templates));
      }
      return objects;
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
    map.objects = readObjects(getJsonField(value, Fields::kObjects), map.objects_templates);
    readField(map.global_events, value, Fields::kGlobalEvents);
    readField(map.padding, value, Fields::kPadding);
    return map;
  }
}
