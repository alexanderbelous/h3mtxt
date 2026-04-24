#include <h3mtxt/H3JsonReader/H3MJsonReader/H3MJsonReader.h>

#include <h3mtxt/H3JsonReader/H3JsonReaderBase/H3JsonReaderBase.h>
#include <h3mtxt/JsonCommon/FieldNamesH3M.h>
#include <h3mtxt/Map/Map.h>

#include <stdexcept>

namespace h3json
{
  namespace
  {
    h3m::Object readObject(const Json::Value& value, const std::vector<h3m::ObjectTemplate>& objects_templates)
    {
      using Fields = FieldNames<h3m::Object>;
      h3m::Object object;
      readField(object.coordinates, value, Fields::kCoordinates);
      readField(object.template_idx, value, Fields::kTemplateIdx);
      readField(object.unknown, value, Fields::kUnknown);

      const h3m::ObjectTemplate& object_template = objects_templates.at(object.template_idx);
      const h3m::ObjectPropertiesType object_properties_type =
        h3m::getObjectPropertiesType(object_template.object_class, object_template.object_subclass);
      if (object_properties_type != h3m::ObjectPropertiesType::NONE)
      {
        const Json::Value& properties_json = getJsonField(value, Fields::kProperties);
        object.properties = readObjectPropertiesVariant(properties_json, object_properties_type);
      }
      return object;
    }

    std::vector<h3m::Object> readObjects(const Json::Value& value,
                                         const std::vector<h3m::ObjectTemplate>& objects_templates)
    {
      if (!value.isArray())
      {
        throw std::runtime_error("readH3mJson(): expected array, got " + value.toStyledString());
      }
      const std::size_t num_elements = value.size();
      std::vector<h3m::Object> objects;
      objects.reserve(num_elements);
      for (std::size_t i = 0; i < num_elements; ++i)
      {
        const Json::Value& object_json = value[static_cast<Json::ArrayIndex>(i)];
        objects.push_back(readObject(object_json, objects_templates));
      }
      return objects;
    }
  }

  h3m::Map JsonReader<h3m::Map>::operator()(const Json::Value& value) const
  {
    using Fields = FieldNames<h3m::Map>;

    h3m::Map map;
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
