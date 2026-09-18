#pragma once

#include <h3mtxt/H3JsonReader/H3JsonReaderBase/H3JsonReaderBaseFwd.h>
#include <h3mtxt/SavedGame/SavedGameFwd.h>

// API for deserializing H3M data from JSON.
namespace h3json
{
  template<>
  h3svg::ArtifactMerchants JsonReader<h3svg::ArtifactMerchants>::operator()(const Json::Value& value) const;

  template<>
  h3svg::CoordinatesPacked JsonReader<h3svg::CoordinatesPacked>::operator()(const Json::Value& value) const;

  template<>
  h3svg::CreatureBank JsonReader<h3svg::CreatureBank>::operator()(const Json::Value& value) const;

  template<>
  h3svg::Date JsonReader<h3svg::Date>::operator()(const Json::Value& value) const;

  // Defined in Utils.h.
  template<std::size_t N>
  struct JsonReader<h3svg::FixedLengthString<N>>
  {
    h3svg::FixedLengthString<N> operator()(const Json::Value& value) const;
  };

  template<>
  h3svg::LossCondition JsonReader<h3svg::LossCondition>::operator()(const Json::Value& value) const;

  template<>
  h3svg::Object JsonReader<h3svg::Object>::operator()(const Json::Value& value) const;

  template<>
  h3svg::ObjectPropertiesTables JsonReader<h3svg::ObjectPropertiesTables>::operator()(const Json::Value& value) const;

  template<>
  h3svg::ObjectTemplate JsonReader<h3svg::ObjectTemplate>::operator()(const Json::Value& value) const;

  template<>
  h3svg::Player JsonReader<h3svg::Player>::operator()(const Json::Value& value) const;

  template<>
  h3svg::PlayerSpecs JsonReader<h3svg::PlayerSpecs>::operator()(const Json::Value& value) const;

  template<>
  h3svg::ReplayEvent JsonReader<h3svg::ReplayEvent>::operator()(const Json::Value& value) const;

  template<>
  h3svg::Rumor JsonReader<h3svg::Rumor>::operator()(const Json::Value& value) const;

  template<>
  h3svg::SavedGame JsonReader<h3svg::SavedGame>::operator()(const Json::Value& value) const;

  template<>
  h3svg::ScenarioStartingInfo JsonReader<h3svg::ScenarioStartingInfo>::operator()(const Json::Value& value) const;

  template<>
  h3svg::Tile JsonReader<h3svg::Tile>::operator()(const Json::Value& value) const;

  template<>
  h3svg::TileVisibility JsonReader<h3svg::TileVisibility>::operator()(const Json::Value& value) const;

  template<>
  h3svg::Town JsonReader<h3svg::Town>::operator()(const Json::Value& value) const;

  template<>
  h3svg::TownUniqueBuildingsProperties
  JsonReader<h3svg::TownUniqueBuildingsProperties>::operator()(const Json::Value& value) const;

  template<>
  h3svg::Troops JsonReader<h3svg::Troops>::operator()(const Json::Value& value) const;

  template<>
  h3svg::University JsonReader<h3svg::University>::operator()(const Json::Value& value) const;

  template<>
  h3svg::VictoryCondition JsonReader<h3svg::VictoryCondition>::operator()(const Json::Value& value) const;
}
