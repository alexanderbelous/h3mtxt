#pragma once

#include <h3mtxt/JsonCommon/FieldName.h>
#include <h3mtxt/Map/PrimarySkills.h>
#include <h3mtxt/H3MJsonWriter/H3MJsonWriter.h>

namespace Medea_NS
{
  template<>
  struct JsonObjectWriter<h3m::PrimarySkills>
  {
    void operator()(FieldsWriter& out, const h3m::PrimarySkills& value) const
    {
      using Fields = h3m::FieldNames<h3m::PrimarySkills>;
      out.writeField(Fields::kAttack, value.attack);
      out.writeField(Fields::kDefense, value.defense);
      out.writeField(Fields::kSpellPower, value.spell_power);
      out.writeField(Fields::kKnowledge, value.knowledge);
    }
  };
}
