#include <h3mtxt/H3MJsonReader/readH3mJson.h>

#include <h3mtxt/H3MJsonReader/H3JsonReader.h>

#include <json/json.h>

#include <stdexcept>

namespace h3m
{
  Map readH3mJson(std::istream& stream)
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
    return JsonReader<Map>{}(root);
  }
}
