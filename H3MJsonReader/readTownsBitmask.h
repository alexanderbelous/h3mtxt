#pragma once

#include <h3mtxt/H3MJsonReader/JsonReader.h>
#include <h3mtxt/Map/TownsBitmask.h>

namespace h3m
{
  template<>
  struct JsonReader<TownsBitmask>
  {
    TownsBitmask operator()(const Json::Value& value) const
    {
      TownsBitmask towns_bitmask {};
      towns_bitmask.bitset = fromJson<BitSet<2>>(value);
      return towns_bitmask;
    }
  };
}
