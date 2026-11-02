#include <h3mtxt/H3JsonReader/H3MJsonReader/H3MJsonReader.h>

#include <h3mtxt/H3JsonReader/H3JsonReaderBase/H3JsonReaderBase.h>
#include <h3mtxt/JsonCommon/FieldNamesH3M.h>
#include <h3mtxt/Map/PlayerSpecs.h>

namespace h3json
{
  template<>
  h3m::PlayerSpecs::HeroInfo JsonReader2<h3m::PlayerSpecs::HeroInfo>::operator()() const
  {
    h3m::PlayerSpecs::HeroInfo info;
    readField("type", info.type);
    readField("name", info.name);
    return info;
  }

  template<>
  h3m::MainTown JsonReader2<h3m::MainTown>::operator()() const
  {
    using Fields = FieldNames<h3m::MainTown>;
    h3m::MainTown main_town;
    readField(Fields::kGenerateHero, main_town.generate_hero);
    readField(Fields::kTownType, main_town.town_type);
    readField(Fields::kCoordinates, main_town.coordinates);
    return main_town;
  }

  template<>
  h3m::StartingHero JsonReader2<h3m::StartingHero>::operator()() const
  {
    using Fields = FieldNames<h3m::StartingHero>;
    h3m::StartingHero hero;
    readField(Fields::kType, hero.type);
    if (hero.type != h3m::HeroType{0xFF})
    {
      readField(Fields::kPortrait, hero.portrait);
      readField(Fields::kName, hero.name);
    }
    return hero;
  }

  template<>
  h3m::PlayerSpecs JsonReader2<h3m::PlayerSpecs>::operator()() const
  {
    using Fields = FieldNames<h3m::PlayerSpecs>;
    h3m::PlayerSpecs player;
    readField(Fields::kCanBeHuman, player.can_be_human);
    readField(Fields::kCanBeComputer, player.can_be_computer);
    readField(Fields::kBehavior, player.behavior);
    readField(Fields::kHasCustomizedAlignments, player.has_customized_alignments);
    readField(Fields::kAllowedAlignments, player.allowed_alignments);
    readField(Fields::kAllowRandomAlignment, player.allow_random_alignment);
    readField(Fields::kMainTown, player.main_town);
    readField(Fields::kHasRandomHeroes, player.has_random_heroes);
    readField(Fields::kStartingHero, player.starting_hero);
    readField(Fields::kNumNonspecificPlaceholderHeroes, player.num_nonspecific_placeholder_heroes);
    readField(Fields::kHeroes, player.heroes);
    return player;
  }
}
