#include <h3mtxt/H3Writer/H3MWriter/H3MWriter.h>
#include <h3mtxt/Map/ObjectTemplate.h>

namespace h3m
{
  void H3MWriter::writeData(const SpriteTilesBitmask& value) const
  {
    writeData(value.data);
  }

  void H3MWriter::writeData(const ObjectTemplate& value) const
  {
    writeData(value.def);
    writeData(value.passability);
    writeData(value.actionability);
    writeData(value.allowed_landscapes);
    writeData(value.landscape_group);
    writeData(value.object_class);
    writeData(value.object_subclass);
    writeData(value.object_group);
    writeData(value.is_ground);
    writeData(value.unknown);
  }
}
