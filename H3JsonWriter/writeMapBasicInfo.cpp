#include <h3mtxt/H3JsonWriter/H3JsonWriter.h>
#include <h3mtxt/H3JsonWriter/getEnumString.h>
#include <h3mtxt/H3JsonWriter/Utils.h>
#include <h3mtxt/JsonCommon/FieldName.h>
#include <h3mtxt/Medea/Medea.h>
#include <h3mtxt/Map/MapBasicInfo.h>

namespace Medea_NS
{
  void JsonObjectWriter<h3m::MapBasicInfo>::operator()(FieldsWriter& out, const h3m::MapBasicInfo& value) const
  {
    using Fields = h3m::FieldNames<h3m::MapBasicInfo>;
    out.writeField(Fields::kIsPlayable, value.is_playable);
    out.writeField(Fields::kMapSize, value.map_size);
    out.writeField(Fields::kHasTwoLevels, value.has_two_levels);
    out.writeField(Fields::kName, value.name);
    out.writeField(Fields::kDescription, value.description);
    out.writeField(Fields::kDifficulty, value.difficulty);
    if (std::string_view enum_str = h3m::getEnumString(value.difficulty); !enum_str.empty())
    {
      out.writeComment(enum_str, false);
    }
    out.writeField(Fields::kMaxHeroLevel, value.max_hero_level);
  }
}
