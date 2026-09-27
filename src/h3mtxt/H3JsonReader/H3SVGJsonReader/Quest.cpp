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
  h3svg::QuestDetails<T> JsonReader<h3svg::QuestDetails<T>>::operator()(const Json::Value& value) const
  {
    if constexpr (std::is_base_of_v<h3m::QuestDetails<T>, h3svg::QuestDetails<T>> &&
                  sizeof(h3svg::QuestDetails<T>) == sizeof(h3m::QuestDetails<T>))
    {
      // Reuse H3MJsonReader.
      return h3svg::QuestDetails<T>{ fromJson<h3m::QuestDetails<T>>(value) };
    }
    else
    {
      using Fields = FieldNames<h3svg::QuestDetails<T>>;
      h3svg::QuestDetails<T> details;
      if constexpr (T == h3svg::QuestType::Level)
      {
        readField(details.level, value, Fields::kLevel);
      }
      else if constexpr (T == h3svg::QuestType::DefeatHero)
      {
        readField(details.hero, value, Fields::kHero);
        readField(details.unknown, value, Fields::kUnknown);
        readField(details.completed_by, value, Fields::kCompletedBy);
      }
      else if constexpr (T == h3svg::QuestType::DefeatMonster)
      {
        readField(details.coordinates, value, Fields::kCoordinates);
        readField(details.creature_type, value, Fields::kCreatureType);
        readField(details.completed_by, value, Fields::kCompletedBy);
      }
      else if constexpr (T == h3svg::QuestType::Creatures)
      {
        readField(details.creatures, value, Fields::kCreatures);
      }
      else if constexpr (T == h3svg::QuestType::BeHero)
      {
        readField(details.hero, value, Fields::kHero);
        readField(details.unknown, value, Fields::kUnknown);
      }
      else
      {
        static_assert(false, "Invalid QuestType.");
      }
      return details;
    }
  }

  template<>
  h3svg::Quest
  JsonReader<h3svg::Quest>::operator()(const Json::Value& value) const
  {
    using Fields = h3json::FieldNames<h3svg::Quest>;
    const h3svg::QuestType quest_type = readField<h3svg::QuestType>(value, Fields::kType);
    h3svg::Quest quest;
    if (quest_type != h3svg::QuestType::None)
    {
      const std::size_t variant_alternative_idx = h3m::Quest::getAlternativeIdx(quest_type);
      quest.details = VariantJsonReader<h3svg::Quest::Details>{}(getJsonField(value, Fields::kDetails),
                                                                 variant_alternative_idx);
      readField(quest.unknown, value, Fields::kUnknown);
      readField(quest.deadline, value, Fields::kDeadline);
      readField(quest.proposal, value, Fields::kProposal);
      readField(quest.progress, value, Fields::kProgress);
      readField(quest.completion, value, Fields::kCompletion);
    }
    return quest;
  }
}
