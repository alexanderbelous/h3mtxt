#pragma once

#include <h3mtxt/JsonCommon/FieldName.h>
#include <h3mtxt/H3MJsonReader/JsonReader.h>
#include <h3mtxt/H3MJsonReader/readCreatureStack.h>
#include <h3mtxt/H3MJsonReader/readResources.h>
#include <h3mtxt/Map/Quest.h>

#include <array>
#include <type_traits>

namespace h3m
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

  namespace H3MJsonReader_NS
  {
    // Wrapper around JsonReader<QuestDetails<T>>, which returns the result as Quest::Details variant.
    template<QuestType T>
    Quest::Details readQuestDetailsAsVariant(const Json::Value& value)
    {
      return JsonReader<QuestDetails<T>>{}(value);
    }

    // Reads QuestDetails for the specified QuestType.
    // \param value - input JSON.
    // \param quest_type - type of the quest.
    // \return the deserialized data as Quest::Details.
    inline Quest::Details readQuestDetailsVariant(const Json::Value& value, QuestType quest_type)
    {
      // The underlying integer type for QuestType.
      using QuestTypeIdx = std::underlying_type_t<QuestType>;
      // Type of a pointer to a function that takes const Json::Value& and returns Quest::Details.
      using ReadQuestDetailsPtr = Quest::Details(*)(const Json::Value&);
      // Generate (at compile time) an array of function pointers for each instantiation of
      // readQuestDetailsAsVariant() ordered by QuestType.
      constexpr
        std::array<ReadQuestDetailsPtr, kNumQuestTypes> kQuestDetailsReaders =
        [] <QuestTypeIdx... quest_type_idx>
        (std::integer_sequence<QuestTypeIdx, quest_type_idx...> seq)
        consteval
      {
        return std::array<ReadQuestDetailsPtr, sizeof...(quest_type_idx)>
        {
          &readQuestDetailsAsVariant<static_cast<QuestType>(quest_type_idx)>...
        };
      }(std::make_integer_sequence<QuestTypeIdx, kNumQuestTypes>{});
      // Invoke a function from the generated array.
      return kQuestDetailsReaders.at(static_cast<QuestTypeIdx>(quest_type))(value);
    }
  }

  template<>
  struct JsonReader<Quest>
  {
    Quest operator()(const Json::Value& value) const
    {
      using Fields = FieldNames<Quest>;
      Quest quest;
      const QuestType quest_type = readField<QuestType>(value, Fields::kType);
      if (quest_type != QuestType::None)
      {
        const Json::Value* details_json = value.find(
          Fields::kDetails.data(), Fields::kDetails.data() + Fields::kDetails.size());
        if (!details_json)
        {
          throw MissingJsonFieldError(Fields::kDetails);
        }
        quest.details = H3MJsonReader_NS::readQuestDetailsVariant(*details_json, quest_type);
      }
      readField(quest.deadline, value, Fields::kDeadline);
      readField(quest.proposal, value, Fields::kProposal);
      readField(quest.progress, value, Fields::kProgress);
      readField(quest.completion, value, Fields::kCompletion);
      return quest;
    }
  };
}