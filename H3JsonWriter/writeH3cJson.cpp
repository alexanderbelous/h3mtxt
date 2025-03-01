#include <h3mtxt/H3JsonWriter/writeH3cJson.h>

#include <h3mtxt/H3JsonWriter/H3JsonWriter.h>
#include <h3mtxt/JsonWriter/JsonValueWriter.h>

namespace h3m
{
  void writeH3cJson(std::ostream& stream, const Campaign& campaign)
  {
    Medea_NS::JsonDocumentWriter document_writer(stream, 0);
    Medea_NS::JsonValueWriter<Campaign> value_writer {};
    value_writer(document_writer, campaign);
  }
}
