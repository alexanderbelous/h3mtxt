#include <h3mparser/parseh3m.h>

#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>

namespace fs = std::filesystem;

namespace
{
  void printMapInfo(std::ostream& stream, const h3m::Map& map)
  {
    stream << "format: " << static_cast<unsigned int>(map.format) << "\n"
           << "is_playable: " << (map.basic_info.is_playable ? "true" : "false") << "\n"
           << "map_size: " << map.basic_info.map_size << "\n"
           << "has_two_levels: " << (map.basic_info.has_two_levels ? "true" : "false") << "\n"
           << "name: \"" << map.basic_info.name << "\"\n"
           << "description: \"" << map.basic_info.description << "\"\n"
           << "difficulty: " << static_cast<unsigned int>(map.basic_info.difficulty) << "\n"
           << "max_hero_level: " << static_cast<unsigned int>(map.basic_info.max_hero_level) << std::endl;
    stream << "players: [\n";
    for (int i = 0; i < h3m::kMaxPlayers; ++i)
    {
      const h3m::PlayerSpecs& player = map.players[i];
      stream << "  # Player " << i << "\n"
             << "  {\n"
             << "    can_be_human: " << (player.can_be_human ? "true" : "false") << "\n"
             << "    can_be_computer: " << (player.can_be_computer ? "true" : "false") << "\n"
             << "    behavior: " << static_cast<unsigned int>(player.behavior) << "\n"
             << "    customized_alignments: " << static_cast<unsigned int>(player.customized_alignments) << "\n"
             << "    town_types: " << static_cast<unsigned int>(player.town_types) << "\n"
             << "    town_conflux: " << static_cast<unsigned int>(player.town_conflux) << "\n"
             << "    random_town: " << static_cast<unsigned int>(player.random_town) << "\n";

      if (player.main_town)
      {
        const h3m::MainTown& main_town = *player.main_town;
        stream << "    main_town {\n"
               << "      generate_hero: " << (main_town.generate_hero ? "true" : "false") << "\n"
               << "      town_type: " << static_cast<unsigned int>(main_town.town_type) << "\n"
               << "      x: " << static_cast<unsigned int>(main_town.x) << "\n"
               << "      y: " << static_cast<unsigned int>(main_town.y) << "\n"
               << "      z: " << static_cast<unsigned int>(main_town.z) << "\n"
               << "    }\n";
      }
      stream << "  }\n";
    }
    stream << "]\n";
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
    printMapInfo(std::cout, map);

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
