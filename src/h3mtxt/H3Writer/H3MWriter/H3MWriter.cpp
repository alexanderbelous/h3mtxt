#include <h3mtxt/H3Writer/H3MWriter/H3MWriter.h>

#include <h3mtxt/Map/Coordinates.h>
#include <h3mtxt/Map/CreatureStack.h>
#include <h3mtxt/Map/HeroArtifacts.h>
#include <h3mtxt/Map/SecondarySkill.h>

#include <stdexcept>

namespace h3m
{
  H3MWriter::H3MWriter(std::ostream& stream, MapFormat map_format):
    H3WriterBase{ stream },
    map_format_{ map_format }
  {
    if (map_format != MapFormat::ArmageddonsBlade &&
        map_format != MapFormat::ShadowOfDeath)
    {
      throw std::invalid_argument("H3MWriter: invalid MapFormat");
    }
  }

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
    writeData(value.quantity);
  }

  void H3MWriter::writeData(const HeroArtifacts& value) const
  {
    // Misc5 is ignored for MapFormat::RestorationOfErathia and MapFormat::ArmageddonsBlade.
    writeSpan(std::span{ value.equipped.data }.first(countArtifactSlots(map_format_)));
    writeData(safeCastVectorSize<std::uint16_t>(value.backpack.size()));
    writeSpan(std::span{ value.backpack });
  }

  void H3MWriter::writeData(const SecondarySkill& secondary_skill) const
  {
    writeData(secondary_skill.type);
    writeData(secondary_skill.level);
  }
}
