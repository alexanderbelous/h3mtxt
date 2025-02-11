#pragma once

#include <h3mtxt/H3MWriter/H3MWriter.h>
#include <h3mtxt/Map/PlayerSpecs.h>

namespace h3m
{
  template<>
  struct H3MWriter<MainTown>
  {
    void operator()(std::ostream& stream, const MainTown& value) const
    {
      writeData(stream, value.generate_hero);
      writeData(stream, value.town_type);
      writeData(stream, value.x);
      writeData(stream, value.y);
      writeData(stream, value.z);
    }
  };

  template<>
  struct H3MWriter<StartingHero>
  {
    void operator()(std::ostream& stream, const StartingHero& value) const
    {
      writeData(stream, value.type);
      if (value.type != HeroType{0xFF})
      {
        writeData(stream, value.portrait);
        writeData(stream, value.name);
      }
    }
  };

  template<>
  struct H3MWriter<PlayerSpecs::HeroInfo>
  {
    void operator()(std::ostream& stream, const PlayerSpecs::HeroInfo& value) const
    {
      writeData(stream, value.type);
      writeData(stream, value.name);
    }
  };

  template<>
  struct H3MWriter<PlayerSpecs>
  {
    void operator()(std::ostream& stream, const PlayerSpecs& value) const
    {
      writeData(stream, value.can_be_human);
      writeData(stream, value.can_be_computer);
      writeData(stream, value.behavior);
      writeData(stream, value.customized_alignments);
      writeData(stream, value.allowed_alignments.bitset);
      writeData(stream, value.random_town);
      writeData(stream, value.main_town);
      writeData(stream, value.has_random_heroes);
      writeData(stream, value.starting_hero);
      writeData(stream, value.num_nonspecific_placeholder_heroes);
      writeVector<std::uint32_t>(stream, value.heroes);
    }
  };
}
