#include <h3mtxt/H3JsonWriter/API.h>
#include <h3mtxt/H3JsonWriter/H3JsonWriter.h>
#include <h3mtxt/JsonCommon/FieldName.h>
#include <h3mtxt/Map/Utils/EnumBitmask.h>

namespace Medea_NS
{
  void JsonObjectWriter<h3m::TownsBitmask>::operator()(FieldsWriter& out, const h3m::TownsBitmask& bitmask) const
  {
    using Fields = h3m::FieldNames<h3m::TownsBitmask>;
    static_assert(Fields::kNames.size() == bitmask.bitset.kNumBits,
                  "The number of fields in h3m::FieldNames<h3m::TownsBitmask> "
                  "should match the number of bits in h3m::TownsBitmask");
    for (std::size_t i = 0; i < bitmask.bitset.kNumBits; ++i)
    {
      out.writeField(Fields::kNames[i], bitmask.bitset[i]);
    }
  }
}
