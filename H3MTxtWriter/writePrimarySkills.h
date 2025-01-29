#pragma once

#include <h3mtxt/Map/PrimarySkills.h>
#include <h3mtxt/H3MTxtWriter/H3MTxtWriter.h>

namespace Util_NS
{
  template<>
  struct JsonObjectWriter<h3m::PrimarySkills>
  {
    void operator()(FieldsWriter& out, const h3m::PrimarySkills& value) const
    {
      out.writeField("attack", value.attack);
      out.writeField("defense", value.defense);
      out.writeField("spell_power", value.spell_power);
      out.writeField("knowledge", value.knowledge);
    }
  };
}
