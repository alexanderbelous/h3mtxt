#pragma once

#include <Minimap/Image.h>

#include <h3mtxt/Map/MapFwd.h>

namespace Minimap_NS
{
  // Constructs a minimap image for the given h3m::Map.
  //
  // The function constructs a NxN RGB24 image, where N = map.basic_info.map_size.
  // The image is the same as shown in the Map Editor.
  //
  // The constructed image can be saved as PNG via:
  //   Minimap_NS::writeImage("image.png", image);  // see Image.h
  //
  // \param map - input h3m::Map.
  // \param subterranean - if true, the function will construct an image for the subterranean level,
  //        otherwise for the surface.
  // \return a minimap image for @map.
  // \throw std::invalid_argument if !map.basic_info.has_two_levels && subterranean.
  Image makeMinimap(const h3m::Map& map, bool subterranean);
}
