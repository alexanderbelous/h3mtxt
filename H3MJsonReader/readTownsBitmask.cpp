#include <h3mtxt/H3MJsonReader/Utils.h>
#include <h3mtxt/JsonCommon/FieldName.h>
#include <h3mtxt/Map/Utils/EnumBitmask.h>

namespace h3m
{
  TownsBitmask JsonReader<TownsBitmask>::operator()(const Json::Value& value) const
  {
    using Fields = FieldNames<TownsBitmask>;
    TownsBitmask bitmask {};
    static_assert(Fields::kNames.size() == bitmask.bitset.kNumBits,
                  "The number of fields in h3m::FieldNames<h3m::TownsBitmask> "
                  "should match the number of bits in h3m::TownsBitmask");
    for (std::size_t i = 0; i < bitmask.bitset.kNumBits; ++i)
    {
      bitmask.bitset.set(i, readField<bool>(value, Fields::kNames[i]));
    }
    return bitmask;
  }
}
