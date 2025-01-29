#pragma once

#include <h3mtxt/Map/SecondarySkill.h>
#include <h3mtxt/H3MTxtWriter/H3MTxtWriter.h>

namespace Util_NS
{
  template<>
  struct JsonObjectWriter<h3m::SecondarySkill>
  {
    void operator()(FieldsWriter& out, const h3m::SecondarySkill& value) const
    {
      out.writeField("type", value.type);
      out.writeField("level", value.level);
    }
  };
}
