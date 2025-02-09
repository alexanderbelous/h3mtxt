#pragma once

#include <h3mtxt/Map/SpellsBitmask.h>
#include <h3mtxt/H3MJsonWriter/H3MJsonWriter.h>

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
