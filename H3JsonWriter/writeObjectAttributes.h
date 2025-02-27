#pragma once

#include <h3mtxt/JsonCommon/FieldName.h>
#include <h3mtxt/Map/ObjectAttributes.h>
#include <h3mtxt/H3JsonWriter/H3JsonWriter.h>
#include <h3mtxt/H3JsonWriter/getEnumString.h>

namespace Medea_NS
{
  template<>
  struct JsonObjectWriter<h3m::ObjectAttributes>
  {
    void operator()(FieldsWriter& out, const h3m::ObjectAttributes& value) const
    {
      using Fields = h3m::FieldNames<h3m::ObjectAttributes>;
      out.writeField(Fields::kDef, value.def);
      out.writeField(Fields::kPassability, value.passability);
      out.writeField(Fields::kActionability, value.actionability);
      out.writeField(Fields::kAllowedLandscapes, value.allowed_landscapes);
      out.writeField(Fields::kLandscapeGroup, value.landscape_group);
      out.writeField(Fields::kObjectClass, value.object_class);
      if (auto enum_str = h3m::getEnumString(value.object_class); !enum_str.empty())
      {
        out.writeComma();
        out.writeComment(enum_str, false);
      }
      out.writeField(Fields::kObjectNumber, value.object_number);
      out.writeField(Fields::kObjectGroup, value.object_group);
      if (auto enum_str = h3m::getEnumString(value.object_group); !enum_str.empty())
      {
        out.writeComma();
        out.writeComment(enum_str, false);
      }
      out.writeField(Fields::kIsGround, value.is_ground);
      out.writeField(Fields::kUnknown, value.unknown);
    }
  };
}
