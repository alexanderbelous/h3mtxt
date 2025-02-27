#include <h3mtxt/H3JsonWriter/writeH3mJson.h>
#include <h3mtxt/H3JsonWriter/writeMap.h>

#include <h3mtxt/JsonWriter/JsonDocumentWriter.h>

namespace h3m
{
  void writeH3mJson(std::ostream& stream, const Map& map)
  {
    Medea_NS::JsonDocumentWriter writer(stream, 0);
    Medea_NS::writeValue(writer, map);
  }
}
