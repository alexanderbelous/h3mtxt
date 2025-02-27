#include <h3mtxt/H3JsonReader/Utils.h>
#include <h3mtxt/JsonCommon/FieldName.h>
#include <h3mtxt/Map/Utils/EnumBitmask.h>

namespace h3m::H3JsonReader_NS
{
  SecondarySkillsBitmask JsonReader<SecondarySkillsBitmask>::operator()(const Json::Value& value) const
  {
    using Fields = FieldNames<SecondarySkillsBitmask>;
    SecondarySkillsBitmask bitmask;
    static_assert(Fields::kNames.size() == bitmask.bitset.kNumBits,
                  "The number of fields in h3m::FieldNames<h3m::SecondarySkillsBitmask> "
                  "should match the number of bits in h3m::SecondarySkillsBitmask");
    for (std::size_t i = 0; i < bitmask.bitset.kNumBits; ++i)
    {
      bitmask.bitset.set(i, readField<bool>(value, Fields::kNames[i]));
    }
    return bitmask;
  }
}
