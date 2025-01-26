#pragma once

#include <h3mtxt/Map/ObjectAttributes.h>
#include <h3mtxt/H3MTxtWriter/H3MTxtWriter.h>

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
      out.writeField("object_number", value.object_number);
      out.writeField("object_group", value.object_group);
      out.writeField("is_ground", value.is_ground);
      out.writeField("unknown", value.unknown);
    }
  };
}
