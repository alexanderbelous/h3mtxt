#include <h3mtxt/H3JsonWriter/H3SVGJsonWriter/H3SVGJsonWriter.h>

#include <h3mtxt/H3JsonWriter/H3MJsonWriter/Utils.h>
#include <h3mtxt/H3JsonWriter/H3SVGJsonWriter/FixedLengthString.h>
#include <h3mtxt/JsonCommon/FieldNamesH3M.h>
#include <h3mtxt/JsonCommon/FieldNamesH3SVG.h>
#include <h3mtxt/Medea/Medea.h>
#include <h3mtxt/SavedGame/ScenarioStartingInfo.h>

namespace Medea_NS
{
  template<>
  void JsonObjectWriter<h3svg::ScenarioStartingInfo>::operator()(FieldsWriter& out,
                                                                 const h3svg::ScenarioStartingInfo& starting_info) const
  {
    using Fields = h3json::FieldNames<h3svg::ScenarioStartingInfo>;

    out.writeField(Fields::kStartingTowns, starting_info.starting_towns);
    out.writeField(Fields::kUnknown1, starting_info.unknown1);
    out.writeField(Fields::kDifficulty, starting_info.difficulty);
    out.writeField(Fields::kMapFilename, starting_info.map_filename);
    out.writeField(Fields::kMapDirectory, starting_info.map_directory);
    out.writeField(Fields::kPlayersControl, starting_info.players_control);
    out.writeField(Fields::kUnknown2, starting_info.unknown2);
    out.writeField(Fields::kPlayerTurnDuration, starting_info.player_turn_duration);
    out.writeField(Fields::kStartingHeroes, starting_info.starting_heroes);
    out.writeField(Fields::kStartingBonuses, starting_info.starting_bonuses);
    if (starting_info.campaign_info.has_value())
    {
      out.writeField(Fields::kCampaignInfo, *starting_info.campaign_info);
    }
    out.writeField(Fields::kPlaceholderHeroes, starting_info.placeholder_heroes);
  }
}
