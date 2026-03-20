#include <h3mtxt/H3JsonReader/H3MJsonReader/H3MJsonReader.h>

#include <h3mtxt/H3JsonReader/H3JsonReaderBase/H3JsonReaderBase.h>
#include <h3mtxt/Map/Utils/EnumBitmask.h>

namespace h3json
{
  h3m::TerrainsBitmask JsonReader<h3m::TerrainsBitmask>::operator()(const Json::Value& value) const
  {
    h3m::TerrainsBitmask bitmask;
    bitmask.bitset = fromJson<h3m::BitSet<2>>(value);
    return bitmask;
  }
}
