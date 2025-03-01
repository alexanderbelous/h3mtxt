#include <h3mtxt/H3JsonWriter/H3JsonWriter.h>
#include <h3mtxt/H3JsonWriter/getEnumString.h>
#include <h3mtxt/H3JsonWriter/Utils.h>
#include <h3mtxt/JsonCommon/FieldName.h>
#include <h3mtxt/Map/CreatureStack.h>

namespace Medea_NS
{
  void JsonObjectWriter<h3m::CreatureStack>::operator()(FieldsWriter& out, const h3m::CreatureStack& creature_stack) const
  {
    using Fields = h3m::FieldNames<h3m::CreatureStack>;
    out.writeField(Fields::kType, creature_stack.type);
    if (auto enum_str = h3m::getEnumString(creature_stack.type); !enum_str.empty())
    {
      out.writeComma();
      out.writeComment(enum_str, false);
    }
    out.writeField(Fields::kCount, creature_stack.count);
  }
}
