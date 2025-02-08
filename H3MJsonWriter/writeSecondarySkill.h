#pragma once

#include <h3mtxt/JsonCommon/FieldName.h>
#include <h3mtxt/Map/SecondarySkill.h>
#include <h3mtxt/H3MJsonWriter/getEnumString.h>
#include <h3mtxt/H3MJsonWriter/H3MJsonWriter.h>

namespace Util_NS
{
  template<>
  struct JsonObjectWriter<h3m::SecondarySkill>
  {
    void operator()(FieldsWriter& out, const h3m::SecondarySkill& skill) const
    {
      using Fields = h3m::FieldNames<h3m::SecondarySkill>;
      out.writeField(Fields::kType, skill.type);
      if (auto enum_str = h3m::getEnumString(skill.type); !enum_str.empty())
      {
        out.writeComma();
        out.writeComment(enum_str, false);
      }
      out.writeField(Fields::kLevel, skill.level);
    }
  };
}
