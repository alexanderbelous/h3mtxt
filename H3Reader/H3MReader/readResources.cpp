#include <h3mtxt/H3Reader/H3MReader/H3MReader.h>
#include <h3mtxt/Map/Utils/EnumIndexedArray.h>

namespace h3m
{
  Resources H3MReader::readResources() const
  {
    Resources resources;
    for (std::int32_t& amount : resources.data)
    {
      amount = readInt<std::int32_t>();
    }
    return resources;
  }
}
