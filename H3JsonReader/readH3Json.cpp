#include <h3mtxt/H3JsonReader/readH3Json.h>

#include <h3mtxt/H3JsonReader/H3JsonReader.h>
#include <h3mtxt/JsonCommon/FieldName.h>

#include <json/json.h>

#include <stdexcept>

namespace h3m::H3JsonReader_NS
{
  namespace
  {
    bool hasField(const Json::Value& value, std::string_view field_name)
    {
      return value.find(field_name.data(), field_name.data() + field_name.size()) != nullptr;
    }

    bool isCampaignJson(const Json::Value& value)
    {
      using Fields = FieldNames<Campaign>;
      return hasField(value, Fields::kHeader) && hasField(value, Fields::kMaps);
    }
  }

  std::variant<Map, Campaign> readH3Json(std::istream& stream)
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
      return JsonReader<Campaign>{}(root);
    }
    return JsonReader<Map>{}(root);
  }
}
