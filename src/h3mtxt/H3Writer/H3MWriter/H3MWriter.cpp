#include <h3mtxt/H3Writer/H3MWriter/H3MWriter.h>

#include <h3mtxt/Map/Coordinates.h>
#include <h3mtxt/Map/CreatureStack.h>
#include <h3mtxt/Map/HeroArtifacts.h>
#include <h3mtxt/Map/SecondarySkill.h>

namespace h3m
{
  void H3MWriter::writeData(const std::string& value) const
  {
    writeString32(value);
  }

  void H3MWriter::writeData(const Coordinates& value) const
  {
    writeData(value.x);
    writeData(value.y);
    writeData(value.z);
  }

  void H3MWriter::writeData(const CreatureStack& value) const
  {
    writeData(value.type);
    writeData(value.count);
  }

  void H3MWriter::writeData(const HeroArtifacts& value) const
  {
    writeData(value.equipped);
    writeData(safeCastVectorSize<std::uint16_t>(value.backpack.size()));
    writeSpan(std::span{ value.backpack });
  }

  void H3MWriter::writeData(const SecondarySkill& secondary_skill) const
  {
    writeData(secondary_skill.type);
    writeData(secondary_skill.level);
  }
}
