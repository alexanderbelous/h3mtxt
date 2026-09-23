#include <h3mtxt/H3JsonReader/H3SVGJsonReader/H3SVGJsonReader.h>

#include <h3mtxt/H3JsonReader/H3JsonReaderBase/H3JsonReaderBase.h>
#include <h3mtxt/JsonCommon/FieldNamesH3SVG.h>
#include <h3mtxt/SavedGame/Player.h>

namespace h3json
{
  template<>
  h3svg::Player JsonReader<h3svg::Player>::operator()(const Json::Value& value) const
  {
    using Fields = h3json::FieldNames<h3svg::Player>;
    h3svg::Player player;
    readField(player.player_color, value, Fields::kPlayerColor);
    readField(player.num_heroes, value, Fields::kNumHeroes);
    readField(player.active_hero, value, Fields::kActiveHero);
    readField(player.heroes, value, Fields::kHeroes);
    readField(player.heroes_in_tavern, value, Fields::kHeroesInTavern);
    readField(player.unknown1, value, Fields::kUnknown1);
    readField(player.personality, value, Fields::kPersonality);
    readField(player.unknown2, value, Fields::kUnknown2);
    readField(player.days_left, value, Fields::kDaysLeft);
    readField(player.num_towns, value, Fields::kNumTowns);
    readField(player.current_town, value, Fields::kCurrentTown);
    readField(player.towns, value, Fields::kTowns);
    readField(player.resources, value, Fields::kResources);
    readField(player.mystical_gardens, value, Fields::kMysticalGardens);
    readField(player.magic_springs, value, Fields::kMagicSprings);
    readField(player.corpses, value, Fields::kCorpses);
    readField(player.lean_tos, value, Fields::kLeanTos);
    readField(player.unknown3, value, Fields::kUnknown3);
    return player;
  }
}
