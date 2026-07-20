#include <h3mtxt/H3Writer/H3SVGWriter/writeh3svg.h>

#include <h3mtxt/H3Writer/H3SVGWriter/H3SVGWriter.h>

#include <h3mtxt/thirdparty/zstr/src/zstr.hpp>

namespace h3svg
{
  void writeh3svg(std::ostream& stream, const SavedGame& saved_game, bool compress)
  {
    if (compress)
    {
      zstr::ostream zstr_stream{stream};
      H3SVGWriter{ zstr_stream }.writeData(saved_game);
    }
    else
    {
      H3SVGWriter{ stream }.writeData(saved_game);
    }
  }
}
