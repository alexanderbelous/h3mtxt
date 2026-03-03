#include <h3mtxt/H3SvgJsonWriter/H3SvgJsonWriter.h>

#include <h3mtxt/H3JsonWriter/H3JsonWriter.h>
#include <h3mtxt/H3JsonWriter/getEnumString.h>
#include <h3mtxt/H3JsonWriter/Utils.h>
#include <h3mtxt/H3SvgJsonWriter/getEnumString.h>
#include <h3mtxt/JsonCommon/FieldNamesSvg.h>
#include <h3mtxt/Medea/Medea.h>
#include <h3mtxt/SavedGame/RewardSvg.h>

namespace Medea_NS
{
  void JsonObjectWriter<h3m::RewardDetailsSvg<h3m::RewardType::None>>::operator()(
    FieldsWriter& out, const h3m::RewardDetailsSvg<h3m::RewardType::None>& details) const
  {
    out.writeField("reserved", details.reserved);
  }

  void JsonObjectWriter<h3m::RewardDetailsSvg<h3m::RewardType::Experience>>::operator()(
    FieldsWriter& out, const h3m::RewardDetailsSvg<h3m::RewardType::Experience>& details) const
  {
    out.writeField("experience", details.experience);
    out.writeField("reserved", details.reserved);
  }

  void JsonObjectWriter<h3m::RewardDetailsSvg<h3m::RewardType::SpellPoints>>::operator()(
    FieldsWriter& out, const h3m::RewardDetailsSvg<h3m::RewardType::SpellPoints>& details) const
  {
    out.writeField("spell_points", details.spell_points);
    out.writeField("reserved", details.reserved);
  }

  void JsonObjectWriter<h3m::RewardDetailsSvg<h3m::RewardType::Morale>>::operator()(
    FieldsWriter& out, const h3m::RewardDetailsSvg<h3m::RewardType::Morale>& details) const
  {
    out.writeField("morale", details.morale);
    out.writeField("reserved", details.reserved);
  }

  void JsonObjectWriter<h3m::RewardDetailsSvg<h3m::RewardType::Luck>>::operator()(
    FieldsWriter& out, const h3m::RewardDetailsSvg<h3m::RewardType::Luck>& details) const
  {
    out.writeField("luck", details.luck);
    out.writeField("reserved", details.reserved);
  }

  void JsonObjectWriter<h3m::RewardDetailsSvg<h3m::RewardType::Resource>>::operator()(
    FieldsWriter& out, const h3m::RewardDetailsSvg<h3m::RewardType::Resource>& details) const
  {
    out.writeField("type", details.type);
    if (std::string_view enum_str = h3m::getEnumString(details.type); !enum_str.empty())
    {
      out.writeComment(enum_str, false);
    }
    out.writeField("amount", details.amount);
  }

  void JsonObjectWriter<h3m::RewardDetailsSvg<h3m::RewardType::PrimarySkill>>::operator()(
    FieldsWriter& out, const h3m::RewardDetailsSvg<h3m::RewardType::PrimarySkill>& details) const
  {
    out.writeField("type", details.type);
    if (std::string_view enum_str = h3m::getEnumString(details.type); !enum_str.empty())
    {
      out.writeComment(enum_str, false);
    }
    out.writeField("value", details.value);
  }

  void JsonObjectWriter<h3m::RewardDetailsSvg<h3m::RewardType::SecondarySkill>>::operator()(
    FieldsWriter& out, const h3m::RewardDetailsSvg<h3m::RewardType::SecondarySkill>& details) const
  {
    out.writeField("type", details.type);
    if (std::string_view enum_str = h3m::getEnumString(details.type); !enum_str.empty())
    {
      out.writeComment(enum_str, false);
    }
    out.writeField("level", details.level);
  }

  void JsonObjectWriter<h3m::RewardDetailsSvg<h3m::RewardType::Artifact>>::operator()(
    FieldsWriter& out, const h3m::RewardDetailsSvg<h3m::RewardType::Artifact>& details) const
  {
    out.writeField("type", details.artifact);
    if (std::string_view enum_str = h3m::getEnumString(details.artifact); !enum_str.empty())
    {
      out.writeComment(enum_str, false);
    }
    out.writeField("reserved", details.reserved);
  }

  void JsonObjectWriter<h3m::RewardDetailsSvg<h3m::RewardType::Spell>>::operator()(
    FieldsWriter& out, const h3m::RewardDetailsSvg<h3m::RewardType::Spell>& details) const
  {
    out.writeField("type", details.spell);
    if (std::string_view enum_str = h3m::getEnumString(details.spell); !enum_str.empty())
    {
      out.writeComment(enum_str, false);
    }
    out.writeField("reserved", details.reserved);
  }

  void JsonObjectWriter<h3m::RewardDetailsSvg<h3m::RewardType::Creature>>::operator()(
    FieldsWriter& out, const h3m::RewardDetailsSvg<h3m::RewardType::Creature>& details) const
  {
    out.writeField("type", details.type);
    if (std::string_view enum_str = h3m::getEnumString(details.type); !enum_str.empty())
    {
      out.writeComment(enum_str, false);
    }
    out.writeField("count", details.count);
  }

  void JsonObjectWriter<h3m::RewardSvg>::operator()(FieldsWriter& out, const h3m::RewardSvg& reward) const
  {
    using Fields = h3m::FieldNames<h3m::RewardSvg>;
    out.writeField(Fields::kType, reward.type());
    out.writeComment(h3m::getEnumString(reward.type()), false);
    if (reward.type() != h3m::RewardType::None)
    {
      std::visit([&out] <h3m::RewardType T> (const h3m::RewardDetailsSvg<T>& details)
                 {
                   out.writeField(Fields::kDetails, details);
                 },
                 reward.details);
    }
  }
}
