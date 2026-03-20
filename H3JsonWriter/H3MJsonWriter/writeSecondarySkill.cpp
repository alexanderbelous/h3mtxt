#include <h3mtxt/H3JsonWriter/H3MJsonWriter/H3MJsonWriter.h>

#include <h3mtxt/H3JsonWriter/H3MJsonWriter/getEnumString.h>
#include <h3mtxt/H3JsonWriter/H3MJsonWriter/getSecondarySkillLevelString.h>
#include <h3mtxt/JsonCommon/FieldNamesH3M.h>
#include <h3mtxt/Map/SecondarySkill.h>
#include <h3mtxt/Medea/Medea.h>

namespace Medea_NS
{
  void JsonObjectWriter<h3m::SecondarySkill>::operator()(FieldsWriter& out, const h3m::SecondarySkill& skill) const
  {
    using Fields = h3json::FieldNames<h3m::SecondarySkill>;
    out.writeField(Fields::kType, skill.type);
    if (std::string_view enum_str = h3m::getEnumString(skill.type); !enum_str.empty())
    {
      out.writeComment(enum_str, false);
    }
    out.writeField(Fields::kLevel, skill.level);
    if (std::string_view enum_str = h3m::getSecondarySkillLevelString(skill.type, skill.level); !enum_str.empty())
    {
      out.writeComment(enum_str, false);
    }
  }
}
