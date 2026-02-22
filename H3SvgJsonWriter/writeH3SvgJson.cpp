#include <h3mtxt/H3SvgJsonWriter/writeH3SvgJson.h>

#include <h3mtxt/H3SvgJsonWriter/H3SvgJsonWriter.h>
#include <h3mtxt/Medea/Core.h>

namespace h3m
{
  void writeH3SvgJson(std::ostream& stream, const SavedGame& saved_game)
  {
    Medea_NS::writeJson(stream, saved_game);
  }
}
