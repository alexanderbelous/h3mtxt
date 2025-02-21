#include <h3mtxt/H3Reader/H3Reader.h>
#include <h3mtxt/H3Reader/Utils.h>
#include <h3mtxt/Map/HeroArtifacts.h>

namespace h3m::H3Reader_NS
{
  HeroArtifacts readHeroArtifacts(std::istream& stream)
  {
    HeroArtifacts artifacts;
    artifacts.headwear = readEnum<ArtifactType>(stream);
    artifacts.shoulders = readEnum<ArtifactType>(stream);
    artifacts.neck = readEnum<ArtifactType>(stream);
    artifacts.right_hand = readEnum<ArtifactType>(stream);
    artifacts.left_hand = readEnum<ArtifactType>(stream);
    artifacts.torso = readEnum<ArtifactType>(stream);
    artifacts.right_ring = readEnum<ArtifactType>(stream);
    artifacts.left_ring = readEnum<ArtifactType>(stream);
    artifacts.feet = readEnum<ArtifactType>(stream);
    artifacts.misc1 = readEnum<ArtifactType>(stream);
    artifacts.misc2 = readEnum<ArtifactType>(stream);
    artifacts.misc3 = readEnum<ArtifactType>(stream);
    artifacts.misc4 = readEnum<ArtifactType>(stream);
    artifacts.device1 = readEnum<ArtifactType>(stream);
    artifacts.device2 = readEnum<ArtifactType>(stream);
    artifacts.device3 = readEnum<ArtifactType>(stream);
    artifacts.device4 = readEnum<ArtifactType>(stream);
    artifacts.spellbook = readEnum<ArtifactType>(stream);
    artifacts.misc5 = readEnum<ArtifactType>(stream);
    const std::uint16_t backpack_count = readInt<std::uint16_t>(stream);
    artifacts.backpack.reserve(backpack_count);
    for (std::uint16_t i = 0; i < backpack_count; ++i)
    {
      artifacts.backpack.push_back(readEnum<ArtifactType>(stream));
    }
    return artifacts;
  }
}
