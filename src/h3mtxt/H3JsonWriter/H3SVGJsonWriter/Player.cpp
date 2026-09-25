#include <h3mtxt/H3JsonWriter/H3SVGJsonWriter/H3SVGJsonWriter.h>

#include <h3mtxt/H3JsonWriter/H3MJsonWriter/Utils.h>
#include <h3mtxt/JsonCommon/FieldNamesH3M.h>
#include <h3mtxt/JsonCommon/FieldNamesH3SVG.h>
#include <h3mtxt/Medea/Medea.h>
#include <h3mtxt/SavedGame/Player.h>

namespace Medea_NS
{
  template<>
  void JsonObjectWriter<h3svg::Player>::operator()(FieldsWriter& out,
                                                   const h3svg::Player& player) const
  {
    using Fields = h3json::FieldNames<h3svg::Player>;
    out.writeField(Fields::kPlayerColor, player.player_color);
    out.writeField(Fields::kNumHeroes, player.num_heroes);
    out.writeField(Fields::kActiveHero, player.active_hero);
    out.writeField(Fields::kHeroes, player.heroes);
    out.writeField(Fields::kHeroesInTavern, player.heroes_in_tavern);
    out.writeField(Fields::kUnknown1, player.unknown1);
    out.writeField(Fields::kPersonality, player.personality);
    out.writeField(Fields::kUnknown2, player.unknown2);
    out.writeField(Fields::kDaysLeft, player.days_left);
    out.writeField(Fields::kNumTowns, player.num_towns);
    out.writeField(Fields::kCurrentTown, player.current_town);
    out.writeField(Fields::kTowns, player.towns);
    out.writeField(Fields::kResources, player.resources);
    out.writeField(Fields::kMysticalGardens, player.mystical_gardens);
    out.writeField(Fields::kMagicSprings, player.magic_springs);
    out.writeField(Fields::kCorpses, player.corpses);
    out.writeField(Fields::kLeanTos, player.lean_tos);
    out.writeField(Fields::kUnknown3, player.unknown3);
  }
}
