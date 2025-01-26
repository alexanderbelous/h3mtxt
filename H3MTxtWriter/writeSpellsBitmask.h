#pragma once

#include <h3mtxt/Map/SpellsBitmask.h>
#include <h3mtxt/H3MTxtWriter/H3MTxtWriter.h>

namespace Util_NS
{
  // TODO: replace with StructWriter and print true/false for each spell.
  template<>
  struct ValueWriter<h3m::SpellsBitmask>
  {
    void operator()(IndentedTextWriter& out, const h3m::SpellsBitmask& bitmask) const
    {
      writeValue(out, bitmask.bitset);
    }
  };
}
