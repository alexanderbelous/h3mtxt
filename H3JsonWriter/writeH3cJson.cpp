#include <h3mtxt/H3JsonWriter/writeH3cJson.h>

#include <h3mtxt/H3JsonWriter/H3JsonWriter.h>
#include <h3mtxt/JsonWriter/writeJson.h>

namespace h3m
{
  void writeH3cJson(std::ostream& stream, const Campaign& campaign)
  {
    Medea_NS::writeJson(stream, campaign);
  }
}
