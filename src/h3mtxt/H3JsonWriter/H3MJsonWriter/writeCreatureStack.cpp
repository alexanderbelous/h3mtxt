#include <h3mtxt/H3JsonWriter/H3MJsonWriter/H3MJsonWriter.h>

#include <h3mtxt/JsonCommon/FieldNamesH3M.h>
#include <h3mtxt/Map/CreatureStack.h>
#include <h3mtxt/Medea/Medea.h>

namespace Medea_NS
{
  void JsonObjectWriter<h3m::CreatureStack>::operator()(FieldsWriter& out, const h3m::CreatureStack& creature_stack) const
  {
    using Fields = h3json::FieldNames<h3m::CreatureStack>;
    out.writeField(Fields::kType, creature_stack.type);
    out.writeField(Fields::kCount, creature_stack.count);
  }
}
