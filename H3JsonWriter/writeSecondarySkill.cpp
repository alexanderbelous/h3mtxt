#include <h3mtxt/H3JsonWriter/H3JsonWriter.h>
#include <h3mtxt/H3JsonWriter/getEnumString.h>
#include <h3mtxt/H3JsonWriter/getSecondarySkillLevelString.h>
#include <h3mtxt/H3JsonWriter/Utils.h>
#include <h3mtxt/JsonCommon/FieldName.h>
#include <h3mtxt/JsonWriter/JsonWriter.h>
#include <h3mtxt/Map/SecondarySkill.h>

namespace Medea_NS
{
  void JsonObjectWriter<h3m::SecondarySkill>::operator()(FieldsWriter& out, const h3m::SecondarySkill& skill) const
  {
    using Fields = h3m::FieldNames<h3m::SecondarySkill>;
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
