#include <h3mtxt/H3Reader/H3Reader.h>
#include <h3mtxt/H3Reader/Utils.h>
#include <h3mtxt/Map/HeroArtifacts.h>

namespace h3m::H3Reader_NS
{
  HeroArtifacts readHeroArtifacts(std::istream& stream)
  {
    HeroArtifacts artifacts;
    for (ArtifactType& artifact : artifacts.equipped.data)
    {
      artifact = readEnum<ArtifactType>(stream);
    }
    const std::uint16_t backpack_count = readInt<std::uint16_t>(stream);
    artifacts.backpack.reserve(backpack_count);
    for (std::uint16_t i = 0; i < backpack_count; ++i)
    {
      artifacts.backpack.push_back(readEnum<ArtifactType>(stream));
    }
    return artifacts;
  }
}
