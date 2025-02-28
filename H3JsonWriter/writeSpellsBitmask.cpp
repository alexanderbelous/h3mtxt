#include <h3mtxt/H3JsonWriter/API.h>
#include <h3mtxt/H3JsonWriter/H3JsonWriter.h>
#include <h3mtxt/Map/Utils/EnumBitmask.h>

namespace Medea_NS
{
  // TODO: replace with JsonObjectWriter and print true/false for each spell.
  void JsonValueWriter<h3m::SpellsBitmask>::operator()(JsonDocumentWriter& out,
                                                       const h3m::SpellsBitmask& bitmask) const
  {
    writeValue(out, bitmask.bitset);
  }
}
