#include <h3mtxt/H3Reader/H3SVGReader/H3SVGReader.h>
#include <h3mtxt/SavedGame/Player.h>

namespace h3svg
{
  // Always 145 bytes.
  Player H3SVGReader::readPlayer() const
  {
    Player player;
    player.player_color = readEnum<PlayerColor>();
    player.num_heroes = readInt<std::uint8_t>();
    player.active_hero = readEnum<HeroType>();
    for (HeroType& hero : player.heroes)
    {
      hero = readEnum<HeroType>();
    }
    for (HeroType& hero : player.heroes_in_tavern)
    {
      hero = readEnum<HeroType>();
    }
    player.unknown1 = readInt<std::uint8_t>();
    player.personality = readEnum<PlayerPersonality>();
    player.unknown2 = readByteArray<5>();
    player.days_left = readInt<std::int8_t>();
    player.num_towns = readInt<std::uint8_t>();
    player.current_town = readInt<std::int8_t>();
    for (std::int8_t& town_id : player.towns)
    {
      town_id = readInt<std::uint8_t>();
    }
    player.resources = readResources();
    player.mystical_gardens = readBitSet<4>();
    player.unknown3 = readByteArray<4>();
    player.corpses = readBitSet<4>();
    player.lean_tos = readBitSet<4>();
    player.unknown4 = readByteArray<3>();
    return player;
  }
}
