#include <h3mtxt/H3JsonWriter/H3JsonWriter.h>
#include <h3mtxt/H3JsonWriter/getEnumString.h>
#include <h3mtxt/H3JsonWriter/Utils.h>
#include <h3mtxt/H3JsonWriter/writeRewardDetails.h>
#include <h3mtxt/JsonCommon/FieldName.h>
#include <h3mtxt/Medea/JsonWriter.h>
#include <h3mtxt/Map/Reward.h>

namespace Medea_NS
{
  void JsonObjectWriter<h3m::RewardDetails<h3m::RewardType::None>>::operator()(
    FieldsWriter&, const h3m::RewardDetails<h3m::RewardType::None>&) const
  {
  }

  void JsonObjectWriter<h3m::RewardDetails<h3m::RewardType::Experience>>::operator()(
    FieldsWriter& out, const h3m::RewardDetails<h3m::RewardType::Experience>& details) const
  {
    out.writeField("experience", details.experience);
  }

  void JsonObjectWriter<h3m::RewardDetails<h3m::RewardType::SpellPoints>>::operator()(
    FieldsWriter& out, const h3m::RewardDetails<h3m::RewardType::SpellPoints>& details) const
  {
    out.writeField("spell_points", details.spell_points);
  }

  void JsonObjectWriter<h3m::RewardDetails<h3m::RewardType::Morale>>::operator()(
    FieldsWriter& out, const h3m::RewardDetails<h3m::RewardType::Morale>& details) const
  {
    out.writeField("morale", details.morale);
  }

  void JsonObjectWriter<h3m::RewardDetails<h3m::RewardType::Luck>>::operator()(
    FieldsWriter& out, const h3m::RewardDetails<h3m::RewardType::Luck>& details) const
  {
    out.writeField("luck", details.luck);
  }

  void JsonObjectWriter<h3m::RewardDetails<h3m::RewardType::Resource>>::operator()(
    FieldsWriter& out, const h3m::RewardDetails<h3m::RewardType::Resource>& details) const
  {
    out.writeField("type", details.type);
    if (auto enum_str = h3m::getEnumString(details.type); !enum_str.empty())
    {
      out.writeComment(enum_str, false);
    }
    out.writeField("amount", details.amount);
  }

  void JsonObjectWriter<h3m::RewardDetails<h3m::RewardType::PrimarySkill>>::operator()(
    FieldsWriter& out, const h3m::RewardDetails<h3m::RewardType::PrimarySkill>& details) const
  {
    out.writeField("type", details.type);
    if (auto enum_str = h3m::getEnumString(details.type); !enum_str.empty())
    {
      out.writeComment(enum_str, false);
    }
    out.writeField("value", details.value);
  }

  void JsonObjectWriter<h3m::RewardDetails<h3m::RewardType::SecondarySkill>>::operator()(
    FieldsWriter& out, const h3m::RewardDetails<h3m::RewardType::SecondarySkill>& details) const
  {
    JsonObjectWriter<h3m::SecondarySkill> secondary_skill_writer {};
    secondary_skill_writer(out, static_cast<const h3m::SecondarySkill&>(details));
  }

  void JsonObjectWriter<h3m::RewardDetails<h3m::RewardType::Artifact>>::operator()(
    FieldsWriter& out, const h3m::RewardDetails<h3m::RewardType::Artifact>& details) const
  {
    out.writeField("artifact", details.artifact);
    if (auto enum_str = h3m::getEnumString(details.artifact); !enum_str.empty())
    {
      out.writeComment(enum_str, false);
    }
  }

  void JsonObjectWriter<h3m::RewardDetails<h3m::RewardType::Spell>>::operator()(
    FieldsWriter& out, const h3m::RewardDetails<h3m::RewardType::Spell>& details) const
  {
    out.writeField("spell", details.spell);
    if (auto enum_str = h3m::getEnumString(details.spell); !enum_str.empty())
    {
      out.writeComment(enum_str, false);
    }
  }

  void JsonObjectWriter<h3m::RewardDetails<h3m::RewardType::Creature>>::operator()(
    FieldsWriter& out, const h3m::RewardDetails<h3m::RewardType::Creature>& details) const
  {
    JsonObjectWriter<h3m::CreatureStack> creature_writer {};
    creature_writer(out, static_cast<const h3m::CreatureStack&>(details));
  }

  void JsonObjectWriter<h3m::Reward>::operator()(FieldsWriter& out, const h3m::Reward& reward) const
  {
    using Fields = h3m::FieldNames<h3m::Reward>;
    out.writeField(Fields::kType, reward.type());
    out.writeComment(h3m::getEnumString(reward.type()), false);
    if (reward.type() != h3m::RewardType::None)
    {
      std::visit([&out] <h3m::RewardType T> (const h3m::RewardDetails<T>& details)
                  { out.writeField(Fields::kDetails, details); },
                  reward.details);
    }
  }
}
