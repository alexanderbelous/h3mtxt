#include <h3mtxt/H3JsonWriter/writeH3mJson.h>

#include <h3mtxt/H3JsonWriter/H3JsonWriter.h>
#include <h3mtxt/JsonWriter/JsonValueWriter.h>

namespace h3m
{
  void writeH3mJson(std::ostream& stream, const Map& map)
  {
    Medea_NS::writeJson(stream, map);
  }
}
