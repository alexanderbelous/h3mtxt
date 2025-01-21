#include <h3mtxt/H3MReader/readHeroArtifacts.h>

#include <h3mtxt/H3MReader/Utils.h>

namespace h3m
{
  HeroArtifacts readHeroArtifacts(std::istream& stream)
  {
    HeroArtifacts artifacts;
    artifacts.headwear = readUint<std::uint16_t>(stream);
    artifacts.shoulders = readUint<std::uint16_t>(stream);
    artifacts.neck = readUint<std::uint16_t>(stream);
    artifacts.right_hand = readUint<std::uint16_t>(stream);
    artifacts.left_hand = readUint<std::uint16_t>(stream);
    artifacts.torso = readUint<std::uint16_t>(stream);
    artifacts.right_ring = readUint<std::uint16_t>(stream);
    artifacts.left_ring = readUint<std::uint16_t>(stream);
    artifacts.feet = readUint<std::uint16_t>(stream);
    artifacts.misc1 = readUint<std::uint16_t>(stream);
    artifacts.misc2 = readUint<std::uint16_t>(stream);
    artifacts.misc3 = readUint<std::uint16_t>(stream);
    artifacts.misc4 = readUint<std::uint16_t>(stream);
    artifacts.device1 = readUint<std::uint16_t>(stream);
    artifacts.device2 = readUint<std::uint16_t>(stream);
    artifacts.device3 = readUint<std::uint16_t>(stream);
    artifacts.device4 = readUint<std::uint16_t>(stream);
    artifacts.spellbook = readUint<std::uint16_t>(stream);
    artifacts.misc5 = readUint<std::uint16_t>(stream);
    const std::uint16_t backpack_count = readUint<std::uint16_t>(stream);
    artifacts.backpack.reserve(backpack_count);
    for (std::uint16_t i = 0; i < backpack_count; ++i)
    {
      artifacts.backpack.push_back(readUint<std::uint16_t>(stream));
    }
    return artifacts;
  }
}
