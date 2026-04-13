#include <h3mtxt/H3JsonReader/readH3Json.h>

#include <h3mtxt/H3JsonReader/H3CJsonReader/H3CJsonReader.h>
#include <h3mtxt/H3JsonReader/H3JsonReaderBase/Utils.h>
#include <h3mtxt/H3JsonReader/H3MJsonReader/H3MJsonReader.h>
#include <h3mtxt/JsonCommon/FieldNamesH3C.h>

namespace h3json
{
  namespace
  {
    bool isCampaignJson(const Json::Value& value)
    {
      using Fields = FieldNames<h3m::Campaign>;
      return value.isMember(Fields::kHeader) && value.isMember(Fields::kMaps);
    }
  }

  std::variant<h3m::Map, h3m::Campaign> readH3Json(std::istream& stream)
  {
    const Json::Value root = parseJsonFromStream(stream);

    // Technically, it's possible to craft a JSON which can be interpreted as both Map and Campaign.
    // Failing on such files makes even less sense than favoring one interpretation over the other, so
    // I'm just gonna treat it as Campaign in this case.
    if (isCampaignJson(root))
    {
      return JsonReader<h3m::Campaign>{}(root);
    }
    return JsonReader<h3m::Map>{}(root);
  }
}
