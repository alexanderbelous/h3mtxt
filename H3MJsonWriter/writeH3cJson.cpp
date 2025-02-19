#include <h3mtxt/H3MJsonWriter/writeH3mJson.h>
#include <h3mtxt/H3MJsonWriter/writeCampaign.h>

#include <h3mtxt/JsonWriter/JsonDocumentWriter.h>

namespace h3m
{
  void writeH3cJson(std::ostream& stream, const Campaign& campaign)
  {
    Medea_NS::JsonDocumentWriter writer(stream, 0);
    Medea_NS::writeValue(writer, campaign);
  }
}
