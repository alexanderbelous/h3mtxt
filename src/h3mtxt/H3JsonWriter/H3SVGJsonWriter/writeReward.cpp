#include <h3mtxt/H3JsonWriter/H3SVGJsonWriter/H3SVGJsonWriter.h>

#include <h3mtxt/H3JsonWriter/H3MJsonWriter/H3MJsonWriter.h>
#include <h3mtxt/H3JsonWriter/H3MJsonWriter/Utils.h>
#include <h3mtxt/JsonCommon/FieldNamesH3SVG.h>
#include <h3mtxt/Medea/Medea.h>
#include <h3mtxt/SavedGame/Reward.h>

namespace Medea_NS
{
  void JsonObjectWriter<h3svg::RewardDetails<h3svg::RewardType::None>>::operator()(
    FieldsWriter& out, const h3svg::RewardDetails<h3svg::RewardType::None>& details) const
  {
    out.writeField("reserved", details.reserved);
  }

  void JsonObjectWriter<h3svg::RewardDetails<h3svg::RewardType::Experience>>::operator()(
    FieldsWriter& out, const h3svg::RewardDetails<h3svg::RewardType::Experience>& details) const
  {
    out.writeField("experience", details.experience);
    out.writeField("reserved", details.reserved);
  }

  void JsonObjectWriter<h3svg::RewardDetails<h3svg::RewardType::SpellPoints>>::operator()(
    FieldsWriter& out, const h3svg::RewardDetails<h3svg::RewardType::SpellPoints>& details) const
  {
    out.writeField("spell_points", details.spell_points);
    out.writeField("reserved", details.reserved);
  }

  void JsonObjectWriter<h3svg::RewardDetails<h3svg::RewardType::Morale>>::operator()(
    FieldsWriter& out, const h3svg::RewardDetails<h3svg::RewardType::Morale>& details) const
  {
    out.writeField("morale", details.morale);
    out.writeField("reserved", details.reserved);
  }

  void JsonObjectWriter<h3svg::RewardDetails<h3svg::RewardType::Luck>>::operator()(
    FieldsWriter& out, const h3svg::RewardDetails<h3svg::RewardType::Luck>& details) const
  {
    out.writeField("luck", details.luck);
    out.writeField("reserved", details.reserved);
  }

  void JsonObjectWriter<h3svg::RewardDetails<h3svg::RewardType::Resource>>::operator()(
    FieldsWriter& out, const h3svg::RewardDetails<h3svg::RewardType::Resource>& details) const
  {
    out.writeField("type", details.type);
    out.writeField("amount", details.amount);
  }

  void JsonObjectWriter<h3svg::RewardDetails<h3svg::RewardType::PrimarySkill>>::operator()(
    FieldsWriter& out, const h3svg::RewardDetails<h3svg::RewardType::PrimarySkill>& details) const
  {
    out.writeField("type", details.type);
    out.writeField("value", details.value);
  }

  void JsonObjectWriter<h3svg::RewardDetails<h3svg::RewardType::SecondarySkill>>::operator()(
    FieldsWriter& out, const h3svg::RewardDetails<h3svg::RewardType::SecondarySkill>& details) const
  {
    out.writeField("type", details.type);
    out.writeField("level", details.level);
  }

  void JsonObjectWriter<h3svg::RewardDetails<h3svg::RewardType::Artifact>>::operator()(
    FieldsWriter& out, const h3svg::RewardDetails<h3svg::RewardType::Artifact>& details) const
  {
    out.writeField("type", details.artifact);
    out.writeField("reserved", details.reserved);
  }

  void JsonObjectWriter<h3svg::RewardDetails<h3svg::RewardType::Spell>>::operator()(
    FieldsWriter& out, const h3svg::RewardDetails<h3svg::RewardType::Spell>& details) const
  {
    out.writeField("type", details.spell);
    out.writeField("reserved", details.reserved);
  }

  void JsonObjectWriter<h3svg::RewardDetails<h3svg::RewardType::Creature>>::operator()(
    FieldsWriter& out, const h3svg::RewardDetails<h3svg::RewardType::Creature>& details) const
  {
    out.writeField("type", details.type);
    out.writeField("count", details.count);
  }

  void JsonObjectWriter<h3svg::Reward>::operator()(FieldsWriter& out, const h3svg::Reward& reward) const
  {
    using Fields = h3json::FieldNames<h3svg::Reward>;
    out.writeField(Fields::kType, reward.type());
    if (reward.type() != h3svg::RewardType::None)
    {
      std::visit([&out] <h3svg::RewardType T> (const h3svg::RewardDetails<T>& details)
                 {
                   out.writeField(Fields::kDetails, details);
                 },
                 reward.details);
    }
  }
}
