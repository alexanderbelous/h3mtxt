#include <h3mtxt/H3JsonReader/Utils.h>
#include <h3mtxt/JsonCommon/FieldName.h>
#include <h3mtxt/Map/PlayerSpecs.h>

namespace h3m::H3JsonReader_NS
{
  template<>
  struct JsonReader<PlayerSpecs::HeroInfo>
  {
    PlayerSpecs::HeroInfo operator()(const Json::Value& value) const
    {
      PlayerSpecs::HeroInfo info{};
      info.type = readField<HeroType>(value, "type");
      info.name = readField<std::string>(value, "name");
      return info;
    }
  };

  MainTown JsonReader<MainTown>::operator()(const Json::Value& value) const
  {
    using Fields = FieldNames<MainTown>;
    MainTown main_town {};
    readField(main_town.generate_hero, value, Fields::kGenerateHero);
    readField(main_town.town_type, value, Fields::kTownType);
    readField(main_town.x, value, Fields::kX);
    readField(main_town.y, value, Fields::kY);
    readField(main_town.z, value, Fields::kZ);
    return main_town;
  }

  StartingHero JsonReader<StartingHero>::operator()(const Json::Value& value) const
  {
    using Fields = FieldNames<StartingHero>;
    StartingHero hero {};
    readField(hero.type, value, Fields::kType);
    if (hero.type != HeroType{0xFF})
    {
      readField(hero.portrait, value, Fields::kPortrait);
      readField(hero.name, value, Fields::kName);
    }
    return hero;
  }

  PlayerSpecs JsonReader<PlayerSpecs>::operator()(const Json::Value& value) const
  {
    using Fields = FieldNames<PlayerSpecs>;
    PlayerSpecs player {};
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
