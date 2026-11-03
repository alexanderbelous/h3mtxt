#include <h3mtxt/H3JsonReader/H3SVGJsonReader/H3SVGJsonReader.h>

#include <h3mtxt/H3JsonReader/H3JsonReaderBase/H3JsonReaderBase.h>
#include <h3mtxt/JsonCommon/FieldNamesH3SVG.h>
#include <h3mtxt/SavedGame/Player.h>

namespace h3json
{
  template<>
  h3svg::Player JsonReader2<h3svg::Player>::operator()() const
  {
    using Fields = h3json::FieldNames<h3svg::Player>;
    h3svg::Player player;
    readField(Fields::kPlayerColor, player.player_color);
    readField(Fields::kNumHeroes, player.num_heroes);
    readField(Fields::kActiveHero, player.active_hero);
    readField(Fields::kHeroes, player.heroes);
    readField(Fields::kHeroesInTavern, player.heroes_in_tavern);
    readField(Fields::kUnknown1, player.unknown1);
    readField(Fields::kPersonality, player.personality);
    readField(Fields::kUnknown2, player.unknown2);
    readField(Fields::kGrailGuess, player.grail_guess);
    readField(Fields::kDaysLeft, player.days_left);
    readField(Fields::kNumTowns, player.num_towns);
    readField(Fields::kCurrentTown, player.current_town);
    readField(Fields::kTowns, player.towns);
    readField(Fields::kResources, player.resources);
    readField(Fields::kMysticalGardens, player.mystical_gardens);
    readField(Fields::kMagicSprings, player.magic_springs);
    readField(Fields::kCorpses, player.corpses);
    readField(Fields::kLeanTos, player.lean_tos);
    readField(Fields::kShowTacticsMessage, player.show_tactics_message);
    readField(Fields::kUnknown3, player.unknown3);
    return player;
  }
}
