#pragma once

#include <h3mtxt/JsonCommon/FieldName.h>
#include <h3mtxt/H3JsonWriter/H3JsonWriter.h>
#include <h3mtxt/Map/MapFwd.h>
#include <h3mtxt/Map/Utils/EnumBitmask.h>

#include <cstdint>

namespace Medea_NS
{
  template<>
  struct JsonObjectWriter<h3m::SecondarySkillsBitmask>
  {
    void operator()(FieldsWriter& out, const h3m::SecondarySkillsBitmask& bitmask) const
    {
      using Fields = h3m::FieldNames<h3m::SecondarySkillsBitmask>;
      static_assert(Fields::kNames.size() == bitmask.bitset.kNumBits,
                    "The number of fields in h3m::FieldNames<h3m::SecondarySkillsBitmask> "
                    "should match the number of bits in h3m::SecondarySkillsBitmask");

      for (std::size_t i = 0; i < bitmask.bitset.kNumBits; ++i)
      {
        out.writeField(Fields::kNames[i], bitmask.bitset[i]);
      }
    }
  };
}
