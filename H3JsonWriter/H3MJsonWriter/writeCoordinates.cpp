#include <h3mtxt/H3JsonWriter/H3MJsonWriter/H3MJsonWriter.h>

#include <h3mtxt/JsonCommon/FieldName.h>
#include <h3mtxt/Map/Coordinates.h>
#include <h3mtxt/Medea/Medea.h>

namespace Medea_NS
{
  void JsonObjectWriter<h3m::Coordinates>::operator()(FieldsWriter& out, const h3m::Coordinates& coordinates) const
  {
    using Fields = h3m::FieldNames<h3m::Coordinates>;
    out.writeField(Fields::kX, coordinates.x);
    out.writeField(Fields::kY, coordinates.y);
    out.writeField(Fields::kZ, coordinates.z);
  }
}
