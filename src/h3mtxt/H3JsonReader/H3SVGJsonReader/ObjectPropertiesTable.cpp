#include <h3mtxt/H3JsonReader/H3SVGJsonReader/H3SVGJsonReader.h>

#include <h3mtxt/H3JsonReader/H3JsonReaderBase/H3JsonReaderBase.h>
#include <h3mtxt/SavedGame/ObjectPropertiesTables.h>

#include <stdexcept>

namespace h3json
{
  template<>
  h3svg::ObjectPropertiesTables JsonReader<h3svg::ObjectPropertiesTables>::operator()(const Json::Value& value) const
  {
    throw std::logic_error("JsonReader<h3svg::ObjectPropertiesTables>: Not implemented.");
  }
}
