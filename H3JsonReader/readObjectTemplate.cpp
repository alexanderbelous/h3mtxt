#include <h3mtxt/H3JsonReader/Utils.h>
#include <h3mtxt/JsonCommon/FieldName.h>
#include <h3mtxt/Map/ObjectTemplate.h>

namespace h3m::H3JsonReader_NS
{
  ObjectTemplate JsonReader<ObjectTemplate>::operator()(const Json::Value& value) const
  {
    using Fields = FieldNames<ObjectTemplate>;
    ObjectTemplate object_template{};
    readField(object_template.def, value, Fields::kDef);
    readField(object_template.passability, value, Fields::kPassability);
    readField(object_template.actionability, value, Fields::kActionability);
    readField(object_template.allowed_landscapes, value, Fields::kAllowedLandscapes);
    readField(object_template.landscape_group, value, Fields::kLandscapeGroup);
    readField(object_template.object_class, value, Fields::kObjectClass);
    readField(object_template.object_subclass, value, Fields::kObjectSubclass);
    readField(object_template.object_group, value, Fields::kObjectGroup);
    readField(object_template.is_ground, value, Fields::kIsGround);
    readField(object_template.unknown, value, Fields::kUnknown);
    return object_template;
  }
}
