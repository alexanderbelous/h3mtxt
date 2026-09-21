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
    // Sanity checks
    static_assert(std::is_base_of_v<h3m::QuestDetails<T>, h3svg::QuestDetails<T>>,
                  "h3svg::QuestDetails<T> must be derived from h3m::QuestDetails<T>.");
    static_assert(sizeof(h3svg::QuestDetails<T>) == sizeof(h3m::QuestDetails<T>),
                  "h3svg::QuestDetails<T> must have the same size as h3m::QuestDetails<T>.");
    return h3svg::QuestDetails<T>{ fromJson<h3m::QuestDetails<T>>(value) };
  }

  // Explicit instantiations for QuestTypes that use the default implementation.
  template
  h3svg::QuestDetails<h3svg::QuestType::None>
  JsonReader<h3svg::QuestDetails<h3svg::QuestType::None>>::operator()(const Json::Value& value) const;

  template
  h3svg::QuestDetails<h3svg::QuestType::PrimarySkills>
  JsonReader<h3svg::QuestDetails<h3svg::QuestType::PrimarySkills>>::operator()(const Json::Value& value) const;

  template
  h3svg::QuestDetails<h3svg::QuestType::Artifacts>
  JsonReader<h3svg::QuestDetails<h3svg::QuestType::Artifacts>>::operator()(const Json::Value& value) const;

  template
  h3svg::QuestDetails<h3svg::QuestType::Resources>
  JsonReader<h3svg::QuestDetails<h3svg::QuestType::Resources>>::operator()(const Json::Value& value) const;

  template
  h3svg::QuestDetails<h3svg::QuestType::BePlayer>
  JsonReader<h3svg::QuestDetails<h3svg::QuestType::BePlayer>>::operator()(const Json::Value& value) const;

  // Specializations for QuestTypes that don't use the default implementation.
  template<>
  h3svg::QuestDetails<h3svg::QuestType::Level>
  JsonReader<h3svg::QuestDetails<h3svg::QuestType::Level>>::operator()(const Json::Value& value) const
  {
    using Fields = FieldNames<h3svg::QuestDetails<h3svg::QuestType::Level>>;
    h3svg::QuestDetails<h3svg::QuestType::Level> details;
    readField(details.level, value, Fields::kLevel);
    return details;
  }

  template<>
  h3svg::QuestDetails<h3svg::QuestType::DefeatHero>
  JsonReader<h3svg::QuestDetails<h3svg::QuestType::DefeatHero>>::operator()(const Json::Value& value) const
  {
    using Fields = FieldNames<h3svg::QuestDetails<h3svg::QuestType::DefeatHero>>;
    h3svg::QuestDetails<h3svg::QuestType::DefeatHero> details;
    readField(details.hero, value, Fields::kHero);
    readField(details.unknown, value, Fields::kUnknown);
    readField(details.completed_by, value, Fields::kCompletedBy);
    return details;
  }

  template<>
  h3svg::QuestDetails<h3svg::QuestType::DefeatMonster>
  JsonReader<h3svg::QuestDetails<h3svg::QuestType::DefeatMonster>>::operator()(const Json::Value& value) const
  {
    using Fields = FieldNames<h3svg::QuestDetails<h3svg::QuestType::DefeatMonster>>;
    h3svg::QuestDetails<h3svg::QuestType::DefeatMonster> details;
    readField(details.coordinates, value, Fields::kCoordinates);
    readField(details.creature_type, value, Fields::kCreatureType);
    readField(details.completed_by, value, Fields::kCompletedBy);
    return details;
  }

  template<>
  h3svg::QuestDetails<h3svg::QuestType::Creatures>
  JsonReader<h3svg::QuestDetails<h3svg::QuestType::Creatures>>::operator()(const Json::Value& value) const
  {
    using Fields = FieldNames<h3svg::QuestDetails<h3svg::QuestType::Creatures>>;
    h3svg::QuestDetails<h3svg::QuestType::Creatures> details;
    readField(details.creatures, value, Fields::kCreatures);
    return details;
  }

  template<>
  h3svg::QuestDetails<h3svg::QuestType::BeHero>
  JsonReader<h3svg::QuestDetails<h3svg::QuestType::BeHero>>::operator()(const Json::Value& value) const
  {
    using Fields = FieldNames<h3svg::QuestDetails<h3svg::QuestType::BeHero>>;
    h3svg::QuestDetails<h3svg::QuestType::BeHero> details;
    readField(details.hero, value, Fields::kHero);
    readField(details.unknown, value, Fields::kUnknown);
    return details;
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
