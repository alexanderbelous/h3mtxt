#include <h3mtxt/H3Writer/H3Writer.h>
#include <h3mtxt/H3Writer/Utils.h>
#include <h3mtxt/Map/MapBasicInfo.h>

namespace h3m::H3Writer_NS
{
  void H3Writer<MapBasicInfo>::operator()(std::ostream& stream, const MapBasicInfo& value) const
  {
    writeData(stream, value.is_playable);
    writeData(stream, value.map_size);
    writeData(stream, value.has_two_levels);
    writeData(stream, value.name);
    writeData(stream, value.description);
    writeData(stream, value.difficulty);
    writeData(stream, value.max_hero_level);
  }
}
