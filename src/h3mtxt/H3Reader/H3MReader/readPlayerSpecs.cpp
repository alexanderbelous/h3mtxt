#include <h3mtxt/H3Reader/H3MReader/H3MReader.h>
#include <h3mtxt/Map/Utils/FeatureTesting.h>
#include <h3mtxt/Map/PlayerSpecs.h>

namespace h3m
{
  namespace
  {
    PlayerSpecs::HeroInfo readPlayerSpecsHeroInfo(const H3MReader& reader)
    {
      PlayerSpecs::HeroInfo hero;
      hero.type = reader.readEnum<HeroType>();
      hero.name = reader.readString32();
      return hero;
    }
  }

  MainTown H3MReader::readMainTown() const
  {
    MainTown main_town;
    if (FeatureTesting{ map_format_ }.generateHeroAtMainTown())
    {
      main_town.generate_hero = readBool();
    }
    if (FeatureTesting{ map_format_ }.mainTownType())
    {
      main_town.town_type = readEnum<TownType>();
    }
    main_town.coordinates = readCoordinates();
    return main_town;
  }

  StartingHero H3MReader::readStartingHero() const
  {
    StartingHero starting_hero;
    starting_hero.type = readEnum<HeroType>();
    if (starting_hero.type != HeroType{0xFF})
    {
      starting_hero.portrait = readEnum<HeroPortrait>();
      starting_hero.name = readString32();
    }
    return starting_hero;
  }

  PlayerSpecs H3MReader::readPlayerSpecs() const
  {
    PlayerSpecs player;
    player.can_be_human = readBool();
    player.can_be_computer = readBool();
    player.behavior = readEnum<PlayerBehavior>();
    if (FeatureTesting{ map_format_ }.customizedAlignments())
    {
      player.has_customized_alignments = readInt<std::uint8_t>();
    }
    player.allowed_alignments =
      readEnumBitmask<TownType, 2>(FeatureTesting{ map_format_ }.getBitmaskSize<TownsBitmask>());
    player.allow_random_alignment = readInt<std::uint8_t>();
    const bool has_main_town = readBool();
    if (has_main_town)
    {
      player.main_town = readMainTown();
    }
    player.has_random_heroes = readBool();
    player.starting_hero = readStartingHero();
    if (FeatureTesting{ map_format_ }.numNonspecificPlaceholderHeroes())
    {
      player.num_nonspecific_placeholder_heroes = readInt<std::uint8_t>();
    }
    if (FeatureTesting{ map_format_ }.startingHeroes())
    {
      const std::uint32_t num_heroes = readInt<std::uint32_t>();
      player.heroes.reserve(num_heroes);
      for (std::uint32_t i = 0; i < num_heroes; ++i)
      {
        player.heroes.push_back(readPlayerSpecsHeroInfo(*this));
      }
    }
    return player;
  }
}
