#include <h3mtxt/H3JsonReader/H3CJsonReader/readH3cJson.h>

#include <h3mtxt/H3JsonReader/H3CJsonReader/H3CJsonReader.h>
#include <h3mtxt/H3JsonReader/H3JsonReaderBase/Utils.h>

namespace h3json
{
  h3m::Campaign readH3cJson(std::istream& stream)
  {
    return fromJsonStream<h3m::Campaign>(stream);
  }
}
