#include <h3mtxt/H3JsonReader/H3SVGJsonReader/H3SVGJsonReader.h>

#include <h3mtxt/H3JsonReader/H3JsonReaderBase/H3JsonReaderBase.h>
#include <h3mtxt/H3JsonReader/H3SVGJsonReader/Utils.h>
#include <h3mtxt/JsonCommon/FieldNamesH3SVG.h>
#include <h3mtxt/SavedGame/ScenarioStartingInfo.h>

namespace h3json
{
  template<>
  h3svg::ScenarioStartingInfo JsonReader<h3svg::ScenarioStartingInfo>::operator()(const Json::Value& value) const
  {
    using Fields = h3json::FieldNames<h3svg::ScenarioStartingInfo>;
    h3svg::ScenarioStartingInfo starting_info;
    readField(starting_info.starting_towns, value, Fields::kStartingTowns);
    readField(starting_info.unknown1, value, Fields::kUnknown1);
    readField(starting_info.difficulty, value, Fields::kDifficulty);
    readField(starting_info.map_filename, value, Fields::kMapFilename);
    readField(starting_info.map_directory, value, Fields::kMapDirectory);
    readField(starting_info.players_control, value, Fields::kPlayersControl);
    readField(starting_info.unknown2, value, Fields::kUnknown2);
    readField(starting_info.player_turn_duration, value, Fields::kPlayerTurnDuration);
    readField(starting_info.starting_heroes, value, Fields::kStartingHeroes);
    readField(starting_info.starting_bonuses, value, Fields::kStartingBonuses);
    readField(starting_info.campaign_info, value, Fields::kCampaignInfo);
    readField(starting_info.placeholder_heroes, value, Fields::kPlaceholderHeroes);
    return starting_info;
  }
}
