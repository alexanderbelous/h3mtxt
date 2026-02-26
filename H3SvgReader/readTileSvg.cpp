#include <h3mtxt/H3SvgReader/H3SvgReader.h>
#include <h3mtxt/H3SvgReader/Utils.h>
#include <h3mtxt/H3Reader/H3Reader.h>
#include <h3mtxt/H3Reader/Utils.h>
#include <h3mtxt/SavedGame/TileSvg.h>

namespace h3m::H3SvgReader_NS
{
  using H3Reader_NS::readBool;
  using H3Reader_NS::readEnum;
  using H3Reader_NS::readEnumBitmask;
  using H3Reader_NS::readInt;
  using H3Reader_NS::readReservedData;

  TileSvg readTileSvg(std::istream& stream)
  {
    TileSvg tile;
    tile.terrain_type = readEnum<TerrainType>(stream);
    tile.terrain_sprite = readInt<std::uint8_t>(stream);
    tile.river_type = readEnum<RiverType>(stream);
    tile.river_sprite = readInt<std::uint8_t>(stream);
    tile.road_type = readEnum<RoadType>(stream);
    tile.road_sprite = readInt<std::uint8_t>(stream);
    tile.flags1 = readInt<std::uint8_t>(stream);
    tile.flags2 = readInt<std::uint8_t>(stream);
    tile.object_class = readInt<std::uint16_t>(stream);
    tile.object_subclass = readInt<std::uint16_t>(stream);
    tile.object_idx = readInt<std::uint16_t>(stream);
    H3Reader_NS::Detail_NS::readByteArrayImpl(stream, std::span<std::byte, 4>{ tile.unknown });
    const std::uint32_t num_objects_to_render = readInt<std::uint32_t>(stream);
    tile.objects_to_render.reserve(num_objects_to_render);
    for (std::uint32_t i = 0; i < num_objects_to_render; ++i)
    {
      TileSvg::ObjectToRender object_to_render;
      object_to_render.object_idx = readInt<std::uint16_t>(stream);
      object_to_render.unknown = readInt<std::uint16_t>(stream);
      tile.objects_to_render.push_back(object_to_render);
    }
    return tile;
  }
}
