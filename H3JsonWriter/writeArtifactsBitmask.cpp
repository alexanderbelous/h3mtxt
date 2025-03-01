#include <h3mtxt/H3JsonWriter/H3JsonWriter.h>
#include <h3mtxt/H3JsonWriter/Utils.h>
#include <h3mtxt/Map/Utils/EnumBitmask.h>

namespace Medea_NS
{
  // TODO: replace with JsonObjectWriter and print true/false for each artifact.
  void JsonValueWriter<h3m::ArtifactsBitmask>::operator()(JsonDocumentWriter& out, const h3m::ArtifactsBitmask& bitmask) const
  {
    writeValue(out, bitmask.bitset);
  }
}
