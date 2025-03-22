#include <h3mtxt/H3JsonWriter/H3JsonWriter.h>
#include <h3mtxt/H3JsonWriter/Utils.h>
#include <h3mtxt/JsonCommon/FieldName.h>
#include <h3mtxt/JsonWriter/JsonWriter.h>
#include <h3mtxt/Map/PrimarySkills.h>

namespace Medea_NS
{
  void JsonObjectWriter<h3m::PrimarySkills>::operator()(FieldsWriter& out, const h3m::PrimarySkills& value) const
  {
    using Fields = h3m::FieldNames<h3m::PrimarySkills>;
    out.writeField(Fields::kAttack, value.attack);
    out.writeField(Fields::kDefense, value.defense);
    out.writeField(Fields::kSpellPower, value.spell_power);
    out.writeField(Fields::kKnowledge, value.knowledge);
  }
}
