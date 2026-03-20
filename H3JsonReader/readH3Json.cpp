#include <h3mtxt/H3JsonReader/readH3Json.h>

#include <h3mtxt/H3JsonReader/H3CJsonReader/H3CJsonReader.h>
#include <h3mtxt/H3JsonReader/H3MJsonReader/H3MJsonReader.h>
#include <h3mtxt/JsonCommon/FieldNamesH3C.h>

#include <json/json.h>

#include <stdexcept>

namespace h3json
{
  namespace
  {
    bool hasField(const Json::Value& value, std::string_view field_name)
    {
      return value.find(field_name.data(), field_name.data() + field_name.size()) != nullptr;
    }

    bool isCampaignJson(const Json::Value& value)
    {
      using Fields = FieldNames<h3m::Campaign>;
      return hasField(value, Fields::kHeader) && hasField(value, Fields::kMaps);
    }
  }

  std::variant<h3m::Map, h3m::Campaign> readH3Json(std::istream& stream)
  {
    Json::Value root;
    {
      Json::CharReaderBuilder builder;
      builder["collectComments"] = false;
      Json::String errs;
      if (!parseFromStream(builder, stream, &root, &errs))
      {
        throw std::runtime_error("readH3Json(): " + errs);
      }
    }
    // Technically, it's possible to craft a JSON which can be interpreted as both Map and Campaign.
    // Failing on such file makes even less sense than favoring one interpretation over the other, so
    // I'm just gonna treat as Campaign in this case.
    if (isCampaignJson(root))
    {
      return JsonReader<h3m::Campaign>{}(root);
    }
    return JsonReader<h3m::Map>{}(root);
  }
}
