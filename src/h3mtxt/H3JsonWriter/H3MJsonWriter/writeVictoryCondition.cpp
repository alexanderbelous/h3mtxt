#include <h3mtxt/H3JsonWriter/H3MJsonWriter/H3MJsonWriter.h>

#include <h3mtxt/H3JsonWriter/H3MJsonWriter/getEnumString.h>
#include <h3mtxt/H3JsonWriter/H3MJsonWriter/Utils.h>
#include <h3mtxt/JsonCommon/FieldNamesH3M.h>
#include <h3mtxt/Map/VictoryCondition.h>
#include <h3mtxt/Medea/Medea.h>

namespace Medea_NS
{
  template<>
  void JsonObjectWriter<h3m::SpecialVictoryConditionBase>::operator()(
    FieldsWriter& out, const h3m::SpecialVictoryConditionBase& value) const
  {
    using Fields = h3json::FieldNames<h3m::SpecialVictoryConditionBase>;
    out.writeField(Fields::kAllowNormalWin, value.allow_normal_win);
    out.writeField(Fields::kAppliesToComputer, value.applies_to_computer);
  }

  template<>
  void JsonObjectWriter<h3m::VictoryConditionDetails<h3m::VictoryConditionType::AcquireArtifact>>::operator()(
    FieldsWriter& out, const h3m::VictoryConditionDetails<h3m::VictoryConditionType::AcquireArtifact>& value) const
  {
    JsonObjectWriter<h3m::SpecialVictoryConditionBase>{}(out, value);
    out.writeField("artifact_type", value.artifact_type);
    if (std::string_view enum_str = h3m::getEnumString(value.artifact_type); !enum_str.empty())
    {
      out.writeComment(enum_str, false);
    }
  }

  template<>
  void JsonObjectWriter<h3m::VictoryConditionDetails<h3m::VictoryConditionType::AccumulateCreatures>>::operator()(
    FieldsWriter& out, const h3m::VictoryConditionDetails<h3m::VictoryConditionType::AccumulateCreatures>& value) const
  {
    JsonObjectWriter<h3m::SpecialVictoryConditionBase>{}(out, value);
    out.writeField("creature_type", value.creature_type);
    if (std::string_view enum_str = h3m::getEnumString(value.creature_type); !enum_str.empty())
    {
      out.writeComment(enum_str, false);
    }
    out.writeField("count", value.count);
  }

  template<>
  void JsonObjectWriter<h3m::VictoryConditionDetails<h3m::VictoryConditionType::AccumulateResources>>::operator()(
    FieldsWriter& out, const h3m::VictoryConditionDetails<h3m::VictoryConditionType::AccumulateResources>& value) const
  {
    JsonObjectWriter<h3m::SpecialVictoryConditionBase>{}(out, value);
    out.writeField("resource_type", value.resource_type);
    if (std::string_view enum_str = h3m::getEnumString(value.resource_type); !enum_str.empty())
    {
      out.writeComment(enum_str, false);
    }
    out.writeField("amount", value.amount);
  }

  template<>
  void JsonObjectWriter<h3m::VictoryConditionDetails<h3m::VictoryConditionType::UpgradeTown>>::operator()(
    FieldsWriter& out, const h3m::VictoryConditionDetails<h3m::VictoryConditionType::UpgradeTown>& value) const
  {
    JsonObjectWriter<h3m::SpecialVictoryConditionBase>{}(out, value);
    out.writeField("coordinates", value.coordinates);
    out.writeField("hall_level", value.hall_level);
    out.writeField("castle_level", value.castle_level);
  }

  template<>
  void JsonObjectWriter<h3m::VictoryConditionDetails<h3m::VictoryConditionType::BuildGrail>>::operator()(
    FieldsWriter& out, const h3m::VictoryConditionDetails<h3m::VictoryConditionType::BuildGrail>& value) const
  {
    JsonObjectWriter<h3m::SpecialVictoryConditionBase>{}(out, value);
    out.writeField("coordinates", value.coordinates);
  }

  template<>
  void JsonObjectWriter<h3m::VictoryConditionDetails<h3m::VictoryConditionType::DefeatHero>>::operator()(
    FieldsWriter& out, const h3m::VictoryConditionDetails<h3m::VictoryConditionType::DefeatHero>& value) const
  {
    JsonObjectWriter<h3m::SpecialVictoryConditionBase>{}(out, value);
    out.writeField("coordinates", value.coordinates);
  }

  template<>
  void JsonObjectWriter<h3m::VictoryConditionDetails<h3m::VictoryConditionType::CaptureTown>>::operator()(
    FieldsWriter& out, const h3m::VictoryConditionDetails<h3m::VictoryConditionType::CaptureTown>& value) const
  {
    JsonObjectWriter<h3m::SpecialVictoryConditionBase>{}(out, value);
    out.writeField("coordinates", value.coordinates);
  }

  template<>
  void JsonObjectWriter<h3m::VictoryConditionDetails<h3m::VictoryConditionType::DefeatMonster>>::operator()(
    FieldsWriter& out, const h3m::VictoryConditionDetails<h3m::VictoryConditionType::DefeatMonster>& value) const
  {
    JsonObjectWriter<h3m::SpecialVictoryConditionBase>{}(out, value);
    out.writeField("coordinates", value.coordinates);
  }

  template<>
  void JsonObjectWriter<h3m::VictoryConditionDetails<h3m::VictoryConditionType::FlagDwellings>>::operator()(
    FieldsWriter& out, const h3m::VictoryConditionDetails<h3m::VictoryConditionType::FlagDwellings>& value) const
  {
    JsonObjectWriter<h3m::SpecialVictoryConditionBase>{}(out, value);
  }

  template<>
  void JsonObjectWriter<h3m::VictoryConditionDetails<h3m::VictoryConditionType::FlagMines>>::operator()(
    FieldsWriter& out, const h3m::VictoryConditionDetails<h3m::VictoryConditionType::FlagMines>& value) const
  {
    JsonObjectWriter<h3m::SpecialVictoryConditionBase>{}(out, value);
  }

  template<>
  void JsonObjectWriter<h3m::VictoryConditionDetails<h3m::VictoryConditionType::TransportArtifact>>::operator()(
    FieldsWriter& out, const h3m::VictoryConditionDetails<h3m::VictoryConditionType::TransportArtifact>& value) const
  {
    JsonObjectWriter<h3m::SpecialVictoryConditionBase>{}(out, value);
    out.writeField("artifact_type", value.artifact_type);
    if (std::string_view enum_str = h3m::getEnumString(static_cast<h3m::ArtifactType>(value.artifact_type));
        !enum_str.empty())
    {
      out.writeComment(enum_str, false);
    }
    out.writeField("destination", value.destination);
  }

  template<>
  void JsonObjectWriter<h3m::VictoryConditionDetails<h3m::VictoryConditionType::DefeatAllMonsters>>::operator()(
    FieldsWriter& out, const h3m::VictoryConditionDetails<h3m::VictoryConditionType::DefeatAllMonsters>& value) const
  {
    JsonObjectWriter<h3m::SpecialVictoryConditionBase>{}(out, value);
  }

  template<>
  void JsonObjectWriter<h3m::VictoryConditionDetails<h3m::VictoryConditionType::SurviveBeyondATimeLimit>>::operator()(
    FieldsWriter& out, const h3m::VictoryConditionDetails<h3m::VictoryConditionType::SurviveBeyondATimeLimit>& value) const
  {
    JsonObjectWriter<h3m::SpecialVictoryConditionBase>{}(out, value);
    out.writeField("days", value.days);
  }

  template<>
  void JsonObjectWriter<h3m::VictoryConditionDetails<h3m::VictoryConditionType::Normal>>::operator()(
    FieldsWriter&, const h3m::VictoryConditionDetails<h3m::VictoryConditionType::Normal>&) const
  {
  }

  void JsonObjectWriter<h3m::VictoryCondition>::operator()(FieldsWriter& out, const h3m::VictoryCondition& value) const
  {
    using Fields = h3json::FieldNames<h3m::VictoryCondition>;
    out.writeField(Fields::kType, value.type());
    out.writeComment(h3m::getEnumString(value.type()), false);
    if (value.type() != h3m::VictoryConditionType::Normal)
    {
      std::visit([&out] <h3m::VictoryConditionType T> (const h3m::VictoryConditionDetails<T>& details)
                 { out.writeField(Fields::kDetails, details); },
                 value.details);
    }
  }
}
