#pragma once

#include <h3mtxt/Map/MapBasicInfo.h>
#include <h3mtxt/H3MTxtWriter/H3MTxtWriter.h>

namespace Util_NS
{
  template<>
  struct StructWriter<h3m::MapBasicInfo>
  {
    void operator()(FieldsWriter& out, const h3m::MapBasicInfo& value) const
    {
      out.writeField("is_playable", value.is_playable);
      out.writeField("map_size", value.map_size);
      out.writeField("has_two_levels", value.has_two_levels);
      out.writeField("name", value.name);
      out.writeField("description", value.description);
      out.writeField("difficulty", value.difficulty);
      out.writeField("max_hero_level", value.max_hero_level);
    }
  };
}
