#include <h3mtxt/H3JsonReader/H3MJsonReader/H3MJsonReader.h>

#include <h3mtxt/H3JsonReader/H3JsonReaderBase/H3JsonReaderBase.h>
#include <h3mtxt/JsonCommon/FieldNamesH3M.h>
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
