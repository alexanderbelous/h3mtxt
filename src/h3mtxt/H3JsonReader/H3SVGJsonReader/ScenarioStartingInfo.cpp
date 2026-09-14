#include <h3mtxt/H3JsonReader/H3SVGJsonReader/H3SVGJsonReader.h>

#include <h3mtxt/H3JsonReader/H3JsonReaderBase/H3JsonReaderBase.h>
#include <h3mtxt/SavedGame/ScenarioStartingInfo.h>

#include <stdexcept>

namespace h3json
{
  template<>
  h3svg::ScenarioStartingInfo JsonReader<h3svg::ScenarioStartingInfo>::operator()(const Json::Value& value) const
  {
    throw std::logic_error("Not implemented.");
  }
}
