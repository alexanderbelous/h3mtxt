#include <h3mtxt/H3Writer/H3Writer.h>
#include <h3mtxt/H3Writer/Utils.h>
#include <h3mtxt/Map/ObjectAttributes.h>

namespace h3m::H3Writer_NS
{
  void H3Writer<ObjectAttributes>::operator()(std::ostream& stream, const ObjectAttributes& value) const
  {
    writeData(stream, value.def);
    writeData(stream, value.passability);
    writeData(stream, value.actionability);
    writeData(stream, value.allowed_landscapes);
    writeData(stream, value.landscape_group);
    writeData(stream, value.object_class);
    writeData(stream, value.object_number);
    writeData(stream, value.object_group);
    writeData(stream, value.is_ground);
    writeData(stream, value.unknown);
  }
}
