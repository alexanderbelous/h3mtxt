#include <h3mtxt/Map/Map.h>
#include <h3mtxt/H3Reader/H3MReader/parseh3m.h>

#include <Minimap/Minimap.h>

#include <fstream>
#include <filesystem>
#include <iostream>
#include <stdexcept>

int main(int argc, char** argv)
{
  if (argc != 3)
  {
    std::cout << "Usage: draw_minimap <path_to_map> <output_path.png>" << std::endl;
    return (argc == 0) ? 0 : -1;
  }

  try
  {
    const std::filesystem::path input_path{ argv[1] };
    const std::filesystem::path output_path{ argv[2] };

    // Read the map.
    std::ifstream stream{ input_path, std::ios_base::in | std::ios_base::binary };
    const h3m::Map map = h3m::parseh3m(stream);
    stream.close();

    // Construct an image for the minimap.
    const Minimap_NS::Image minimap = Minimap_NS::makeMinimap(map, false);

    // Save the image as PNG.
    Minimap_NS::writeImage(output_path, minimap);
  }
  catch (const std::exception& error)
  {
    std::cerr << error.what() << std::endl;
    return -1;
  }

  return 0;
}
