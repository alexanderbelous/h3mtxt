#include <h3mtxt/H3Reader/H3MReader/H3MReader.h>
#include <h3mtxt/Map/Army.h>

namespace h3m
{
  Army H3MReader::readArmy() const
  {
    Army army;
    for (auto& slot : army.slots)
    {
      slot = readTypedQuantity<CreatureType, std::int16_t>();
    }
    return army;
  }
}
