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
  if (argc != 3)
  {
    std::cout << "Usage: h3mtxt <input_path> <output_path>\n"
                 "\n"
                 "If <input_path> is a .h3m file, the program will read the map and write it as a\n"
                 "JSON document to <output_path>.\n"
                 "Otherwise, the program will attempt to read <input_path> as a JSON document\n"
                 "representing a H3M map, and then write it as .h3m file to <output_path>.\n"
                 "\n"
                 "The filename extension in <input_path> is not important - the program will\n"
                 "determine the format from the file data." << std::endl;
    return -1;
  }

  try
  {
    const fs::path path_input(argv[1]);
    const fs::path path_output(argv[2]);
    std::ifstream stream(path_input, std::ios_base::in | std::ios_base::binary);
    if (!stream)
    {
      std::cerr << "Failed to open: " << path_input.string();
      return -1;
    }
    const bool is_h3m_file = isH3mFile(stream);
    const h3m::Map map = is_h3m_file ? h3m::parseh3m(stream) : h3m::readH3mJson(stream);
    stream.close();
    std::ofstream out_stream(path_output, std::ios_base::out | std::ios_base::binary);
    if (!out_stream)
    {
      std::cerr << "Failed to open: " << path_output.string();
      return -1;
    }
    if (is_h3m_file)
    {
      h3m::writeH3mTxt(out_stream, map);
    }
    else
    {
      h3m::writeh3m(out_stream, map);
    }
    out_stream.close();
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
