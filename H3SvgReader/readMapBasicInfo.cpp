#include <h3mtxt/H3SvgReader/H3SvgReader.h>
#include <h3mtxt/Map/MapBasicInfo.h>

namespace h3m
{
  MapBasicInfo H3SvgReader::readMapBasicInfo() const
  {
    MapBasicInfo basic_info;
    basic_info.is_playable = readBool();
    basic_info.map_size = readInt<std::uint32_t>();
    basic_info.has_two_levels = readBool();
    basic_info.name = readString16();
    basic_info.description = readString16();
    basic_info.difficulty = readEnum<MapDifficulty>();
    basic_info.max_hero_level = readInt<std::uint8_t>();
    return basic_info;
  }
}
