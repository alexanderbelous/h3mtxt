#include <h3mtxt/H3JsonReader/H3MJsonReader/readH3mJson.h>

#include <h3mtxt/H3JsonReader/H3MJsonReader/H3MJsonReader.h>

#include <json/json.h>

#include <stdexcept>

namespace h3json
{
  h3m::Map readH3mJson(std::istream& stream)
  {
    Json::Value root;
    {
      Json::CharReaderBuilder builder;
      builder["collectComments"] = false;
      Json::String errs;
      if (!parseFromStream(builder, stream, &root, &errs))
      {
        throw std::runtime_error("readH3mJson(): " + errs);
      }
    }
    return JsonReader<h3m::Map>{}(root);
  }
}
