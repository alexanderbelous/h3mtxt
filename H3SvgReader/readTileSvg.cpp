#include <h3mtxt/H3SvgReader/H3SvgReader.h>
#include <h3mtxt/SavedGame/TileSvg.h>

namespace h3m
{
  TileSvg H3SvgReader::readTile() const
  {
    TileSvg tile;
    tile.terrain_type = readEnum<TerrainType>();
    tile.terrain_sprite = readInt<std::uint8_t>();
    tile.river_type = readEnum<RiverType>();
    tile.river_sprite = readInt<std::uint8_t>();
    tile.road_type = readEnum<RoadType>();
    tile.road_sprite = readInt<std::uint8_t>();
    tile.flags1 = readInt<std::uint8_t>();
    tile.flags2 = readInt<std::uint8_t>();
    tile.object_class = readEnum<ObjectClass16>();
    tile.object_subclass = readInt<std::uint16_t>();
    tile.object_idx = readInt<std::uint16_t>();
    readBytes(std::span<std::byte, 4>{ tile.unknown });
    const std::uint32_t num_objects_to_render = readInt<std::uint32_t>();
    tile.objects_to_render.reserve(num_objects_to_render);
    for (std::uint32_t i = 0; i < num_objects_to_render; ++i)
    {
      TileSvg::ObjectToRender object_to_render;
      object_to_render.object_idx = readInt<std::uint16_t>();
      object_to_render.unknown = readInt<std::uint16_t>();
      tile.objects_to_render.push_back(object_to_render);
    }
    return tile;
  }
}
