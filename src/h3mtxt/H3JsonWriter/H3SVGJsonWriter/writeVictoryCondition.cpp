#include <h3mtxt/H3JsonWriter/H3SVGJsonWriter/H3SVGJsonWriter.h>

#include <h3mtxt/H3JsonWriter/H3MJsonWriter/H3MJsonWriter.h>
#include <h3mtxt/H3JsonWriter/H3MJsonWriter/getEnumString.h>
#include <h3mtxt/H3JsonWriter/H3SVGJsonWriter/getEnumString.h>
#include <h3mtxt/JsonCommon/FieldNamesH3SVG.h>
#include <h3mtxt/SavedGame/VictoryCondition.h>
#include <h3mtxt/Medea/Medea.h>

namespace Medea_NS
{
  namespace
  {
    // TODO: reuse the code from H3MJsonWriter.
    void writeSpecialVictoryConditionBase(FieldsWriter& out, const h3svg::SpecialVictoryConditionBase& base)
    {
      out.writeField("allow_normal_win", base.allow_normal_win);
      out.writeField("applies_to_computer", base.applies_to_computer);
    }
  }

  template<>
  void JsonObjectWriter<h3svg::VictoryConditionDetails<h3svg::VictoryConditionType::AcquireArtifact>>::operator()(
    FieldsWriter& out,
    const h3svg::VictoryConditionDetails<h3svg::VictoryConditionType::AcquireArtifact>& details) const
  {
    writeSpecialVictoryConditionBase(out, details);
    out.writeField("artifact_type", details.artifact_type);
    if (std::string_view enum_str = getEnumString(details.artifact_type); !enum_str.empty())
    {
      out.writeComment(enum_str, false);
    }
  }

  template<>
  void JsonObjectWriter<h3svg::VictoryConditionDetails<h3svg::VictoryConditionType::AccumulateCreatures>>::operator()(
    FieldsWriter& out,
    const h3svg::VictoryConditionDetails<h3svg::VictoryConditionType::AccumulateCreatures>& details) const
  {
    writeSpecialVictoryConditionBase(out, details);
    out.writeField("creature_type", details.creature_type);
    if (std::string_view enum_str = getEnumString(details.creature_type); !enum_str.empty())
    {
      out.writeComment(enum_str, false);
    }
    out.writeField("count", details.count);
  }

  template<>
  void JsonObjectWriter<h3svg::VictoryConditionDetails<h3svg::VictoryConditionType::AccumulateResources>>::operator()(
    FieldsWriter& out,
    const h3svg::VictoryConditionDetails<h3svg::VictoryConditionType::AccumulateResources>& details) const
  {
    // TODO: reuse the code from H3MJsonWriter.
    writeSpecialVictoryConditionBase(out, details);
    out.writeField("resource_type", details.resource_type);
    if (std::string_view enum_str = getEnumString(details.resource_type); !enum_str.empty())
    {
      out.writeComment(enum_str, false);
    }
    out.writeField("amount", details.amount);
  }

  template<>
  void JsonObjectWriter<h3svg::VictoryConditionDetails<h3svg::VictoryConditionType::UpgradeTown>>::operator()(
    FieldsWriter& out,
    const h3svg::VictoryConditionDetails<h3svg::VictoryConditionType::UpgradeTown>& details) const
  {
    // TODO: reuse the code from H3MJsonWriter.
    writeSpecialVictoryConditionBase(out, details);
    out.writeField("coordinates", details.coordinates);
    out.writeField("hall_level", details.hall_level);
    out.writeField("castle_level", details.castle_level);
  }

  template<>
  void JsonObjectWriter<h3svg::VictoryConditionDetails<h3svg::VictoryConditionType::BuildGrail>>::operator()(
    FieldsWriter& out,
    const h3svg::VictoryConditionDetails<h3svg::VictoryConditionType::BuildGrail>& details) const
  {
    // TODO: reuse the code from H3MJsonWriter.
    writeSpecialVictoryConditionBase(out, details);
    out.writeField("coordinates", details.coordinates);
  }

  template<>
  void JsonObjectWriter<h3svg::VictoryConditionDetails<h3svg::VictoryConditionType::DefeatHero>>::operator()(
    FieldsWriter& out,
    const h3svg::VictoryConditionDetails<h3svg::VictoryConditionType::DefeatHero>& details) const
  {
    writeSpecialVictoryConditionBase(out, details);
    out.writeField("hero", details.hero);
    if (std::string_view enum_str = getEnumString(details.hero); !enum_str.empty())
    {
      out.writeComment(enum_str, false);
    }
  }

  template<>
  void JsonObjectWriter<h3svg::VictoryConditionDetails<h3svg::VictoryConditionType::CaptureTown>>::operator()(
    FieldsWriter& out,
    const h3svg::VictoryConditionDetails<h3svg::VictoryConditionType::CaptureTown>& details) const
  {
    // TODO: reuse the code from H3MJsonWriter.
    writeSpecialVictoryConditionBase(out, details);
    out.writeField("coordinates", details.coordinates);
  }

  template<>
  void JsonObjectWriter<h3svg::VictoryConditionDetails<h3svg::VictoryConditionType::DefeatMonster>>::operator()(
    FieldsWriter& out,
    const h3svg::VictoryConditionDetails<h3svg::VictoryConditionType::DefeatMonster>& details) const
  {
    // TODO: reuse the code from H3MJsonWriter.
    writeSpecialVictoryConditionBase(out, details);
    out.writeField("coordinates", details.coordinates);
  }

  template<>
  void JsonObjectWriter<h3svg::VictoryConditionDetails<h3svg::VictoryConditionType::FlagDwellings>>::operator()(
    FieldsWriter& out,
    const h3svg::VictoryConditionDetails<h3svg::VictoryConditionType::FlagDwellings>& details) const
  {
    // TODO: reuse the code from H3MJsonWriter.
    writeSpecialVictoryConditionBase(out, details);
  }

  template<>
  void JsonObjectWriter<h3svg::VictoryConditionDetails<h3svg::VictoryConditionType::FlagMines>>::operator()(
    FieldsWriter& out,
    const h3svg::VictoryConditionDetails<h3svg::VictoryConditionType::FlagMines>& details) const
  {
    // TODO: reuse the code from H3MJsonWriter.
    writeSpecialVictoryConditionBase(out, details);
  }

  template<>
  void JsonObjectWriter<h3svg::VictoryConditionDetails<h3svg::VictoryConditionType::TransportArtifact>>::operator()(
    FieldsWriter& out,
    const h3svg::VictoryConditionDetails<h3svg::VictoryConditionType::TransportArtifact>& details) const
  {
    // TODO: reuse the code from H3MJsonWriter.
    writeSpecialVictoryConditionBase(out, details);
    out.writeField("artifact_type", details.artifact_type);
    if (std::string_view enum_str = getEnumString(static_cast<h3m::ArtifactType>(details.artifact_type));
      !enum_str.empty())
    {
      out.writeComment(enum_str, false);
    }
    out.writeField("destination", details.destination);
  }

  template<>
  void JsonObjectWriter<h3svg::VictoryConditionDetails<h3svg::VictoryConditionType::DefeatAllMonsters>>::operator()(
    FieldsWriter& out,
    const h3svg::VictoryConditionDetails<h3svg::VictoryConditionType::DefeatAllMonsters>& details) const
  {
    // TODO: reuse the code from H3MJsonWriter.
    writeSpecialVictoryConditionBase(out, details);
  }

  template<>
  void JsonObjectWriter<h3svg::VictoryConditionDetails<h3svg::VictoryConditionType::SurviveBeyondATimeLimit>>::operator()(
    FieldsWriter& out, const h3svg::VictoryConditionDetails<h3svg::VictoryConditionType::SurviveBeyondATimeLimit>& details) const
  {
    // TODO: reuse the code from H3MJsonWriter.
    writeSpecialVictoryConditionBase(out, details);
    out.writeField("days", details.days);
  }

  template<>
  void JsonObjectWriter<h3svg::VictoryConditionDetails<h3svg::VictoryConditionType::Normal>>::operator()(
    FieldsWriter&, const h3svg::VictoryConditionDetails<h3svg::VictoryConditionType::Normal>&) const
  {
  }

  void JsonObjectWriter<h3svg::VictoryCondition>::operator()(FieldsWriter& out,
                                                             const h3svg::VictoryCondition& victory_condition) const
  {
    using Fields = h3json::FieldNames<h3svg::VictoryCondition>;
    out.writeField(Fields::kType, victory_condition.type());
    out.writeComment(getEnumString(victory_condition.type()), false);
    if (victory_condition.type() != h3svg::VictoryConditionType::Normal)
    {
      std::visit([&out] <h3svg::VictoryConditionType T> (const h3svg::VictoryConditionDetails<T>& details)
                 { out.writeField(Fields::kDetails, details); },
                 victory_condition.details);
    }
  }
}
