#include <h3mtxt/H3JsonWriter/H3CJsonWriter/writeH3cJson.h>

#include <h3mtxt/H3JsonWriter/H3CJsonWriter/H3CJsonWriter.h>
#include <h3mtxt/Medea/Core.h>

namespace h3m
{
  void writeH3cJson(std::ostream& stream, const Campaign& campaign)
  {
    Medea_NS::writeJson(stream, campaign);
  }
}
