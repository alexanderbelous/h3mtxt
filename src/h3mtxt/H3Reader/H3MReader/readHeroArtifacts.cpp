#include <h3mtxt/H3Reader/H3MReader/H3MReader.h>
#include <h3mtxt/Map/HeroArtifacts.h>

namespace h3m
{
  HeroArtifacts H3MReader::readHeroArtifacts() const
  {
    HeroArtifacts artifacts;
    for (ArtifactType& artifact : artifacts.equipped.data)
    {
      artifact = readEnum<ArtifactType>();
    }
    const std::uint16_t backpack_count = readInt<std::uint16_t>();
    artifacts.backpack.reserve(backpack_count);
    for (std::uint16_t i = 0; i < backpack_count; ++i)
    {
      artifacts.backpack.push_back(readEnum<ArtifactType>());
    }
    return artifacts;
  }
}
