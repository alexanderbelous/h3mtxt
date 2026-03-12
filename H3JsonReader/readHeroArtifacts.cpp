#include <h3mtxt/H3JsonReader/Utils.h>
#include <h3mtxt/JsonCommon/FieldName.h>
#include <h3mtxt/Map/HeroArtifacts.h>

namespace h3m::H3JsonReader_NS
{
  HeroArtifacts JsonReader<HeroArtifacts>::operator()(const Json::Value& value) const
  {
    using Fields = FieldNames<HeroArtifacts>;
    HeroArtifacts artifacts;
    readField(artifacts.equipped, value, Fields::kEquipped);
    readField(artifacts.backpack, value, Fields::kBackpack);
    return artifacts;
  }
}
