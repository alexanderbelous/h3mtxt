#include <h3mtxt/H3MJsonReader/Utils.h>
#include <h3mtxt/Map/Utils/EnumBitmask.h>

namespace h3m
{
  ArtifactsBitmask JsonReader<ArtifactsBitmask>::operator()(const Json::Value& value) const
  {
    ArtifactsBitmask artifacts_bitmask;
    artifacts_bitmask.bitset = fromJson<BitSet<18>>(value);
    return artifacts_bitmask;
  }
}
