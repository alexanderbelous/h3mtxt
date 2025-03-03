#include <h3mtxt/H3JsonWriter/H3JsonWriter.h>
#include <h3mtxt/JsonCommon/FieldName.h>
#include <h3mtxt/JsonWriter/JsonValueWriter.h>
#include <h3mtxt/Map/Utils/EnumBitmask.h>

namespace Medea_NS
{
  void JsonObjectWriter<h3m::ArtifactsBitmask>::operator()(FieldsWriter& out,
                                                           const h3m::ArtifactsBitmask& bitmask) const
  {
    using Fields = h3m::FieldNames<h3m::ArtifactsBitmask>;
    for (std::size_t i = 0; i < bitmask.bitset.kNumBits; ++i)
    {
      out.writeField(Fields::kNames[i], bitmask.bitset[i]);
    }
  }
}
