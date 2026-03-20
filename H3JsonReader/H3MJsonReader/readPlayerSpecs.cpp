#include <h3mtxt/H3JsonReader/H3MJsonReader/H3MJsonReader.h>

#include <h3mtxt/H3JsonReader/H3JsonReaderBase/H3JsonReaderBase.h>
#include <h3mtxt/JsonCommon/FieldNamesH3M.h>
#include <h3mtxt/Map/PlayerSpecs.h>

namespace h3json
{
  template<>
  struct JsonReader<h3m::PlayerSpecs::HeroInfo>
  {
    h3m::PlayerSpecs::HeroInfo operator()(const Json::Value& value) const
    {
      h3m::PlayerSpecs::HeroInfo info{};
      readField(info.type, value, "type");
      readField(info.name, value, "name");
      return info;
    }
  };

  h3m::MainTown JsonReader<h3m::MainTown>::operator()(const Json::Value& value) const
  {
    using Fields = FieldNames<h3m::MainTown>;
    h3m::MainTown main_town {};
    readField(main_town.generate_hero, value, Fields::kGenerateHero);
    readField(main_town.town_type, value, Fields::kTownType);
    readField(main_town.coordinates, value, Fields::kCoordinates);
    return main_town;
  }

  h3m::StartingHero JsonReader<h3m::StartingHero>::operator()(const Json::Value& value) const
  {
    using Fields = FieldNames<h3m::StartingHero>;
    h3m::StartingHero hero {};
    readField(hero.type, value, Fields::kType);
    if (hero.type != h3m::HeroType{0xFF})
    {
      readField(hero.portrait, value, Fields::kPortrait);
      readField(hero.name, value, Fields::kName);
    }
    return hero;
  }

  h3m::PlayerSpecs JsonReader<h3m::PlayerSpecs>::operator()(const Json::Value& value) const
  {
    using Fields = FieldNames<h3m::PlayerSpecs>;
    h3m::PlayerSpecs player {};
    readField(player.can_be_human, value, Fields::kCanBeHuman);
    readField(player.can_be_computer, value, Fields::kCanBeComputer);
    readField(player.behavior, value, Fields::kBehavior);
    readField(player.has_customized_alignments, value, Fields::kHasCustomizedAlignments);
    readField(player.allowed_alignments, value, Fields::kAllowedAlignments);
    readField(player.allow_random_alignment, value, Fields::kAllowRandomAlignment);
    readField(player.main_town, value, Fields::kMainTown);
    readField(player.has_random_heroes, value, Fields::kHasRandomHeroes);
    readField(player.starting_hero, value, Fields::kStartingHero);
    readField(player.num_nonspecific_placeholder_heroes, value, Fields::kNumNonspecificPlaceholderHeroes);
    readField(player.heroes, value, Fields::kHeroes);
    return player;
  }
}
