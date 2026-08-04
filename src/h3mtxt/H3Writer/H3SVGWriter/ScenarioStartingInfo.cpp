#include <h3mtxt/H3Writer/H3SVGWriter/H3SVGWriter.h>

#include <h3mtxt/H3Writer/H3SVGWriter/Utils.h>
#include <h3mtxt/SavedGame/ScenarioStartingInfo.h>

namespace h3svg
{
  void H3SVGWriter::writeData(const ScenarioStartingInfo& starting_info) const
  {
    writeData(starting_info.starting_towns);
    writeData(starting_info.unknown1);
    writeData(starting_info.difficulty);
    writeData(starting_info.map_filename);
    writeData(starting_info.map_directory);
    writeData(starting_info.players_control);
    writeData(starting_info.unknown2);
    writeData(starting_info.player_turn_duration);
    writeData(starting_info.starting_heroes);
    writeData(starting_info.starting_bonuses);
    writeData(starting_info.campaign_info);
    writeData(safeCastVectorSize<std::uint8_t>(starting_info.placeholder_heroes.size()));
    writeSpan(std::span{ starting_info.placeholder_heroes });
  }
}
