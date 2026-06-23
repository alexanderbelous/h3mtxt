#include <h3mtxt/H3JsonWriter/H3MJsonWriter/H3MJsonWriter.h>

#include <h3mtxt/Map/Army.h>
#include <h3mtxt/Medea/Medea.h>

namespace Medea_NS
{
  template<>
  void JsonArrayWriter<h3m::Army>::operator()(const ArrayElementsWriter& out, const h3m::Army& army) const
  {
    JsonArrayWriter<decltype(h3m::Army::slots)>{}(out, army.slots);
  }
}
