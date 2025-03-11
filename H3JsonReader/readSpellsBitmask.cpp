#include <h3mtxt/H3JsonReader/Utils.h>
#include <h3mtxt/JsonCommon/FieldName.h>
#include <h3mtxt/Map/Utils/EnumBitmask.h>

namespace h3m::H3JsonReader_NS
{
  SpellsBitmask JsonReader<SpellsBitmask>::operator()(const Json::Value& value) const
  {
    using Fields = FieldNames<SpellsBitmask>;
    static_assert(Fields::kNames.size() == SpellsBitmask::kNumBits);
    SpellsBitmask bitmask;
    for (std::size_t i = 0; i < bitmask.bitset.kNumBits; ++i)
    {
      bitmask.bitset.set(i, readField<bool>(value, Fields::kNames[i]));
    }
    return bitmask;
  }
}
