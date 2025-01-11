#include <h3mparser/parseh3m.h>
#include <h3mparser/writeText.h>

#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>

namespace fs = std::filesystem;

int main(int argc, char** argv)
{
  if (argc != 2) {
    std::cout << "Usage: h3mparser map-path" << std::endl;
    return -1;
  }

  try
  {
    const fs::path path_map(argv[1]);
    std::ifstream stream(path_map, std::ios_base::in | std::ios_base::binary);
    const h3m::Map map = h3m::parseh3m(stream);
    stream.close();
    h3m::writeText(std::cout, map);

  }
  catch (const std::exception& error)
  {
    std::cerr << error.what() << std::endl;
  }
  catch (...)
  {
    std::cerr << "Unknown error." << std::endl;
  }

  return 0;
}
