#include <h3mtxt/H3Reader/H3SVGReader/H3SVGReader.h>
#include <h3mtxt/SavedGame/Tile.h>

namespace h3svg
{
  Tile H3SVGReader::readTile() const
  {
    Tile tile;
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
    readBytes(std::span<std::byte, 4>{ tile.object_properties });
    const std::uint32_t num_objects_to_render = readInt<std::uint32_t>();
    tile.objects_to_render.reserve(num_objects_to_render);
    for (std::uint32_t i = 0; i < num_objects_to_render; ++i)
    {
      tile.objects_to_render.push_back(readTileRenderInfo());
    }
    return tile;
  }

  TileRenderInfo H3SVGReader::readTileRenderInfo() const
  {
    TileRenderInfo object_to_render;
    object_to_render.object_idx = readInt<std::uint16_t>();
    const std::uint8_t sprite_tile_coordinates_packed = readInt<std::uint8_t>();
    object_to_render.x = static_cast<std::uint8_t>(sprite_tile_coordinates_packed & 0x0Fu);
    object_to_render.y = static_cast<std::uint8_t>((sprite_tile_coordinates_packed & 0xF0u) >> 4);
    object_to_render.z_buffer = readInt<std::uint8_t>();
    return object_to_render;
  }
}
