#include <h3mtxt/H3Writer/H3SVGWriter/H3SVGWriter.h>

#include <h3mtxt/SavedGame/PlayerSpecs.h>

namespace h3svg
{
  void H3SVGWriter::writeData(const StartingHero& starting_hero) const
  {
    writeData(starting_hero.type);
    if (starting_hero.type != HeroType{ 0xFF })
    {
      writeData(starting_hero.portrait);
      writeString16(starting_hero.name);
    }
  }

  void H3SVGWriter::writeData(const PlayerSpecs& player) const
  {
    writeData(player.can_be_human);
    writeData(player.can_be_computer);
    writeData(player.behavior);
    writeData(player.allowed_alignments);
    writeData(player.allow_random_alignment);
    writeData(player.generated_hero_coordinates);
    writeData(player.starting_hero);
  }
}
