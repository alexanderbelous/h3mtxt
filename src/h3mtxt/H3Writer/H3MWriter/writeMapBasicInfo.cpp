#include <h3mtxt/H3Writer/H3MWriter/H3MWriter.h>
#include <h3mtxt/Map/MapBasicInfo.h>

namespace h3m
{
  void H3MWriter::writeData(const MapBasicInfo& value) const
  {
    writeData(value.is_playable);
    writeData(value.map_size);
    writeData(value.has_two_levels);
    writeData(value.name);
    writeData(value.description);
    writeData(value.difficulty);
    writeData(value.max_hero_level);
  }
}
