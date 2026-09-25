#include <h3mtxt/H3JsonWriter/H3SVGJsonWriter/H3SVGJsonWriter.h>

#include <h3mtxt/H3JsonWriter/H3MJsonWriter/H3MJsonWriter.h>
#include <h3mtxt/H3JsonWriter/H3MJsonWriter/Utils.h>
#include <h3mtxt/JsonCommon/FieldNamesH3SVG.h>
#include <h3mtxt/Medea/Medea.h>
#include <h3mtxt/SavedGame/Quest.h>

#include <type_traits>

namespace Medea_NS
{
  template<h3svg::QuestType T>
  void JsonObjectWriter<h3svg::QuestDetails<T>>::operator()(FieldsWriter& out,
                                                            const h3svg::QuestDetails<T>& details) const
  {
    using Fields = h3json::FieldNames<h3svg::QuestDetails<T>>;

    if constexpr (T == h3svg::QuestType::Level)
    {
      out.writeField(Fields::kLevel, details.level);
    }
    else if constexpr (T == h3svg::QuestType::DefeatHero)
    {
      out.writeField(Fields::kHero, details.hero);
      out.writeField(Fields::kUnknown, details.unknown);
      out.writeField(Fields::kCompletedBy, details.completed_by);
    }
    else if constexpr (T == h3svg::QuestType::DefeatMonster)
    {
      out.writeField(Fields::kCoordinates, details.coordinates);
      out.writeField(Fields::kCreatureType, details.creature_type);
      out.writeField(Fields::kCompletedBy, details.completed_by);
    }
    else if constexpr (T == h3svg::QuestType::Creatures)
    {
      out.writeField(Fields::kCreatures, details.creatures);
    }
    else if constexpr (T == h3svg::QuestType::BeHero)
    {
      out.writeField(Fields::kHero, details.hero);
      out.writeField(Fields::kUnknown, details.unknown);
    }
    else
    {
      static_assert(std::is_base_of_v<h3m::QuestDetails<T>, h3svg::QuestDetails<T>>,
                    "h3svg::QuestDetails<T> must be derived from h3m::QuestDetails<T>.");
      static_assert(sizeof(h3svg::QuestDetails<T>) == sizeof(h3m::QuestDetails<T>),
                    "h3svg::QuestDetails<T> must have the same size as h3m::QuestDetails<T>.");
      JsonObjectWriter<h3m::QuestDetails<T>>{}(out, details);
    }
  }

  template<>
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
