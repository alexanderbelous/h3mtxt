#include <h3mtxt/H3Reader/Utils.h>
#include <h3mtxt/H3SvgReader/H3SvgReader.h>
#include <h3mtxt/H3SvgReader/Utils.h>
#include <h3mtxt/Map/MapBasicInfo.h>

namespace h3m::H3SvgReader_NS
{
  using H3Reader_NS::readBool;
  using H3Reader_NS::readEnum;
  using H3Reader_NS::readInt;

  MapBasicInfo readMapBasicInfo(std::istream& stream)
  {
    MapBasicInfo basic_info;
    basic_info.is_playable = readBool(stream);
    basic_info.map_size = readInt<std::uint32_t>(stream);
    basic_info.has_two_levels = readBool(stream);
    basic_info.name = readString(stream);
    basic_info.description = readString(stream);
    basic_info.difficulty = readEnum<MapDifficulty>(stream);
    basic_info.max_hero_level = readInt<std::uint8_t>(stream);
    return basic_info;
  }
}
