#pragma once

#include <h3mtxt/H3MJsonReader/JsonReader.h>
#include <h3mtxt/JsonCommon/FieldName.h>
#include <h3mtxt/Map/ObjectAttributes.h>

namespace h3m
{
  template<>
  struct JsonReader<ObjectAttributes>
  {
    ObjectAttributes operator()(const Json::Value& value) const
    {
      using Fields = FieldNames<ObjectAttributes>;
      ObjectAttributes object_attributes{};
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
}
