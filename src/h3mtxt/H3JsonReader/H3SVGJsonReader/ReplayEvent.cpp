#include <h3mtxt/H3JsonReader/H3SVGJsonReader/H3SVGJsonReader.h>

#include <h3mtxt/H3JsonReader/H3JsonReaderBase/H3JsonReaderBase.h>
#include <h3mtxt/SavedGame/Replay.h>

#include <stdexcept>

namespace h3json
{
  template<>
  h3svg::ReplayEvent JsonReader<h3svg::ReplayEvent>::operator()(const Json::Value& value) const
  {
    throw std::logic_error("JsonReader<h3svg::ReplayEvent>: Not implemented.");
  }
}
