#pragma once

#include <h3mtxt/Map/SecondarySkill.h>
#include <h3mtxt/H3MTxtWriter/getEnumString.h>
#include <h3mtxt/H3MTxtWriter/H3MTxtWriter.h>

namespace Util_NS
{
  template<>
  struct JsonObjectWriter<h3m::SecondarySkill>
  {
    void operator()(FieldsWriter& out, const h3m::SecondarySkill& skill) const
    {
      out.writeField("type", skill.type);
      if (auto enum_str = h3m::getEnumString(skill.type); !enum_str.empty())
      {
        out.writeComma();
        out.writeComment(enum_str, false);
      }
      out.writeField("level", skill.level);
    }
  };
}
