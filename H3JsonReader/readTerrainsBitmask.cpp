#include <h3mtxt/H3JsonReader/Utils.h>
#include <h3mtxt/Map/Utils/EnumBitmask.h>

namespace h3m::H3JsonReader_NS
{
  TerrainsBitmask JsonReader<TerrainsBitmask>::operator()(const Json::Value& value) const
  {
    TerrainsBitmask bitmask;
    bitmask.bitset = fromJson<BitSet<2>>(value);
    return bitmask;
  }
}
