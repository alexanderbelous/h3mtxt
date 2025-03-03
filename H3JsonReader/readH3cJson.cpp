#include <h3mtxt/H3JsonReader/readH3cJson.h>

#include <h3mtxt/H3JsonReader/H3JsonReader.h>

#include <json/json.h>

#include <stdexcept>

namespace h3m::H3JsonReader_NS
{
  Campaign readH3cJson(std::istream& stream)
  {
    Json::Value root;
    {
      Json::CharReaderBuilder builder;
      builder["collectComments"] = false;
      Json::String errs;
      if (!parseFromStream(builder, stream, &root, &errs))
      {
        throw std::runtime_error("readH3cJson(): " + errs);
      }
    }
    return JsonReader<Campaign>{}(root);
  }
}
