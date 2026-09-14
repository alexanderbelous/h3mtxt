#pragma once

#include <h3mtxt/H3JsonReader/H3JsonReaderBase/H3JsonReaderBaseFwd.h>
#include <h3mtxt/SavedGame/SavedGameFwd.h>

// API for deserializing H3M data from JSON.
namespace h3json
{
  template<>
  h3svg::SavedGame JsonReader<h3svg::SavedGame>::operator()(const Json::Value& value) const;
}
