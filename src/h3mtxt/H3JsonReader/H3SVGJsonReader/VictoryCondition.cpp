#include <h3mtxt/H3JsonReader/H3SVGJsonReader/H3SVGJsonReader.h>

#include <h3mtxt/H3JsonReader/H3JsonReaderBase/H3JsonReaderBase.h>
#include <h3mtxt/SavedGame/VictoryCondition.h>

#include <stdexcept>

namespace h3json
{
  template<>
  h3svg::VictoryCondition JsonReader<h3svg::VictoryCondition>::operator()(const Json::Value& value) const
  {
    throw std::logic_error("Not implemented.");
  }
}
