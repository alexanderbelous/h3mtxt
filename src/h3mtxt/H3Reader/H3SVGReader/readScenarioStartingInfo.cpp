#include <h3mtxt/H3Reader/H3SVGReader/H3SVGReader.h>
#include <h3mtxt/SavedGame/ScenarioStartingInfo.h>

namespace h3svg
{
  ScenarioStartingInfo H3SVGReader::readScenarioStartingInfo() const
  {
    ScenarioStartingInfo starting_info;
    // Read 32 bytes - 4 bytes per player, specifying their alignment.
    for (TownType32& alignment : starting_info.starting_towns.data)
    {
      alignment = readEnum<TownType32>();
    }
    // Read 8 bytes.
    // TODO: figure out what it is.
    readBytes(std::span<std::byte, 8>{ starting_info.unknown1 });
    // Read 1 byte - the selected difficulty level.
    starting_info.difficulty = readEnum<MapDifficulty>();
    // Read 251 bytes representing the filename of the original map.
    readBytes(std::as_writable_bytes(std::span{ starting_info.map_filename }));
    // Read 100 bytes representing the relative path to the directory in which the original map is located.
    readBytes(std::as_writable_bytes(std::span{ starting_info.map_directory }));
    // Read 8 bytes - 1 byte per PlayerColor, indicating who can control this color.
    for (PlayerControlType& player_control : starting_info.players_control.data)
    {
      player_control = readEnum<PlayerControlType>();
    }
    // Read 3 bytes.
    // TODO: figure out what this is. Seems to always be {255, 1, 1}.
    readBytes(std::span<std::byte, 3>{ starting_info.unknown2 });
    // Read 1 byte specifying the player turn duration.
    starting_info.player_turn_duration = readEnum<PlayerTurnDurationType>();
    // Read 8 bytes - 1 byte per player, specifying the starting hero.
    for (HeroType& starting_hero : starting_info.starting_heroes.data)
    {
      starting_hero = readEnum<HeroType>();
    }
    // Read 8 bytes - 1 byte per player, specifying the starting bonus.
    for (PlayerStartingBonusType& starting_bonus : starting_info.starting_bonuses.data)
    {
      starting_bonus = readEnum<PlayerStartingBonusType>();
    }
    // Read 1 byte indicating if this is a campaign scenario.
    const Bool has_campaign_info = readBool();
    if (has_campaign_info)
    {
      starting_info.campaign_info = readCampaignInfo();
    }
    // Read crossover heroes.
    {
      const std::uint8_t num_crossover_heroes = readInt<std::uint8_t>();
      starting_info.crossover_heroes.reserve(num_crossover_heroes);
      for (std::size_t i = 0; i < num_crossover_heroes; ++i)
      {
        starting_info.crossover_heroes.push_back(readHero());
      }
    }
    return starting_info;
  }
}
