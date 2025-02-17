#pragma once

#include <h3mtxt/H3MJsonWriter/H3MJsonWriter.h>
#include <h3mtxt/Map/MapFwd.h>
#include <h3mtxt/Map/Utils/EnumBitmask.h>

namespace Medea_NS
{
  // TODO: replace with JsonObjectWriter and print true/false for each spell.
  template<>
  struct JsonValueWriter<h3m::SpellsBitmask>
  {
    void operator()(JsonDocumentWriter& out, const h3m::SpellsBitmask& bitmask) const
    {
      writeValue(out, bitmask.bitset);
    }
  };
}
