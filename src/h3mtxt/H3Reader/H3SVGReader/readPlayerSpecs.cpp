#include <h3mtxt/H3Reader/H3SVGReader/H3SVGReader.h>
#include <h3mtxt/SavedGame/PlayerSpecs.h>

namespace h3svg
{
  StartingHero H3SVGReader::readStartingHero() const
  {
    StartingHero starting_hero;
    starting_hero.type = readEnum<HeroType>();
    if (starting_hero.type != HeroType{ 0xFF })
    {
      starting_hero.portrait = readEnum<HeroPortrait>();
      starting_hero.name = readString16();
    }
    return starting_hero;
  }

  PlayerSpecs H3SVGReader::readPlayerSpecs() const
  {
    PlayerSpecs player;
    player.can_be_human = readBool();
    player.can_be_computer = readBool();
    player.behavior = readEnum<PlayerBehavior>();
    player.allowed_alignments = readEnumBitmask<TownType, 2>();
    player.allow_random_alignment = readBool();
    const Bool has_generated_hero = readBool();
    if (has_generated_hero)
    {
      player.generated_hero_coordinates = readCoordinates();
    }
    player.starting_hero = readStartingHero();
    return player;
  }
}
