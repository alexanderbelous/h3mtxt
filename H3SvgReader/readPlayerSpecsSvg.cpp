#include <h3mtxt/H3SvgReader/H3SvgReader.h>
#include <h3mtxt/H3SvgReader/Utils.h>
#include <h3mtxt/H3Reader/H3Reader.h>
#include <h3mtxt/H3Reader/Utils.h>
#include <h3mtxt/SavedGame/PlayerSpecsSvg.h>

namespace h3m::H3SvgReader_NS
{
  using H3Reader_NS::readBool;
  using H3Reader_NS::readEnum;
  using H3Reader_NS::readEnumBitmask;
  using H3Reader_NS::readInt;
  using H3Reader_NS::readReservedData;

  Coordinates readCoordinates(std::istream& stream)
  {
    Coordinates result;
    result.x = readInt<std::uint8_t>(stream);
    result.y = readInt<std::uint8_t>(stream);
    result.z = readInt<std::uint8_t>(stream);
    return result;
  }

  StartingHero readStartingHeroSvg(std::istream& stream)
  {
    StartingHero starting_hero;
    starting_hero.type = readEnum<HeroType>(stream);
    if (starting_hero.type != HeroType{ 0xFF })
    {
      starting_hero.portrait = readEnum<HeroPortrait>(stream);
      starting_hero.name = readString16(stream);
    }
    return starting_hero;
  }

  PlayerSpecsSvg readPlayerSpecsSvg(std::istream& stream)
  {
    PlayerSpecsSvg player;
    player.can_be_human = readBool(stream);
    player.can_be_computer = readBool(stream);
    player.behavior = readEnum<PlayerBehavior>(stream);
    player.allowed_alignments = readEnumBitmask<TownType, 2>(stream);
    player.allow_random_alignment = readBool(stream);
    const Bool has_generated_hero = readBool(stream);
    if (has_generated_hero)
    {
      player.generated_hero_coordinates = readCoordinates(stream);
    }
    player.starting_hero = readStartingHeroSvg(stream);
    return player;
  }
}
