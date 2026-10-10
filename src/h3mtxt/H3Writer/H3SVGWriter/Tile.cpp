#include <h3mtxt/H3Writer/H3SVGWriter/H3SVGWriter.h>

#include <h3mtxt/SavedGame/Tile.h>

namespace h3svg
{
  void H3SVGWriter::writeData(const Tile& tile) const
  {
    writeData(tile.terrain_type);
    writeData(tile.terrain_sprite);
    writeData(tile.river_type);
    writeData(tile.river_sprite);
    writeData(tile.road_type);
    writeData(tile.road_sprite);
    writeData(tile.flags);
    writeData(tile.object_class);
    writeData(tile.object_subclass);
    writeData(tile.object_idx);
    writeData(tile.object_properties);
    writeVector<std::uint32_t>(std::span{ tile.objects_to_render });
  }

  void H3SVGWriter::writeData(const TileRenderInfo& object_to_render) const
  {
    writeData(object_to_render.object_idx);
    const std::uint8_t sprite_tile_coordinates_packed = (object_to_render.y << 4) | object_to_render.x;
    writeData(sprite_tile_coordinates_packed);
    writeData(object_to_render.z_buffer);
  }
}
