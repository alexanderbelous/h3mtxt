#include <h3mtxt/H3JsonReader/Utils.h>
#include <h3mtxt/H3JsonReader/VariantJsonReader.h>
#include <h3mtxt/JsonCommon/FieldName.h>
#include <h3mtxt/Map/Quest.h>

namespace h3m::H3JsonReader_NS
{
  template<>
  struct JsonReader<QuestDetails<QuestType::None>>
  {
    QuestDetails<QuestType::None> operator()(const Json::Value&) const
    {
      return {};
    }
  };

  template<>
  struct JsonReader<QuestDetails<QuestType::Level>>
  {
    QuestDetails<QuestType::Level> operator()(const Json::Value& value) const
    {
      QuestDetails<QuestType::Level> details;
      readField(details.level, value, "level");
      return details;
    }
  };

  template<>
  struct JsonReader<QuestDetails<QuestType::PrimarySkills>>
  {
    QuestDetails<QuestType::PrimarySkills> operator()(const Json::Value& value) const
    {
      QuestDetails<QuestType::PrimarySkills> details;
      readField(details.skills, value, "skills");
      return details;
    }
  };

  template<>
  struct JsonReader<QuestDetails<QuestType::DefeatHero>>
  {
    QuestDetails<QuestType::DefeatHero> operator()(const Json::Value& value) const
    {
      QuestDetails<QuestType::DefeatHero> details;
      readField(details.absod_id, value, "absod_id");
      return details;
    }
  };

  template<>
  struct JsonReader<QuestDetails<QuestType::DefeatMonster>>
  {
    QuestDetails<QuestType::DefeatMonster> operator()(const Json::Value& value) const
    {
      QuestDetails<QuestType::DefeatMonster> details;
      readField(details.absod_id, value, "absod_id");
      return details;
    }
  };

  template<>
  struct JsonReader<QuestDetails<QuestType::Artifacts>>
  {
    QuestDetails<QuestType::Artifacts> operator()(const Json::Value& value) const
    {
      QuestDetails<QuestType::Artifacts> details;
      readField(details.artifacts, value, "artifacts");
      return details;
    }
  };

  template<>
  struct JsonReader<QuestDetails<QuestType::Creatures>>
  {
    QuestDetails<QuestType::Creatures> operator()(const Json::Value& value) const
    {
      QuestDetails<QuestType::Creatures> details;
      readField(details.creatures, value, "creatures");
      return details;
    }
  };

  template<>
  struct JsonReader<QuestDetails<QuestType::Resources>>
  {
    QuestDetails<QuestType::Resources> operator()(const Json::Value& value) const
    {
      QuestDetails<QuestType::Resources> details;
      readField(details.resources, value, "resources");
      return details;
    }
  };

  template<>
  struct JsonReader<QuestDetails<QuestType::BeHero>>
  {
    QuestDetails<QuestType::BeHero> operator()(const Json::Value& value) const
    {
      QuestDetails<QuestType::BeHero> details;
      readField(details.hero, value, "hero");
      return details;
    }
  };

  template<>
  struct JsonReader<QuestDetails<QuestType::BePlayer>>
  {
    QuestDetails<QuestType::BePlayer> operator()(const Json::Value& value) const
    {
      QuestDetails<QuestType::BePlayer> details;
      readField(details.player, value, "player");
      return details;
    }
  };

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
    }
    readField(quest.deadline, value, Fields::kDeadline);
    readField(quest.proposal, value, Fields::kProposal);
    readField(quest.progress, value, Fields::kProgress);
    readField(quest.completion, value, Fields::kCompletion);
    return quest;
  }
}
