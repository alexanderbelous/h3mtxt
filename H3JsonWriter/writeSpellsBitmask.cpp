#include <h3mtxt/H3JsonWriter/H3JsonWriter.h>
#include <h3mtxt/JsonCommon/FieldName.h>
#include <h3mtxt/H3JsonWriter/Utils.h>
#include <h3mtxt/Map/Utils/EnumBitmask.h>

namespace Medea_NS
{
  void JsonObjectWriter<h3m::SpellsBitmask>::operator()(FieldsWriter& out, const h3m::SpellsBitmask& bitmask) const
  {
    using Fields = h3m::FieldNames<h3m::SpellsBitmask>;
    static_assert(Fields::kNames.size() == bitmask.bitset.kNumBits);
    for (std::size_t i = 0; i < bitmask.bitset.kNumBits; ++i)
    {
      out.writeField(Fields::kNames[i], bitmask.bitset[i]);
    }
  }
}
