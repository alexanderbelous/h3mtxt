#include <h3mtxt/H3MReader/parseh3m.h>
#include <h3mtxt/H3MWriter/writeh3m.h>
#include <h3mtxt/H3MTxtWriter/writeH3mTxt.h>

#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>

namespace fs = std::filesystem;

int main(int argc, char** argv)
{
  if (argc != 2) {
    std::cout << "Usage: h3mtxt map-path" << std::endl;
    return -1;
  }

  try
  {
    const fs::path path_map(argv[1]);
    std::ifstream stream(path_map, std::ios_base::in | std::ios_base::binary);
    const h3m::Map map = h3m::parseh3m(stream);
    stream.close();
    h3m::writeH3mTxt(std::cout, map);
    std::ofstream out_stream("no_objects_or_events.h3m", std::ios_base::out | std::ios_base::binary);
    h3m::writeh3m(out_stream, map);
    out_stream.close();
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
