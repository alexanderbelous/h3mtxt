#include <h3mtxt/H3JsonWriter/H3SVGJsonWriter/H3SVGJsonWriter.h>

#include <h3mtxt/H3JsonWriter/H3MJsonWriter/H3MJsonWriter.h>
#include <h3mtxt/H3JsonWriter/H3MJsonWriter/Utils.h>
#include <h3mtxt/JsonCommon/FieldNamesH3SVG.h>
#include <h3mtxt/Medea/Medea.h>
#include <h3mtxt/SavedGame/Quest.h>

namespace Medea_NS
{
  // TODO: reuse the implementations for h3m::QuestDetails where applicable.

  void JsonObjectWriter<h3svg::QuestDetails<h3svg::QuestType::None>>::operator()(
    FieldsWriter&, const h3svg::QuestDetails<h3svg::QuestType::None>&) const
  {
  }

  void JsonObjectWriter<h3svg::QuestDetails<h3svg::QuestType::Level>>::operator()(
    FieldsWriter& out, const h3svg::QuestDetails<h3svg::QuestType::Level>& details) const
  {
    using Fields = h3json::FieldNames<h3svg::QuestDetails<h3svg::QuestType::Level>>;
    out.writeField(Fields::kLevel, details.level);
  }

  void JsonObjectWriter<h3svg::QuestDetails<h3svg::QuestType::PrimarySkills>>::operator()(
    FieldsWriter& out, const h3svg::QuestDetails<h3svg::QuestType::PrimarySkills>& details) const
  {
    JsonObjectWriter<h3m::QuestDetails<h3m::QuestType::PrimarySkills>>{}(out, details);
  }

  void JsonObjectWriter<h3svg::QuestDetails<h3svg::QuestType::DefeatHero>>::operator()(
    FieldsWriter& out, const h3svg::QuestDetails<h3svg::QuestType::DefeatHero>& details) const
  {
    using Fields = h3json::FieldNames<h3svg::QuestDetails<h3svg::QuestType::DefeatHero>>;
    out.writeField(Fields::kHero, details.hero);
    out.writeField(Fields::kUnknown, details.unknown);
    out.writeField(Fields::kCompletedBy, details.completed_by);
  }

  void JsonObjectWriter<h3svg::QuestDetails<h3svg::QuestType::DefeatMonster>>::operator()(
    FieldsWriter& out, const h3svg::QuestDetails<h3svg::QuestType::DefeatMonster>& details) const
  {
    using Fields = h3json::FieldNames<h3svg::QuestDetails<h3svg::QuestType::DefeatMonster>>;
    out.writeField(Fields::kCoordinates, details.coordinates);
    out.writeField(Fields::kCreatureType, details.creature_type);
    out.writeField(Fields::kCompletedBy, details.completed_by);
  }

  void JsonObjectWriter<h3svg::QuestDetails<h3svg::QuestType::Artifacts>>::operator()(
    FieldsWriter& out, const h3svg::QuestDetails<h3svg::QuestType::Artifacts>& details) const
  {
    JsonObjectWriter<h3m::QuestDetails<h3m::QuestType::Artifacts>>{}(out, details);
  }

  void JsonObjectWriter<h3svg::QuestDetails<h3svg::QuestType::Creatures>>::operator()(
    FieldsWriter& out, const h3svg::QuestDetails<h3svg::QuestType::Creatures>& details) const
  {
    using Fields = h3json::FieldNames<h3svg::QuestDetails<h3svg::QuestType::Creatures>>;
    out.writeField(Fields::kCreatures, details.creatures);
  }

  void JsonObjectWriter<h3svg::QuestDetails<h3svg::QuestType::Resources>>::operator()(
    FieldsWriter& out, const h3svg::QuestDetails<h3svg::QuestType::Resources>& details) const
  {
    JsonObjectWriter<h3m::QuestDetails<h3m::QuestType::Resources>>{}(out, details);
  }

  void JsonObjectWriter<h3svg::QuestDetails<h3svg::QuestType::BeHero>>::operator()(
    FieldsWriter& out, const h3svg::QuestDetails<h3svg::QuestType::BeHero>& details) const
  {
    using Fields = h3json::FieldNames<h3svg::QuestDetails<h3svg::QuestType::BeHero>>;
    out.writeField(Fields::kHero, details.hero);
    out.writeField(Fields::kUnknown, details.unknown);
  }

  void JsonObjectWriter<h3svg::QuestDetails<h3svg::QuestType::BePlayer>>::operator()(
    FieldsWriter& out, const h3svg::QuestDetails<h3svg::QuestType::BePlayer>& details) const
  {
    JsonObjectWriter<h3m::QuestDetails<h3m::QuestType::BePlayer>>{}(out, details);
  }

  void JsonObjectWriter<h3svg::Quest>::operator()(FieldsWriter& out, const h3svg::Quest& quest) const
  {
    using Fields = h3json::FieldNames<h3svg::Quest>;
    out.writeField(Fields::kType, quest.type());
    if (quest.type() != h3svg::QuestType::None)
    {
      std::visit([&out] <h3svg::QuestType T> (const h3svg::QuestDetails<T>& details)
                 {
                   out.writeField(Fields::kDetails, details);
                 },
                 quest.details);
      out.writeField(Fields::kUnknown, quest.unknown);
      out.writeField(Fields::kDeadline, quest.deadline);
      out.writeField(Fields::kProposal, quest.proposal);
      out.writeField(Fields::kProgress, quest.progress);
      out.writeField(Fields::kCompletion, quest.completion);
    }
  }
}
