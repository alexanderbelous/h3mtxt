#include <h3mtxt/H3Writer/H3Writer.h>
#include <h3mtxt/H3Writer/Utils.h>
#include <h3mtxt/Map/ObjectTemplate.h>

namespace h3m::H3Writer_NS
{
  void H3Writer<ObjectTemplate>::operator()(std::ostream& stream, const ObjectTemplate& value) const
  {
    writeData(stream, value.def);
    writeData(stream, value.passability);
    writeData(stream, value.actionability);
    writeData(stream, value.allowed_landscapes);
    writeData(stream, value.landscape_group);
    writeData(stream, value.object_class);
    writeData(stream, value.object_subclass);
    writeData(stream, value.object_group);
    writeData(stream, value.is_ground);
    writeData(stream, value.unknown);
  }
}
