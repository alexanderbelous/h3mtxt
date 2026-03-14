#include <h3mtxt/H3JsonWriter/H3MJsonWriter/writeH3mJson.h>

#include <h3mtxt/H3JsonWriter/H3MJsonWriter/H3MJsonWriter.h>
#include <h3mtxt/Medea/Core.h>

namespace h3m
{
  void writeH3mJson(std::ostream& stream, const Map& map)
  {
    Medea_NS::writeJson(stream, map);
  }
}
