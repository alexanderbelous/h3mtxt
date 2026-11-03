#include <h3mtxt/H3JsonReader/H3SVGJsonReader/H3SVGJsonReader.h>

#include <h3mtxt/H3JsonReader/H3JsonReaderBase/H3JsonReaderBase.h>
#include <h3mtxt/H3JsonReader/H3JsonReaderBase/VariantJsonReader.h>
#include <h3mtxt/H3JsonReader/H3MJsonReader/H3MJsonReader.h>
#include <h3mtxt/JsonCommon/FieldNamesH3SVG.h>
#include <h3mtxt/SavedGame/Quest.h>

#include <type_traits>

namespace h3json
{
  template<h3svg::QuestType T>
  h3svg::QuestDetails<T> JsonReader2<h3svg::QuestDetails<T>>::operator()() const
  {
    if constexpr (std::is_base_of_v<h3m::QuestDetails<T>, h3svg::QuestDetails<T>> &&
                  sizeof(h3svg::QuestDetails<T>) == sizeof(h3m::QuestDetails<T>))
    {
      // Reuse H3MJsonReader.
      return h3svg::QuestDetails<T>{ fromJson<h3m::QuestDetails<T>>(value()) };
    }
    else
    {
      using Fields = FieldNames<h3svg::QuestDetails<T>>;
      h3svg::QuestDetails<T> details;
      if constexpr (T == h3svg::QuestType::Level)
      {
        readField(Fields::kLevel, details.level);
      }
      else if constexpr (T == h3svg::QuestType::DefeatHero)
      {
        readField(Fields::kHero, details.hero);
        readField(Fields::kCompletedBy, details.completed_by);
      }
      else if constexpr (T == h3svg::QuestType::DefeatMonster)
      {
        readField(Fields::kCoordinates, details.coordinates);
        readField(Fields::kCreatureType, details.creature_type);
        readField(Fields::kCompletedBy, details.completed_by);
      }
      else if constexpr (T == h3svg::QuestType::Creatures)
      {
        readField(Fields::kCreatures, details.creatures);
      }
      else if constexpr (T == h3svg::QuestType::BeHero)
      {
        readField(Fields::kHero, details.hero);
      }
      else
      {
        static_assert(false, "Invalid QuestType.");
      }
      return details;
    }
  }

  template<>
  h3svg::Quest JsonReader2<h3svg::Quest>::operator()() const
  {
    using Fields = h3json::FieldNames<h3svg::Quest>;
    const h3svg::QuestType quest_type = readField<h3svg::QuestType>(Fields::kType);
    h3svg::Quest quest;
    if (quest_type != h3svg::QuestType::None)
    {
      const std::size_t variant_alternative_idx = h3m::Quest::getAlternativeIdx(quest_type);
      quest.details = VariantJsonReader<h3svg::Quest::Details>{}(getField(Fields::kDetails),
                                                                 variant_alternative_idx);
      readField(Fields::kUnknown, quest.unknown);
      readField(Fields::kDeadline, quest.deadline);
      readField(Fields::kProposal, quest.proposal);
      readField(Fields::kProgress, quest.progress);
      readField(Fields::kCompletion, quest.completion);
    }
    return quest;
  }
}
