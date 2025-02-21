#include <h3mtxt/H3Reader/H3Reader.h>
#include <h3mtxt/H3Reader/Utils.h>
#include <h3mtxt/Map/Resources.h>

namespace h3m::H3Reader_NS
{
  Resources readResources(std::istream& stream)
  {
    Resources resources;
    for (std::int32_t& amount : resources.data)
    {
      amount = readInt<std::int32_t>(stream);
    }
    return resources;
  }
}
