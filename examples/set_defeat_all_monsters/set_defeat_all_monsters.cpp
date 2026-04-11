#include <h3mtxt/Map/Map.h>
#include <h3mtxt/H3Reader/H3MReader/parseh3m.h>
#include <h3mtxt/H3Writer/H3MWriter/writeh3m.h>

#include <fstream>
#include <filesystem>
#include <iostream>
#include <stdexcept>

int main(int argc, char** argv)
{
  if (argc != 2)
  {
    std::cout << "Usage: set_defeat_all_monsters <path_to_map>" << std::endl;
    return (argc == 0) ? 0 : -1;
  }

  try
  {
    const std::filesystem::path path_to_map{ argv[1] };

    // Read the map.
    std::fstream stream{ path_to_map, std::ios_base::in | std::ios_base::binary };
    h3m::Map map = h3m::parseh3m(stream);
    stream.close();

    // Change the victory condition to "Defeat All Monsters".
    map.additional_info.victory_condition.details =
      h3m::VictoryConditionDetails<h3m::VictoryConditionType::DefeatAllMonsters>{
        h3m::SpecialVictoryConditionBase{
          .allow_normal_win = false,
          .applies_to_computer = false
        }
      };

    // Write the modified map.
    stream.open(path_to_map, std::ios_base::out | std::ios_base::binary);
    h3m::writeh3m(stream, map);
  }
  catch (const std::exception& error)
  {
    std::cerr << error.what() << std::endl;
    return -1;
  }

  return 0;
}
