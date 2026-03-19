#include <h3mtxt/H3Writer/H3MWriter/writeh3m.h>

#include <h3mtxt/H3Writer/H3MWriter/H3MWriter.h>

#include <h3mtxt/thirdparty/zstr/src/zstr.hpp>

namespace h3m
{
  void writeh3m(std::ostream& stream, const Map& map, bool compress)
  {
    if (compress)
    {
      zstr::ostream zstr_stream{stream};
      H3MWriter{ zstr_stream }.writeData(map);
    }
    else
    {
      H3MWriter{ stream }.writeData(map);
    }
  }
}
