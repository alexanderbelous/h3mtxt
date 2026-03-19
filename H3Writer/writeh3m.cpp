#include <h3mtxt/H3Writer/writeh3m.h>

#include <h3mtxt/H3Writer/H3Writer.h>

#include <h3mtxt/thirdparty/zstr/src/zstr.hpp>

namespace h3m::H3Writer_NS
{
  void writeh3m(std::ostream& stream, const Map& map, bool compress)
  {
    if (compress)
    {
      zstr::ostream zstr_stream{stream};
      writeData(zstr_stream, map);
    }
    else
    {
      writeData(stream, map);
    }
  }
}
