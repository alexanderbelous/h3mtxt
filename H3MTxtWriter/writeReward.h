#pragma once

#include <h3mtxt/Map/Reward.h>
#include <h3mtxt/H3MTxtWriter/getEnumString.h>
#include <h3mtxt/H3MTxtWriter/H3MTxtWriter.h>
#include <h3mtxt/H3MTxtWriter/writeSecondarySkill.h>

namespace Util_NS
{
  template<>
  struct StructWriter<h3m::RewardDetails<h3m::RewardType::None>>
  {
    void operator()(FieldsWriter&, const h3m::RewardDetails<h3m::RewardType::None>&) const
    {
    }
  };

  template<>
  struct StructWriter<h3m::RewardDetails<h3m::RewardType::Experience>>
  {
    void operator()(FieldsWriter& out, const h3m::RewardDetails<h3m::RewardType::Experience>& details) const
    {
      out.writeField("experience", details.experience);
    }
  };

  template<>
  struct StructWriter<h3m::RewardDetails<h3m::RewardType::SpellPoints>>
  {
    void operator()(FieldsWriter& out, const h3m::RewardDetails<h3m::RewardType::SpellPoints>& details) const
    {
      out.writeField("spell_points", details.spell_points);
    }
  };

  template<>
  struct StructWriter<h3m::RewardDetails<h3m::RewardType::Morale>>
  {
    void operator()(FieldsWriter& out, const h3m::RewardDetails<h3m::RewardType::Morale>& details) const
    {
      out.writeField("morale", details.morale);
    }
  };

  template<>
  struct StructWriter<h3m::RewardDetails<h3m::RewardType::Luck>>
  {
    void operator()(FieldsWriter& out, const h3m::RewardDetails<h3m::RewardType::Luck>& details) const
    {
      out.writeField("luck", details.luck);
    }
  };

  template<>
  struct StructWriter<h3m::RewardDetails<h3m::RewardType::Resource>>
  {
    void operator()(FieldsWriter& out, const h3m::RewardDetails<h3m::RewardType::Resource>& details) const
    {
      out.writeField("type", details.type);
      out.writeField("amount", details.amount);
    }
  };

  template<>
  struct StructWriter<h3m::RewardDetails<h3m::RewardType::PrimarySkill>>
  {
    void operator()(FieldsWriter& out, const h3m::RewardDetails<h3m::RewardType::PrimarySkill>& details) const
    {
      out.writeField("type", details.type);
      out.writeField("value", details.value);
    }
  };

  template<>
  struct StructWriter<h3m::RewardDetails<h3m::RewardType::SecondarySkill>>
  {
    void operator()(FieldsWriter& out, const h3m::RewardDetails<h3m::RewardType::SecondarySkill>& details) const
    {
      out.writeField("skill", details.skill);
    }
  };

  template<>
  struct StructWriter<h3m::RewardDetails<h3m::RewardType::Artifact>>
  {
    void operator()(FieldsWriter& out, const h3m::RewardDetails<h3m::RewardType::Artifact>& details) const
    {
      out.writeField("artifact", details.artifact);
    }
  };

  template<>
  struct StructWriter<h3m::RewardDetails<h3m::RewardType::Spell>>
  {
    void operator()(FieldsWriter& out, const h3m::RewardDetails<h3m::RewardType::Spell>& details) const
    {
      out.writeField("spell", details.spell);
    }
  };

  template<>
  struct StructWriter<h3m::RewardDetails<h3m::RewardType::Creature>>
  {
    void operator()(FieldsWriter& out, const h3m::RewardDetails<h3m::RewardType::Creature>& details) const
    {
      out.writeField("type", details.type);
      out.writeField("count", details.count);
    }
  };

  template<>
  struct StructWriter<h3m::Reward>
  {
    void operator()(FieldsWriter& out, const h3m::Reward& reward) const
    {
      const bool has_details = reward.type() != h3m::RewardType::None;
      out.writeComment(h3m::getEnumString(reward.type()));
      out.writeField("type", reward.type());
      if (has_details)
      {
        std::visit([&out](auto&& details) { out.writeField("details", std::forward<decltype(details)>(details)); },
                   reward.details);
      }
    }
  };
}
