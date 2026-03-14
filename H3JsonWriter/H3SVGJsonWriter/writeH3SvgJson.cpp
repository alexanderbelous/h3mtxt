#include <h3mtxt/H3JsonWriter/H3SVGJsonWriter/writeH3SvgJson.h>

#include <h3mtxt/H3JsonWriter/H3SVGJsonWriter/H3SVGJsonWriter.h>
#include <h3mtxt/Medea/Core.h>

namespace h3svg
{
  void writeH3SvgJson(std::ostream& stream, const SavedGame& saved_game)
  {
    Medea_NS::writeJson(stream, saved_game);
  }
}
