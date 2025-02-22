#include <h3mtxt/H3Writer/writeh3c.h>

#include <h3mtxt/H3Writer/H3Writer.h>

#include <h3mtxt/thirdparty/zstr/src/zstr.hpp>

namespace h3m::H3Writer_NS
{
  void writeh3c(std::ostream& stream, const Campaign& campaign, bool compress)
  {
    if (compress)
    {
      zstr::ostream zstr_stream(stream);
      writeData(zstr_stream, campaign);
    }
    else
    {
      writeData(stream, campaign);
    }
  }
}
