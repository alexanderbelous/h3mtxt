#include <h3mtxt/H3JsonReader/H3SVGJsonReader/H3SVGJsonReader.h>

#include <h3mtxt/H3JsonReader/H3JsonReaderBase/H3JsonReaderBase.h>
#include <h3mtxt/H3JsonReader/H3SVGJsonReader/FixedLengthString.h>
#include <h3mtxt/JsonCommon/FieldNamesH3SVG.h>
#include <h3mtxt/SavedGame/ScenarioStartingInfo.h>

namespace h3json
{
  template<>
  h3svg::ScenarioStartingInfo JsonReader2<h3svg::ScenarioStartingInfo>::operator()() const
  {
    using Fields = h3json::FieldNames<h3svg::ScenarioStartingInfo>;
    h3svg::ScenarioStartingInfo starting_info;
    readField(Fields::kStartingTowns, starting_info.starting_towns);
    readField(Fields::kPlayerTypes, starting_info.player_types);
    readField(Fields::kDifficulty, starting_info.difficulty);
    readField(Fields::kMapFilename, starting_info.map_filename);
    readField(Fields::kMapDirectory, starting_info.map_directory);
    readField(Fields::kPlayersControl, starting_info.players_control);
    readField(Fields::kUnknown, starting_info.unknown);
    readField(Fields::kPlayerTurnDuration, starting_info.player_turn_duration);
    readField(Fields::kStartingHeroes, starting_info.starting_heroes);
    readField(Fields::kStartingBonuses, starting_info.starting_bonuses);
    readField(Fields::kCampaignInfo, starting_info.campaign_info);
    readField(Fields::kPlaceholderHeroes, starting_info.placeholder_heroes);
    return starting_info;
  }
}
