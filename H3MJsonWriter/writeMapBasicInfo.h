#pragma once

#include <h3mtxt/JsonCommon/FieldName.h>
#include <h3mtxt/Map/MapBasicInfo.h>
#include <h3mtxt/H3MJsonWriter/getEnumString.h>
#include <h3mtxt/H3MJsonWriter/H3MJsonWriter.h>

namespace Util_NS
{
  template<>
  struct JsonObjectWriter<h3m::MapBasicInfo>
  {
    void operator()(FieldsWriter& out, const h3m::MapBasicInfo& value) const
    {
      using Fields = h3m::FieldNames<h3m::MapBasicInfo>;
      out.writeField(Fields::kIsPlayable, value.is_playable);
      out.writeField(Fields::kMapSize, value.map_size);
      out.writeField(Fields::kHasTwoLevels, value.has_two_levels);
      out.writeField(Fields::kName, value.name);
      out.writeField(Fields::kDescription, value.description);
      out.writeField(Fields::kDifficulty, value.difficulty);
      if (auto enum_str = h3m::getEnumString(value.difficulty); !enum_str.empty())
      {
        out.writeComma();
        out.writeComment(enum_str, false);
      }
      out.writeField(Fields::kMaxHeroLevel, value.max_hero_level);
    }
  };
}
