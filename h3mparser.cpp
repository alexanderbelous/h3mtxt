#include <h3mparser/parseh3m.h>

#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string_view>

namespace fs = std::filesystem;

namespace
{
  constexpr std::string_view getBoolString(bool value) noexcept
  {
    return value ? "true" : "false";
  }

  template<class T>
  void printH3mStruct(std::ostream& stream, const T& value, std::size_t num_spaces);

  template<>
  void printH3mStruct<h3m::MapBasicInfo>(std::ostream& stream, const h3m::MapBasicInfo& value, std::size_t num_spaces)
  {
    const std::string whitespace(num_spaces, ' ');
    stream << whitespace << "is_playable: " << getBoolString(value.is_playable) << "\n"
           << whitespace << "map_size: " << value.map_size << "\n"
           << whitespace << "has_two_levels: " << getBoolString(value.has_two_levels) << "\n"
           << whitespace << "name: \"" << value.name << "\"\n"
           << whitespace << "description: \"" << value.description << "\"\n"
           << whitespace << "difficulty: " << static_cast<unsigned int>(value.difficulty) << "\n"
           << whitespace << "max_hero_level: " << static_cast<unsigned int>(value.max_hero_level) << "\n";
  }

  template<>
  void printH3mStruct<h3m::MainTown>(std::ostream& stream, const h3m::MainTown& value, std::size_t num_spaces)
  {
    const std::string whitespace(num_spaces, ' ');
    stream << whitespace << "generate_hero: " << getBoolString(value.generate_hero) << "\n"
           << whitespace << "town_type: " << static_cast<unsigned int>(value.town_type) << "\n"
           << whitespace << "x: " << static_cast<unsigned int>(value.x) << "\n"
           << whitespace << "y: " << static_cast<unsigned int>(value.y) << "\n"
           << whitespace << "z: " << static_cast<unsigned int>(value.z) << "\n";
  }

  template<>
  void printH3mStruct<h3m::StartingHero>(std::ostream& stream, const h3m::StartingHero& value, std::size_t num_spaces)
  {
    const std::string whitespace(num_spaces, ' ');
    stream << whitespace << "is_random: " << getBoolString(value.is_random) << "\n"
           << whitespace << "type: " << static_cast<unsigned int>(value.type) << "\n"
           << whitespace << "face: " << static_cast<unsigned int>(value.face) << "\n"
           << whitespace << "name: \"" << value.name << "\"\n";
  }

  template<>
  void printH3mStruct<h3m::AdditionalPlayerInfo::HeroInfo>(std::ostream& stream,
                                                           const h3m::AdditionalPlayerInfo::HeroInfo& value,
                                                           std::size_t num_spaces)
  {
    const std::string whitespace(num_spaces, ' ');
    stream << whitespace << "type: " << static_cast<unsigned int>(value.type) << "\n"
           << whitespace << "name: \"" << value.name << "\"\n";
  }

  template<>
  void printH3mStruct<h3m::AdditionalPlayerInfo>(std::ostream& stream, const h3m::AdditionalPlayerInfo& value, std::size_t num_spaces)
  {
    const std::string whitespace(num_spaces, ' ');
    stream << whitespace << "num_placeholder_heroes: " << static_cast<unsigned int>(value.num_placeholder_heroes) << "\n"
           << whitespace << "heroes: [\n";
    for (const auto& hero : value.heroes)
    {
      stream << whitespace << "  {\n";
      printH3mStruct(stream, hero, num_spaces + 4);
      stream << whitespace << "  }\n";
    }
    stream << whitespace << "]\n";
  }

  template<>
  void printH3mStruct<h3m::PlayerSpecs>(std::ostream& stream, const h3m::PlayerSpecs& value, std::size_t num_spaces)
  {
    const std::string whitespace(num_spaces, ' ');
    stream << whitespace << "can_be_human: " << getBoolString(value.can_be_human) << "\n"
           << whitespace << "can_be_computer: " << getBoolString(value.can_be_computer) << "\n"
           << whitespace << "behavior: " << static_cast<unsigned int>(value.behavior) << "\n"
           << whitespace << "customized_alignments: " << static_cast<unsigned int>(value.customized_alignments) << "\n"
           << whitespace << "town_types: " << static_cast<unsigned int>(value.town_types) << "\n"
           << whitespace << "town_conflux: " << static_cast<unsigned int>(value.town_conflux) << "\n"
           << whitespace << "random_town: " << static_cast<unsigned int>(value.random_town) << "\n";
    if (value.main_town)
    {
      stream << whitespace << "main_town {\n";
      printH3mStruct(stream, *value.main_town, num_spaces + 2);
      stream << whitespace << "}\n";
    }
    stream << whitespace << "starting_hero {\n";
    printH3mStruct(stream, value.starting_hero, num_spaces + 2);
    stream << whitespace << "}\n";
    stream << whitespace << "additional_info {\n";
    printH3mStruct(stream, value.additional_info, num_spaces + 2);
    stream << whitespace << "}\n";
  }

  template<>
  void printH3mStruct<h3m::Map>(std::ostream& stream, const h3m::Map& map, std::size_t num_spaces)
  {
    stream << "format: " << static_cast<unsigned int>(map.format) << "\n";
    stream << "basic_info {\n";
    printH3mStruct(stream, map.basic_info, 2);
    stream << "}\n";
    stream << "players: [\n";
    for (int i = 0; i < h3m::kMaxPlayers; ++i)
    {
      const h3m::PlayerSpecs& player = map.players[i];
      stream << "  # Player " << i << "\n"
             << "  {\n";
      printH3mStruct(stream, player, 4);
      stream << "  }\n";
    }
    stream << "]\n";
    stream << "additional_info {\n";
    stream << "}\n";
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
    std::ifstream stream(path_map, std::ios_base::in | std::ios_base::binary);
    const h3m::Map map = h3m::parseh3m(stream);
    stream.close();
    printH3mStruct(std::cout, map, 0);

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
