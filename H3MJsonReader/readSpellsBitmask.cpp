#include <h3mtxt/H3MJsonReader/Utils.h>
#include <h3mtxt/JsonCommon/FieldName.h>
#include <h3mtxt/Map/Utils/EnumBitmask.h>

namespace h3m::H3JsonReader_NS
{
  SpellsBitmask JsonReader<SpellsBitmask>::operator()(const Json::Value& value) const
  {
    SpellsBitmask spells_bitmask;
    spells_bitmask.bitset = fromJson<BitSet<9>>(value);
    return spells_bitmask;
  }
}
