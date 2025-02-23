#include <h3mtxt/H3MJsonReader/readH3mJson.h>
#include <h3mtxt/H3MJsonWriter/writeH3cJson.h>
#include <h3mtxt/H3MJsonWriter/writeH3mJson.h>
#include <h3mtxt/H3Reader/parseh3.h>
#include <h3mtxt/H3Writer/writeh3c.h>
#include <h3mtxt/H3Writer/writeh3m.h>
#include <h3mtxt/Map/Constants/MapFormat.h>

#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>

namespace fs = std::filesystem;

namespace
{
  // Checks if the input file is a (possibly gzip-compressed) .h3m or .h3c file.
  // \param stream - input stream containing the file data.
  // \return true if @stream contains a (possibly gzip-compressed) .h3m or .h3c file, false otherwise.
  bool isH3File(std::istream& stream)
  {
    constexpr char kGzipFirstByte = 0x1F;
    const int first_byte = stream.peek();
    switch (first_byte)
    {
    case kGzipFirstByte:
    case static_cast<std::uint8_t>(h3m::MapFormat::RestorationOfErathia):
    case static_cast<std::uint8_t>(h3m::MapFormat::ArmageddonsBlade):
    case static_cast<std::uint8_t>(h3m::MapFormat::ShadowOfDeath):
      return true;
    default:
      return false;
    }
  }

  struct Input
  {
    std::variant<h3m::Map, h3m::Campaign> data;
    // True if the input file is a JSON document, false otherwise.
    bool is_json {};
  };

  Input readInput(std::istream& stream)
  {
    if (isH3File(stream))
    {
      return Input{ .data = h3m::H3Reader_NS::parseh3(stream), .is_json = false };
    }
    // TODO: add support for reading .h3c.json files.
    return Input{ .data = h3m::readH3mJson(stream), .is_json = true };
  }

  void writeOutput(std::ostream& stream, const Input& input)
  {
    if (input.is_json)
    {
      if (const h3m::Map* map = std::get_if<h3m::Map>(&input.data))
      {
        h3m::H3Writer_NS::writeh3m(stream, *map);
      }
      else
      {
        h3m::H3Writer_NS::writeh3c(stream, std::get<h3m::Campaign>(input.data));
      }
    }
    else
    {
      if (const h3m::Map* map = std::get_if<h3m::Map>(&input.data))
      {
        h3m::writeH3mJson(stream, *map);
      }
      else
      {
        h3m::writeH3cJson(stream, std::get<h3m::Campaign>(input.data));
      }
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
    const Input input = readInput(stream);
    stream.close();
    std::ofstream out_stream(path_output, std::ios_base::out | std::ios_base::binary);
    if (!out_stream)
    {
      std::cerr << "Failed to open: " << path_output.string();
      return -1;
    }
    writeOutput(out_stream, input);
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
