#include <h3mtxt/H3JsonReader/readH3Json.h>
#include <h3mtxt/H3JsonWriter/H3CJsonWriter/writeH3cJson.h>
#include <h3mtxt/H3JsonWriter/H3MJsonWriter/writeH3mJson.h>
#include <h3mtxt/H3JsonWriter/H3SVGJsonWriter/writeH3SvgJson.h>
#include <h3mtxt/H3Reader/parseh3.h>
#include <h3mtxt/H3Reader/H3SVGReader/parseh3svg.h>
#include <h3mtxt/H3Writer/H3CWriter/writeh3c.h>
#include <h3mtxt/H3Writer/H3MWriter/writeh3m.h>
#include <h3mtxt/Map/Constants/MapFormat.h>
#include <h3mtxt/SavedGame/SavedGame.h>

#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>

namespace fs = std::filesystem;

namespace
{
  // Obtain the version number from H3MTXT_VERSION preprocessor variable.
  // H3MTXT_VERSION is configured in CMakeLists.txt to match the CMake project version.
  #define H3MTXT_STRINGIFY_IMPL(x) #x
  #define H3MTXT_STRINGIFY(x) H3MTXT_STRINGIFY_IMPL(x)
  #ifdef H3MTXT_VERSION
    #define H3MTXT_VERSION_STR H3MTXT_STRINGIFY(H3MTXT_VERSION)
  #else
    #define H3MTXT_VERSION_STR ""
  #endif
  // Version number of h3mtxt, or an empty string if H3MTXT_VERSION is not defined.
  constexpr std::string_view kProgramVersion = H3MTXT_VERSION_STR;
  #undef H3MTXT_VERSION_STR
  #undef H3MTXT_STRINGIFY
  #undef H3MTXT_STRINGIFY_IMPL

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

  // Contents of the input file.
  struct Input
  {
    std::variant<h3m::Map, h3m::Campaign> data;
    // True if the input file is a JSON document, false otherwise.
    bool is_json {};
  };

  // Reads the input file.
  Input readInput(std::istream& stream)
  {
    if (isH3File(stream))
    {
      return Input{ .data = h3m::parseh3(stream), .is_json = false };
    }
    return Input{ .data = h3json::readH3Json(stream), .is_json = true };
  }

  // Writes the output file.
  void writeOutput(std::ostream& stream, const Input& input)
  {
    if (input.is_json)
    {
      if (const h3m::Map* map = std::get_if<h3m::Map>(&input.data))
      {
        h3m::writeh3m(stream, *map);
      }
      else
      {
        h3m::writeh3c(stream, std::get<h3m::Campaign>(input.data));
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

  void runProgram(const fs::path& path_input, const fs::path& path_output)
  {
    std::ifstream stream(path_input, std::ios_base::in | std::ios_base::binary);
    if (!stream)
    {
      throw std::runtime_error("Failed to open: " + path_input.string());
    }
    //const Input input = readInput(stream);

    const h3svg::SavedGame saved_game = h3svg::parseh3svg(stream);
    stream.close();
    std::ofstream out_stream(path_output, std::ios_base::out | std::ios_base::binary);
    if (!out_stream)
    {
      throw std::runtime_error("Failed to open: " + path_output.string());
    }
    h3svg::writeH3SvgJson(out_stream, saved_game);
    //writeOutput(out_stream, input);
    out_stream.close();
  }
}

int main(int argc, char** argv)
{
  if (argc != 3)
  {
    std::cout << "h3mtxt " << kProgramVersion << "\n"
                 "Copyright (c) 2025-2026 Alexander Belous\n"
                 "https://github.com/alexanderbelous/h3mtxt\n"
                 "\n"
                 "Usage: h3mtxt <input_path> <output_path>\n"
                 "\n"
                 "If <input_path> is a .h3m / .h3c file, the program will read it and write it as\n"
                 "a JSON document to <output_path>.\n"
                 "Otherwise, the program will attempt to read <input_path> as a JSON document\n"
                 "and then write it as a .h3m / .h3c file to <output_path>.\n"
                 "\n"
                 "The filename extension in <input_path> is not important - the program will\n"
                 "determine the format from the file data." << std::endl;
    return (argc <= 1) ? EXIT_SUCCESS : EXIT_FAILURE;
  }

  try
  {
    runProgram(argv[1], argv[2]);
  }
  catch (const std::exception& error)
  {
    std::cerr << error.what() << std::endl;
    return EXIT_FAILURE;
  }
  catch (...)
  {
    std::cerr << "Unknown error." << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
