#include <h3mtxt/H3JsonReader/H3SVGJsonReader/readH3SVGJson.h>

#include <h3mtxt/H3JsonReader/H3JsonReaderBase/Utils.h>
#include <h3mtxt/H3JsonReader/H3SVGJsonReader/H3SVGJsonReader.h>

namespace h3json
{
  h3svg::SavedGame readH3SVGJson(std::istream& stream)
  {
    return fromJsonStream<h3svg::SavedGame>(stream);
  }
}
