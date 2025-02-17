#pragma once

#include <h3mtxt/H3MJsonReader/JsonReader.h>
#include <h3mtxt/Map/MapFwd.h>
#include <h3mtxt/Map/Utils/EnumBitmask.h>

namespace h3m
{
  template<>
  struct JsonReader<ArtifactsBitmask>
  {
    ArtifactsBitmask operator()(const Json::Value& value) const
    {
      ArtifactsBitmask artifacts_bitmask;
      artifacts_bitmask.bitset = fromJson<BitSet<18>>(value);
      return artifacts_bitmask;
    }
  };
}
