#pragma once

#include <h3mtxt/Map/VictoryCondition.h>
#include <h3mtxt/H3MTxtWriter/H3MTxtWriter.h>

namespace Util_NS
{
  inline void writeSpecialVictoryConditionBase(FieldsWriter& out, const h3m::SpecialVictoryConditionBase& base)
  {
    out.writeField("allow_normal_win", base.allow_normal_win);
    out.writeField("applies_to_computer", base.applies_to_computer);
  }

  template<>
  struct JsonObjectWriter<h3m::VictoryConditionDetails<h3m::VictoryConditionType::AcquireArtifact>>
  {
    void operator()(FieldsWriter& out,
                    const h3m::VictoryConditionDetails<h3m::VictoryConditionType::AcquireArtifact>& value) const
    {
      writeSpecialVictoryConditionBase(out, value);
      out.writeField("artifact_type", value.artifact_type);
    }
  };

  template<>
  struct JsonObjectWriter<h3m::VictoryConditionDetails<h3m::VictoryConditionType::AccumulateCreatures>>
  {
    void operator()(FieldsWriter& out,
                    const h3m::VictoryConditionDetails<h3m::VictoryConditionType::AccumulateCreatures>& value) const
    {
      writeSpecialVictoryConditionBase(out, value);
      out.writeField("creature_type", value.creature_type);
      out.writeField("count", value.count);
    }
  };

  template<>
  struct JsonObjectWriter<h3m::VictoryConditionDetails<h3m::VictoryConditionType::AccumulateResources>>
  {
    void operator()(FieldsWriter& out,
                    const h3m::VictoryConditionDetails<h3m::VictoryConditionType::AccumulateResources>& value) const
    {
      writeSpecialVictoryConditionBase(out, value);
      out.writeField("resource_type", value.resource_type);
      out.writeField("amount", value.amount);
    }
  };

  template<>
  struct JsonObjectWriter<h3m::VictoryConditionDetails<h3m::VictoryConditionType::UpgradeTown>>
  {
    void operator()(FieldsWriter& out,
                    const h3m::VictoryConditionDetails<h3m::VictoryConditionType::UpgradeTown>& value) const
    {
      writeSpecialVictoryConditionBase(out, value);
      out.writeField("x", value.x);
      out.writeField("y", value.y);
      out.writeField("z", value.z);
      out.writeField("hall_level", value.hall_level);
      out.writeField("castle_level", value.castle_level);
    }
  };

  template<class T>
  struct JsonObjectWriter<T, std::enable_if_t<std::is_same_v<T, h3m::VictoryConditionDetails<h3m::VictoryConditionType::BuildGrail>> ||
                                          std::is_same_v<T, h3m::VictoryConditionDetails<h3m::VictoryConditionType::DefeatHero>> ||
                                          std::is_same_v<T, h3m::VictoryConditionDetails<h3m::VictoryConditionType::CaptureTown>> ||
                                          std::is_same_v<T, h3m::VictoryConditionDetails<h3m::VictoryConditionType::DefeatMonster>>>>
  {
    void operator()(FieldsWriter& out, const T& value) const
    {
      writeSpecialVictoryConditionBase(out, value);
      out.writeField("x", value.x);
      out.writeField("y", value.y);
      out.writeField("z", value.z);
    }
  };

  template<class T>
  struct JsonObjectWriter<T, std::enable_if_t<std::is_same_v<T, h3m::VictoryConditionDetails<h3m::VictoryConditionType::FlagDwellings>> ||
                                          std::is_same_v<T, h3m::VictoryConditionDetails<h3m::VictoryConditionType::FlagMines>>>>
  {
    void operator()(FieldsWriter& out, const T& value) const
    {
      writeSpecialVictoryConditionBase(out, value);
    }
  };

  template<>
  struct JsonObjectWriter<h3m::VictoryConditionDetails<h3m::VictoryConditionType::TransportArtifact>>
  {
    void operator()(FieldsWriter& out,
                    const h3m::VictoryConditionDetails<h3m::VictoryConditionType::TransportArtifact>& value) const
    {
      writeSpecialVictoryConditionBase(out, value);
      out.writeField("artifact_type", value.artifact_type);
      out.writeField("x", value.x);
      out.writeField("y", value.y);
      out.writeField("z", value.z);
    }
  };

  template<>
  struct JsonObjectWriter<h3m::VictoryConditionDetails<h3m::VictoryConditionType::Normal>>
  {
    void operator()(FieldsWriter&,
                    const h3m::VictoryConditionDetails<h3m::VictoryConditionType::Normal>&) const
    {}
  };

  template<>
  struct JsonObjectWriter<h3m::VictoryCondition>
  {
    void operator()(FieldsWriter& out, const h3m::VictoryCondition& value) const
    {
      const bool has_details = value.type() != h3m::VictoryConditionType::Normal;
      out.writeField("type", value.type());
      if (has_details)
      {
        std::visit([&out](auto&& details) { out.writeField("details", std::forward<decltype(details)>(details)); },
                   value.details);
      }
    }
  };
}
