#include <h3mtxt/H3JsonReader/H3MJsonReader/readH3mJson.h>

#include <h3mtxt/H3JsonReader/H3JsonReaderBase/Utils.h>
#include <h3mtxt/H3JsonReader/H3MJsonReader/H3MJsonReader.h>

namespace h3json
{
  h3m::Map readH3mJson(std::istream& stream)
  {
    return fromJsonStream<h3m::Map>(stream);
  }
}
