#include <h3mtxt/H3JsonWriter/H3JsonWriter.h>
#include <h3mtxt/H3JsonWriter/getEnumString.h>
#include <h3mtxt/H3JsonWriter/Utils.h>
#include <h3mtxt/JsonCommon/FieldName.h>
#include <h3mtxt/Map/HeroArtifacts.h>
#include <h3mtxt/Medea/Medea.h>

namespace Medea_NS
{
  void JsonObjectWriter<h3m::HeroArtifacts>::operator()(FieldsWriter& out, const h3m::HeroArtifacts& value) const
  {
    using Fields = h3m::FieldNames<h3m::HeroArtifacts>;
    out.writeField(Fields::kEquipped, value.equipped);
    out.writeField(Fields::kBackpack, value.backpack);
  }
}
