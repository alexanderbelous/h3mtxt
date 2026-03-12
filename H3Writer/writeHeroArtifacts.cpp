#include <h3mtxt/H3Writer/H3Writer.h>
#include <h3mtxt/H3Writer/Utils.h>
#include <h3mtxt/Map/HeroArtifacts.h>

namespace h3m::H3Writer_NS
{
  void H3Writer<HeroArtifacts>::operator()(std::ostream& stream, const HeroArtifacts& artifacts) const
  {
    writeData(stream, artifacts.equipped);
    writeVector<std::uint16_t>(stream, artifacts.backpack);
  }
}
