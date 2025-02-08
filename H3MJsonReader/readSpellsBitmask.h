#pragma once

#include <h3mtxt/H3MJsonReader/JsonReader.h>
#include <h3mtxt/JsonCommon/FieldName.h>
#include <h3mtxt/Map/SpellsBitmask.h>

namespace h3m
{
  template<>
  struct JsonReader<SpellsBitmask>
  {
    SpellsBitmask operator()(const Json::Value& value) const
    {
      SpellsBitmask spells_bitmask;
      spells_bitmask.bitset = fromJson<BitSet<9>>(value);
      return spells_bitmask;
    }
  };
}
