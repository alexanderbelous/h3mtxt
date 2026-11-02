#include <h3mtxt/H3JsonReader/H3MJsonReader/H3MJsonReader.h>

#include <h3mtxt/H3JsonReader/H3JsonReaderBase/H3JsonReaderBase.h>
#include <h3mtxt/JsonCommon/FieldNamesH3M.h>
#include <h3mtxt/Map/HeroArtifacts.h>

namespace h3json
{
  template<>
  h3m::HeroArtifacts JsonReader2<h3m::HeroArtifacts>::operator()() const
  {
    using Fields = FieldNames<h3m::HeroArtifacts>;
    h3m::HeroArtifacts artifacts;
    readField(Fields::kEquipped, artifacts.equipped);
    readField(Fields::kBackpack, artifacts.backpack);
    return artifacts;
  }
}
