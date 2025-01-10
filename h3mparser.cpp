#include <h3mparser/Map.h>

#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <type_traits>

namespace fs = std::filesystem;

namespace
{
  std::uint8_t readUint8(std::istream& stream)
  {
    using Traits = std::istream::traits_type;
    if (!stream)
    {
      throw std::logic_error("Error in the input stream.");
    }
    const Traits::int_type character = stream.get();
    if (character == Traits::eof())
    {
      throw std::runtime_error("Unexpected end of stream.");
    }
    return static_cast<std::uint8_t>(character);
  }

  // Reads a little-endian unsigned integer.
  std::uintmax_t readUintImpl(std::istream& stream, unsigned int num_bytes)
  {
    std::uintmax_t result = 0;
    std::uintmax_t shift = 0;
    for (unsigned int i = 0; i < num_bytes; ++i)
    {
      const std::uint8_t byte = readUint8(stream);
      result |= (static_cast<std::uintmax_t>(byte) << shift);
      shift += 8;
    }
    return result;
  }

  // Reads a little-endian unsigned integer.
  template<class T>
  T readUint(std::istream& stream)
  {
    static_assert(std::is_integral_v<T>, "T must be an integral type.");
    constexpr int kNumBytes = sizeof(T);
    // TODO: this is probably buggy for signed integers. Cast to a smaller unsigned type first.
    return static_cast<T>(readUintImpl(stream, kNumBytes));
  }

  bool readBool(std::istream& stream)
  {
    return static_cast<bool>(readUint8(stream));
  }

  template<class T>
  T readEnum(std::istream& stream)
  {
    return static_cast<T>(readUint<std::underlying_type_t<T>>(stream));
  }

  std::string readString(std::istream& stream)
  {
    const std::uint32_t length = readUint<std::uint32_t>(stream);
    std::string result;
    result.reserve(length);
    for (std::uint32_t i = 0; i < length; ++i)
    {
      result.push_back(static_cast<char>(readUint8(stream)));
    }
    return result;
  }

  h3m::Map readMap(std::istream& stream)
  {
    h3m::Map map;
    map.format = readEnum<h3m::MapFormat>(stream);
    map.basic_info.is_playable = readBool(stream);
    map.basic_info.map_size = readUint<std::uint32_t>(stream);
    map.basic_info.has_two_levels = readBool(stream);
    map.basic_info.name = readString(stream);
    map.basic_info.description = readString(stream);
    map.basic_info.difficulty = readEnum<h3m::MapDifficulty>(stream);
    map.basic_info.max_hero_level = readUint8(stream);
    return map;
  }
}

int main(int argc, char** argv)
{
  if (argc != 2) {
    std::cout << "Usage: h3mparser map-path" << std::endl;
    return -1;
  }

  try
  {
    const fs::path path_map(argv[1]);
    std::ifstream stream(path_map);
    const h3m::Map map = readMap(stream);
    stream.close();
    std::cout << "format: " << static_cast<unsigned int>(map.format) << "\n"
              << "is_playable: " << (map.basic_info.is_playable ? "true" : "false") << "\n"
              << "map_size: " << map.basic_info.map_size << "\n"
              << "has_two_levels: " << (map.basic_info.has_two_levels ? "true" : "false") << "\n"
              << "name: \"" << map.basic_info.name << "\"\n"
              << "description: \"" << map.basic_info.description << "\"\n"
              << "difficulty: " << static_cast<unsigned int>(map.basic_info.difficulty) << "\n"
              << "max_hero_level: " << static_cast<unsigned int>(map.basic_info.max_hero_level) << std::endl;
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
