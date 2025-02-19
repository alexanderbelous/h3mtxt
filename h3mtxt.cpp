#include <h3mtxt/Campaign/Constants/CampaignFormat.h>
#include <h3mtxt/H3MJsonReader/readH3mJson.h>
#include <h3mtxt/H3MJsonWriter/writeH3mJson.h>
#include <h3mtxt/H3MReader/parseh3m.h>
#include <h3mtxt/H3MWriter/writeh3m.h>
#include <h3mtxt/Map/Constants/MapFormat.h>

#include <h3mtxt/thirdparty/zstr/src/zstr.hpp>

#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>

namespace fs = std::filesystem;

namespace
{
  enum class FileType
  {
    GZip,
    UncompressedH3M,
    UncompressedH3C,
    Other
  };

  // Determines the type of the file by reading the 0th byte without extracting it.
  // \param stream - input stream containing the file data.
  // \return FileType for the file contained in @stream.
  FileType getFileType(std::istream& stream)
  {
    constexpr char kGzipFirstByte = 0x1F;

    const int first_byte = stream.peek();
    switch (first_byte)
    {
    case kGzipFirstByte:
      return FileType::GZip;
    case static_cast<std::uint8_t>(h3m::MapFormat::RestorationOfErathia):
    case static_cast<std::uint8_t>(h3m::MapFormat::ArmageddonsBlade):
    case static_cast<std::uint8_t>(h3m::MapFormat::ShadowOfDeath):
      return FileType::UncompressedH3M;
    case static_cast<std::uint8_t>(h3m::CampaignFormat::RestorationOfErathia):
    case static_cast<std::uint8_t>(h3m::CampaignFormat::ArmageddonsBlade):
    case static_cast<std::uint8_t>(h3m::CampaignFormat::ShadowOfDeath):
      return FileType::UncompressedH3C;
    default:
      return FileType::Other;
    }
  }

  struct Input
  {
    // TODO: replace with std::variant<h3m::Map, h3m::Campaign>.
    h3m::Map map;
    // True if the input file is a JSON document, false otherwise.
    bool is_json {};
  };

  // Reads a h3m::Map or a h3m::Campaign from the input stream.
  // TODO: change the type of the returned value to std::variant<h3m::Map, h3m::Campaign>.
  h3m::Map readUncompressedH3(std::istream& stream)
  {
    switch (getFileType(stream))
    {
    case FileType::UncompressedH3M:
      return h3m::parseh3m(stream);
    case FileType::UncompressedH3C:
      throw std::runtime_error(".h3c files are not supported yet.");
    default:
      throw std::runtime_error("Unknown file format.");
    }
  }

  Input readInput(std::istream& stream)
  {
    const FileType file_type = getFileType(stream);
    switch (file_type)
    {
    case FileType::GZip:
    {
      zstr::istream zstr_stream(stream);
      return Input{ .map = readUncompressedH3(zstr_stream), .is_json = false };
    }
    case FileType::UncompressedH3C:
    case FileType::UncompressedH3M:
      return Input{ .map = readUncompressedH3(stream), .is_json = false };
    default:
      return Input{ .map = h3m::readH3mJson(stream), .is_json = true };
    }
  }

  void writeOutput(std::ostream& stream, const Input& input)
  {
    if (input.is_json)
    {
      h3m::writeh3m(stream, input.map);
    }
    else
    {
      h3m::writeH3mJson(stream, input.map);
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
