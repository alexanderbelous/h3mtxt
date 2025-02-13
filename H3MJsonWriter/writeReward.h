#pragma once

#include <h3mtxt/JsonCommon/FieldName.h>
#include <h3mtxt/H3MJsonWriter/getEnumString.h>
#include <h3mtxt/H3MJsonWriter/H3MJsonWriter.h>
#include <h3mtxt/H3MJsonWriter/writeSecondarySkill.h>
#include <h3mtxt/Map/Reward.h>

namespace Medea_NS
{
  template<>
  struct JsonObjectWriter<h3m::RewardDetails<h3m::RewardType::None>>
  {
    void operator()(FieldsWriter&, const h3m::RewardDetails<h3m::RewardType::None>&) const
    {
    }
  };

  template<>
  struct JsonObjectWriter<h3m::RewardDetails<h3m::RewardType::Experience>>
  {
    void operator()(FieldsWriter& out, const h3m::RewardDetails<h3m::RewardType::Experience>& details) const
    {
      out.writeField("experience", details.experience);
    }
  };

  template<>
  struct JsonObjectWriter<h3m::RewardDetails<h3m::RewardType::SpellPoints>>
  {
    void operator()(FieldsWriter& out, const h3m::RewardDetails<h3m::RewardType::SpellPoints>& details) const
    {
      out.writeField("spell_points", details.spell_points);
    }
  };

  template<>
  struct JsonObjectWriter<h3m::RewardDetails<h3m::RewardType::Morale>>
  {
    void operator()(FieldsWriter& out, const h3m::RewardDetails<h3m::RewardType::Morale>& details) const
    {
      out.writeField("morale", details.morale);
    }
  };

  template<>
  struct JsonObjectWriter<h3m::RewardDetails<h3m::RewardType::Luck>>
  {
    void operator()(FieldsWriter& out, const h3m::RewardDetails<h3m::RewardType::Luck>& details) const
    {
      out.writeField("luck", details.luck);
    }
  };

  template<>
  struct JsonObjectWriter<h3m::RewardDetails<h3m::RewardType::Resource>>
  {
    void operator()(FieldsWriter& out, const h3m::RewardDetails<h3m::RewardType::Resource>& details) const
    {
      out.writeField("type", details.type);
      out.writeField("amount", details.amount);
    }
  };

  template<>
  struct JsonObjectWriter<h3m::RewardDetails<h3m::RewardType::PrimarySkill>>
  {
    void operator()(FieldsWriter& out, const h3m::RewardDetails<h3m::RewardType::PrimarySkill>& details) const
    {
      out.writeField("type", details.type);
      out.writeField("value", details.value);
    }
  };

  template<>
  struct JsonObjectWriter<h3m::RewardDetails<h3m::RewardType::SecondarySkill>>
  {
    void operator()(FieldsWriter& out, const h3m::RewardDetails<h3m::RewardType::SecondarySkill>& details) const
    {
      out.writeField("skill", details.skill);
    }
  };

  template<>
  struct JsonObjectWriter<h3m::RewardDetails<h3m::RewardType::Artifact>>
  {
    void operator()(FieldsWriter& out, const h3m::RewardDetails<h3m::RewardType::Artifact>& details) const
    {
      out.writeField("artifact", details.artifact);
    }
  };

  template<>
  struct JsonObjectWriter<h3m::RewardDetails<h3m::RewardType::Spell>>
  {
    void operator()(FieldsWriter& out, const h3m::RewardDetails<h3m::RewardType::Spell>& details) const
    {
      out.writeField("spell", details.spell);
    }
  };

  template<>
  struct JsonObjectWriter<h3m::RewardDetails<h3m::RewardType::Creature>>
  {
    void operator()(FieldsWriter& out, const h3m::RewardDetails<h3m::RewardType::Creature>& details) const
    {
      out.writeField("type", details.type);
      out.writeField("count", details.count);
    }
  };

  template<>
  struct JsonObjectWriter<h3m::Reward>
  {
    void operator()(FieldsWriter& out, const h3m::Reward& reward) const
    {
      using Fields = h3m::FieldNames<h3m::Reward>;
      const bool has_details = reward.type() != h3m::RewardType::None;
      out.writeField(Fields::kType, reward.type());
      if (has_details)
      {
        out.writeComma();
      }
      out.writeComment(h3m::getEnumString(reward.type()), false);
      if (has_details)
      {
        std::visit([&out] <h3m::RewardType T> (const h3m::RewardDetails<T>& details)
                   { out.writeField(Fields::kDetails, details); },
                   reward.details);
      }
    }
  };
}
