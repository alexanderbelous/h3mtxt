#include <h3mtxt/H3JsonReader/H3SVGJsonReader/H3SVGJsonReader.h>

#include <h3mtxt/SavedGame/SavedGame.h>

#include <stdexcept>

namespace h3json
{
  template<>
  h3svg::SavedGame JsonReader<h3svg::SavedGame>::operator()(const Json::Value&) const
  {
    throw std::runtime_error("Not implemented.");
  }
}
