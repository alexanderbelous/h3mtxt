#include <h3mtxt/H3Writer/H3SVGWriter/H3SVGWriter.h>

#include <h3mtxt/Map/MapBasicInfo.h>

namespace h3svg
{
  void H3SVGWriter::writeData(const MapBasicInfo& basic_info) const
  {
    writeData(basic_info.is_playable);
    writeData(basic_info.map_size);
    writeData(basic_info.has_two_levels);
    writeString16(basic_info.name);
    writeString16(basic_info.description);
    writeData(basic_info.difficulty);
    writeData(basic_info.max_hero_level);
  }
}
