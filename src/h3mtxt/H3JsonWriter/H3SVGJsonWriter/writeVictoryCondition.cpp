#include <h3mtxt/H3JsonWriter/H3SVGJsonWriter/H3SVGJsonWriter.h>

#include <h3mtxt/H3JsonWriter/H3MJsonWriter/H3MJsonWriter.h>
#include <h3mtxt/H3JsonWriter/H3MJsonWriter/getEnumString.h>
#include <h3mtxt/H3JsonWriter/H3SVGJsonWriter/getEnumString.h>
#include <h3mtxt/JsonCommon/FieldNamesH3SVG.h>
#include <h3mtxt/SavedGame/VictoryCondition.h>
#include <h3mtxt/Medea/Medea.h>

#include <type_traits>

namespace Medea_NS
{
  template<h3svg::VictoryConditionType T>
  void JsonObjectWriter<h3svg::VictoryConditionDetails<T>>::operator()(
    FieldsWriter& out, const h3svg::VictoryConditionDetails<T>& details) const
  {
    // Sanity checks.
    static_assert(std::is_base_of_v<h3m::VictoryConditionDetails<T>, h3svg::VictoryConditionDetails<T>>,
                  "h3svg::VictoryConditionDetails<T> must be derived from h3m::VictoryConditionDetails<T>.");
    static_assert(sizeof(h3svg::VictoryConditionDetails<T>) == sizeof(h3m::VictoryConditionDetails<T>),
                  "h3svg::VictoryConditionDetails<T> must have the same size as h3m::VictoryConditionDetails<T>.");
    // Reuse the code from H3MJsonWriter.
    JsonObjectWriter<h3m::VictoryConditionDetails<T>>{}(out, details);
  }

  // Explicit instantiations for VictoryConditionTypes that use the default template implementation.
  //
  // Technically, these are redundant because JsonObjectWriter<h3svg::VictoryCondition> will instantiate them anyway.
  // However, I'm not sure how reliable that is: e.g., if the compiler inlines everything in
  // JsonObjectWriter<h3svg::VictoryCondition>, is it guaranteed that these instantiations will still be found
  // by the linker?
  //
  // Safer to explicitly instantiate them.
  template
  void JsonObjectWriter<h3svg::VictoryConditionDetails<h3svg::VictoryConditionType::AccumulateResources>>::operator()(
    FieldsWriter& out, const h3svg::VictoryConditionDetails<h3svg::VictoryConditionType::AccumulateResources>& details) const;

  template
  void JsonObjectWriter<h3svg::VictoryConditionDetails<h3svg::VictoryConditionType::UpgradeTown>>::operator()(
    FieldsWriter& out,
    const h3svg::VictoryConditionDetails<h3svg::VictoryConditionType::UpgradeTown>& details) const;

  template
  void JsonObjectWriter<h3svg::VictoryConditionDetails<h3svg::VictoryConditionType::BuildGrail>>::operator()(
    FieldsWriter& out,
    const h3svg::VictoryConditionDetails<h3svg::VictoryConditionType::BuildGrail>& details) const;

  template
  void JsonObjectWriter<h3svg::VictoryConditionDetails<h3svg::VictoryConditionType::CaptureTown>>::operator()(
    FieldsWriter& out,
    const h3svg::VictoryConditionDetails<h3svg::VictoryConditionType::CaptureTown>& details) const;

  template
  void JsonObjectWriter<h3svg::VictoryConditionDetails<h3svg::VictoryConditionType::DefeatMonster>>::operator()(
    FieldsWriter& out,
    const h3svg::VictoryConditionDetails<h3svg::VictoryConditionType::DefeatMonster>& details) const;

  template
  void JsonObjectWriter<h3svg::VictoryConditionDetails<h3svg::VictoryConditionType::FlagDwellings>>::operator()(
    FieldsWriter& out,
    const h3svg::VictoryConditionDetails<h3svg::VictoryConditionType::FlagDwellings>& details) const;

  template
  void JsonObjectWriter<h3svg::VictoryConditionDetails<h3svg::VictoryConditionType::FlagMines>>::operator()(
    FieldsWriter& out,
    const h3svg::VictoryConditionDetails<h3svg::VictoryConditionType::FlagMines>& details) const;

  template
  void JsonObjectWriter<h3svg::VictoryConditionDetails<h3svg::VictoryConditionType::TransportArtifact>>::operator()(
    FieldsWriter& out,
    const h3svg::VictoryConditionDetails<h3svg::VictoryConditionType::TransportArtifact>& details) const;

  template
  void JsonObjectWriter<h3svg::VictoryConditionDetails<h3svg::VictoryConditionType::DefeatAllMonsters>>::operator()(
    FieldsWriter& out,
    const h3svg::VictoryConditionDetails<h3svg::VictoryConditionType::DefeatAllMonsters>& details) const;

  template
  void JsonObjectWriter<h3svg::VictoryConditionDetails<h3svg::VictoryConditionType::SurviveBeyondATimeLimit>>::operator()(
    FieldsWriter& out,
    const h3svg::VictoryConditionDetails<h3svg::VictoryConditionType::SurviveBeyondATimeLimit>& details) const;

  template
  void JsonObjectWriter<h3svg::VictoryConditionDetails<h3svg::VictoryConditionType::Normal>>::operator()(
    FieldsWriter& out,
    const h3svg::VictoryConditionDetails<h3svg::VictoryConditionType::Normal>& details) const;

  // Specializations.

  template<>
  void JsonObjectWriter<h3svg::VictoryConditionDetails<h3svg::VictoryConditionType::AcquireArtifact>>::operator()(
    FieldsWriter& out,
    const h3svg::VictoryConditionDetails<h3svg::VictoryConditionType::AcquireArtifact>& details) const
  {
    JsonObjectWriter<h3svg::SpecialVictoryConditionBase>{}(out, details);
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
    JsonObjectWriter<h3svg::SpecialVictoryConditionBase>{}(out, details);
    out.writeField("creature_type", details.creature_type);
    if (std::string_view enum_str = getEnumString(details.creature_type); !enum_str.empty())
    {
      out.writeComment(enum_str, false);
    }
    out.writeField("count", details.count);
  }

  template<>
  void JsonObjectWriter<h3svg::VictoryConditionDetails<h3svg::VictoryConditionType::DefeatHero>>::operator()(
    FieldsWriter& out,
    const h3svg::VictoryConditionDetails<h3svg::VictoryConditionType::DefeatHero>& details) const
  {
    JsonObjectWriter<h3svg::SpecialVictoryConditionBase>{}(out, details);
    out.writeField("hero", details.hero);
    if (std::string_view enum_str = getEnumString(details.hero); !enum_str.empty())
    {
      out.writeComment(enum_str, false);
    }
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
