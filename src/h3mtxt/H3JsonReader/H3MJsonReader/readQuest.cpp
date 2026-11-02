#include <h3mtxt/H3JsonReader/H3MJsonReader/H3MJsonReader.h>

#include <h3mtxt/H3JsonReader/H3JsonReaderBase/H3JsonReaderBase.h>
#include <h3mtxt/H3JsonReader/H3JsonReaderBase/VariantJsonReader.h>
#include <h3mtxt/JsonCommon/FieldNamesH3M.h>
#include <h3mtxt/Map/Quest.h>

namespace h3json
{
  using ::h3m::Quest;
  using ::h3m::QuestDetails;
  using ::h3m::QuestType;

  template<QuestType T>
  QuestDetails<T> JsonReader2<QuestDetails<T>>::operator()() const
  {
    using Fields = FieldNames<QuestDetails<T>>;
    QuestDetails<T> details;
    if constexpr (T == QuestType::None)
    {
      // No fields.
    }
    else if constexpr (T == QuestType::Level)
    {
      readField(Fields::kLevel, details.level);
    }
    else if constexpr (T == QuestType::PrimarySkills)
    {
      readField(Fields::kSkills, details.skills);
    }
    else if constexpr (T == QuestType::DefeatHero)
    {
      readField(Fields::kAbsodId, details.absod_id);
    }
    else if constexpr (T == QuestType::DefeatMonster)
    {
      readField(Fields::kAbsodId, details.absod_id);
    }
    else if constexpr (T == QuestType::Artifacts)
    {
      readField(Fields::kArtifacts, details.artifacts);
    }
    else if constexpr (T == QuestType::Creatures)
    {
      readField(Fields::kCreatures, details.creatures);
    }
    else if constexpr (T == QuestType::Resources)
    {
      readField(Fields::kResources, details.resources);
    }
    else if constexpr (T == QuestType::BeHero)
    {
      readField(Fields::kHero, details.hero);
    }
    else if constexpr (T == QuestType::BePlayer)
    {
      readField(Fields::kPlayer, details.player);
    }
    else
    {
      static_assert(false, "Invalid QuestType.");
    }
    return details;
  }

  template<>
  Quest JsonReader2<Quest>::operator()() const
  {
    using Fields = FieldNames<Quest>;
    Quest quest;
    const QuestType quest_type = readField<QuestType>(Fields::kType);
    if (quest_type != QuestType::None)
    {
      quest.details = VariantJsonReader<Quest::Details>{}(getField(Fields::kDetails),
                                                          Quest::getAlternativeIdx(quest_type));
      readField(Fields::kDeadline, quest.deadline);
      readField(Fields::kProposal, quest.proposal);
      readField(Fields::kProgress, quest.progress);
      readField(Fields::kCompletion, quest.completion);
    }
    return quest;
  }
}
