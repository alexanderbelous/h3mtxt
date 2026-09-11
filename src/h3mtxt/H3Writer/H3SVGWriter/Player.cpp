#include <h3mtxt/H3Writer/H3SVGWriter/H3SVGWriter.h>

#include <h3mtxt/SavedGame/Player.h>

namespace h3svg
{
  void H3SVGWriter::writeData(const Player& player) const
  {
    writeData(player.player_color);
    writeData(player.num_heroes);
    writeData(player.active_hero);
    writeData(player.heroes);
    writeData(player.heroes_in_tavern);
    writeData(player.unknown1);
    writeData(player.personality);
    writeData(player.unknown2);
    writeData(player.days_left);
    writeData(player.num_towns);
    writeData(player.current_town);
    writeData(player.towns);
    writeData(player.resources);
    writeData(player.mystical_gardens);
    writeData(player.magic_springs);
    writeData(player.corpses);
    writeData(player.lean_tos);
    writeData(player.unknown3);
  }
}
