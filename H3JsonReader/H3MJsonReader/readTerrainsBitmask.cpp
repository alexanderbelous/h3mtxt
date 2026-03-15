#include <h3mtxt/H3JsonReader/H3MJsonReader/H3MJsonReader.h>

#include <h3mtxt/H3JsonReader/H3JsonReaderBase/H3JsonReaderBase.h>
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
