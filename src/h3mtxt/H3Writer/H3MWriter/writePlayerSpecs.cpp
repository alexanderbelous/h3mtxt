#include <h3mtxt/H3Writer/H3MWriter/H3MWriter.h>
#include <h3mtxt/Map/PlayerSpecs.h>

namespace h3m
{
  void H3MWriter::writeData(const MainTown& value) const
  {
    writeData(value.generate_hero);
    writeData(value.town_type);
    writeData(value.coordinates);
  }

  void H3MWriter::writeData(const StartingHero& value) const
  {
    writeData(value.type);
    if (value.type != HeroType{0xFF})
    {
      writeData(value.portrait);
      writeData(value.name);
    }
  }

  void H3MWriter::writeData(const PlayerSpecs& value) const
  {
    writeData(value.can_be_human);
    writeData(value.can_be_computer);
    writeData(value.behavior);
    writeData(value.has_customized_alignments);
    writeData(value.allowed_alignments);
    writeData(value.allow_random_alignment);
    writeData(value.main_town);
    writeData(value.has_random_heroes);
    writeData(value.starting_hero);
    writeData(value.num_nonspecific_placeholder_heroes);
    writeData(safeCastVectorSize<std::uint32_t>(value.heroes.size()));
    for (const h3m::PlayerSpecs::HeroInfo& hero : value.heroes)
    {
      writeData(hero.type);
      writeData(hero.name);
    }
  }
}
