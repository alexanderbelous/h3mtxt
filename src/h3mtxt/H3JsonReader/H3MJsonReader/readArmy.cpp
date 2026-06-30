#include <h3mtxt/H3JsonReader/H3MJsonReader/H3MJsonReader.h>

#include <h3mtxt/H3JsonReader/H3JsonReaderBase/H3JsonReaderBase.h>
#include <h3mtxt/Map/Army.h>

namespace h3json
{
  template<>
  h3m::Army JsonReader<h3m::Army>::operator()(const Json::Value& value) const
  {
    return h3m::Army{
      .slots = fromJson<std::array<h3m::TypedQuantity<h3m::CreatureType, std::int16_t>, h3m::Army::kNumSlots>>(value)
    };
  }
}
