#include <h3mtxt/H3Writer/H3Writer.h>
#include <h3mtxt/H3Writer/Utils.h>
#include <h3mtxt/Map/Coordinates.h>

namespace h3m::H3Writer_NS
{
  void H3Writer<Coordinates>::operator()(std::ostream& stream, const Coordinates& value) const
  {
    writeData(stream, value.x);
    writeData(stream, value.y);
    writeData(stream, value.z);
  }
}
