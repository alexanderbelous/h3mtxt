#include <h3mtxt/H3MJsonReader/readH3mJson.h>
#include <h3mtxt/H3MReader/parseh3m.h>
#include <h3mtxt/H3MWriter/writeh3m.h>
#include <h3mtxt/H3MTxtWriter/writeH3mTxt.h>

#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>

namespace fs = std::filesystem;

namespace
{
  // \return true if the specified stream contains a H3M file,
  //         false if it contains a JSON file.
  //         The function doesn't check if the stream contains a valid file.
  bool isH3mFile(std::istream& stream)
  {
    constexpr char kGzipFirstByte = 0x1F;
    constexpr char kH3mUncompressedFirstByte = 0x1C;

    const int first_byte = stream.peek();
    switch (first_byte)
    {
    case kGzipFirstByte:
    case kH3mUncompressedFirstByte:
      return true;
    default:
      return false;
    }
  }
}

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
    if (!stream)
    {
      std::cerr << "Failed to open: " << path_map.string();
      return -1;
    }
    const bool is_h3m_file = isH3mFile(stream);
    const h3m::Map map = is_h3m_file ? h3m::parseh3m(stream) : h3m::readH3mJson(stream);
    stream.close();
    if (is_h3m_file)
    {
      h3m::writeH3mTxt(std::cout, map);
    }
    else
    {
      std::ofstream out_stream("rewritten.h3m", std::ios_base::out | std::ios_base::binary);
      h3m::writeh3m(out_stream, map);
      out_stream.close();
    }
  }
  catch (const std::exception& error)
  {
    std::cerr << error.what() << std::endl;
    return -1;
  }
  catch (...)
  {
    std::cerr << "Unknown error." << std::endl;
    return -1;
  }

  return 0;
}
