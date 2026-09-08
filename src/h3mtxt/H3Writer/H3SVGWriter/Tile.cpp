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
    writeData(tile.flags1);
    writeData(tile.flags2);
    writeData(tile.object_class);
    writeData(tile.object_subclass);
    writeData(tile.object_idx);
    writeData(tile.object_properties);
    writeData(safeCastVectorSize<std::uint32_t>(tile.objects_to_render.size()));
    // TODO: replace with writeSpan(std::span{ tile.objects_to_render });
    for (const Tile::ObjectToRender& object : tile.objects_to_render)
    {
      writeData(object.object_idx);
      writeData(object.unknown);
    }
  }
}
