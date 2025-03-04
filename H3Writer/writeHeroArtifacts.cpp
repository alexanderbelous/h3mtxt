#include <h3mtxt/H3Writer/H3Writer.h>
#include <h3mtxt/H3Writer/Utils.h>
#include <h3mtxt/Map/HeroArtifacts.h>

namespace h3m::H3Writer_NS
{
  void H3Writer<HeroArtifacts>::operator()(std::ostream& stream, const HeroArtifacts& artifacts) const
  {
    writeData(stream, artifacts.head);
    writeData(stream, artifacts.shoulders);
    writeData(stream, artifacts.neck);
    writeData(stream, artifacts.right_hand);
    writeData(stream, artifacts.left_hand);
    writeData(stream, artifacts.torso);
    writeData(stream, artifacts.right_ring);
    writeData(stream, artifacts.left_ring);
    writeData(stream, artifacts.feet);
    writeData(stream, artifacts.misc1);
    writeData(stream, artifacts.misc2);
    writeData(stream, artifacts.misc3);
    writeData(stream, artifacts.misc4);
    writeData(stream, artifacts.device1);
    writeData(stream, artifacts.device2);
    writeData(stream, artifacts.device3);
    writeData(stream, artifacts.device4);
    writeData(stream, artifacts.spellbook);
    writeData(stream, artifacts.misc5);
    writeVector<std::uint16_t>(stream, artifacts.backpack);
  }
}
