#pragma once

#include <h3mtxt/Map/ObjectAttributes.h>
#include <h3mtxt/H3MTxtWriter/H3MTxtWriter.h>
#include <h3mtxt/H3MTxtWriter/getEnumString.h>

namespace Util_NS
{
  template<>
  struct StructWriter<h3m::ObjectAttributes>
  {
    void operator()(FieldsWriter& out, const h3m::ObjectAttributes& value) const
    {
      out.writeField("def", value.def);
      out.writeField("passability", value.passability);
      out.writeField("actionability", value.actionability);
      out.writeField("allowed_landscapes", value.allowed_landscapes);
      out.writeField("landscape_group", value.landscape_group);
      out.writeField("object_class", value.object_class);
      const std::string_view object_class_name = h3m::getEnumString(value.object_class);
      if (!object_class_name.empty())
      {
        out.writeComma();
        out.writeComment(object_class_name, false);
      }
      out.writeField("object_number", value.object_number);
      out.writeField("object_group", value.object_group);
      out.writeField("is_ground", value.is_ground);
      out.writeField("unknown", value.unknown);
    }
  };
}
