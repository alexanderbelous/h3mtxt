#include <h3mtxt/H3JsonReader/H3MJsonReader/H3MJsonReader.h>

#include <h3mtxt/H3JsonReader/H3JsonReaderBase/H3JsonReaderBase.h>
#include <h3mtxt/JsonCommon/FieldNamesH3M.h>
#include <h3mtxt/Map/HeroArtifacts.h>

namespace h3json
{
  h3m::HeroArtifacts JsonReader<h3m::HeroArtifacts>::operator()(const Json::Value& value) const
  {
    using Fields = FieldNames<h3m::HeroArtifacts>;
    h3m::HeroArtifacts artifacts;
    readField(artifacts.equipped, value, Fields::kEquipped);
    readField(artifacts.backpack, value, Fields::kBackpack);
    return artifacts;
  }
}
