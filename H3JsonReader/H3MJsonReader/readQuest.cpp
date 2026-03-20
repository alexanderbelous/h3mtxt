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

  template<>
  QuestDetails<QuestType::None>
  JsonReader<QuestDetails<QuestType::None>>::operator()(const Json::Value&) const
  {
    return {};
  }

  template<>
  QuestDetails<QuestType::Level>
  JsonReader<QuestDetails<QuestType::Level>>::operator()(const Json::Value& value) const
  {
    QuestDetails<QuestType::Level> details;
    readField(details.level, value, "level");
    return details;
  }

  template<>
  QuestDetails<QuestType::PrimarySkills>
  JsonReader<QuestDetails<QuestType::PrimarySkills>>::operator()(const Json::Value& value) const
  {
    QuestDetails<QuestType::PrimarySkills> details;
    readField(details.skills, value, "skills");
    return details;
  }

  template<>
  QuestDetails<QuestType::DefeatHero>
  JsonReader<QuestDetails<QuestType::DefeatHero>>::operator()(const Json::Value& value) const
  {
    QuestDetails<QuestType::DefeatHero> details;
    readField(details.absod_id, value, "absod_id");
    return details;
  }

  template<>
  QuestDetails<QuestType::DefeatMonster>
  JsonReader<QuestDetails<QuestType::DefeatMonster>>::operator()(const Json::Value& value) const
  {
    QuestDetails<QuestType::DefeatMonster> details;
    readField(details.absod_id, value, "absod_id");
    return details;
  }

  template<>
  QuestDetails<QuestType::Artifacts>
  JsonReader<QuestDetails<QuestType::Artifacts>>::operator()(const Json::Value& value) const
  {
    QuestDetails<QuestType::Artifacts> details;
    readField(details.artifacts, value, "artifacts");
    return details;
  }

  template<>
  struct JsonReader<QuestDetails<QuestType::Creatures>::Creature>
  {
    QuestDetails<QuestType::Creatures>::Creature operator()(const Json::Value& value) const
    {
      QuestDetails<QuestType::Creatures>::Creature creature;
      readField(creature.type, value, "type");
      readField(creature.count, value, "count");
      return creature;
    }
  };

  template<>
  QuestDetails<QuestType::Creatures>
  JsonReader<QuestDetails<QuestType::Creatures>>::operator()(const Json::Value& value) const
  {
    QuestDetails<QuestType::Creatures> details;
    readField(details.creatures, value, "creatures");
    return details;
  }

  template<>
  QuestDetails<QuestType::Resources>
  JsonReader<QuestDetails<QuestType::Resources>>::operator()(const Json::Value& value) const
  {
    QuestDetails<QuestType::Resources> details;
    readField(details.resources, value, "resources");
    return details;
  }

  template<>
  QuestDetails<QuestType::BeHero>
  JsonReader<QuestDetails<QuestType::BeHero>>::operator()(const Json::Value& value) const
  {
    QuestDetails<QuestType::BeHero> details;
    readField(details.hero, value, "hero");
    return details;
  }

  template<>
  QuestDetails<QuestType::BePlayer>
  JsonReader<QuestDetails<QuestType::BePlayer>>::operator()(const Json::Value& value) const
  {
    QuestDetails<QuestType::BePlayer> details;
    readField(details.player, value, "player");
    return details;
  }

  Quest JsonReader<Quest>::operator()(const Json::Value& value) const
  {
    using Fields = FieldNames<Quest>;
    Quest quest;
    const QuestType quest_type = readField<QuestType>(value, Fields::kType);
    if (quest_type != QuestType::None)
    {
      VariantJsonReader<Quest::Details> variant_reader {};
      quest.details = variant_reader(getJsonField(value, Fields::kDetails),
                                     Quest::getAlternativeIdx(quest_type));
      readField(quest.deadline, value, Fields::kDeadline);
      readField(quest.proposal, value, Fields::kProposal);
      readField(quest.progress, value, Fields::kProgress);
      readField(quest.completion, value, Fields::kCompletion);
    }
    return quest;
  }
}
