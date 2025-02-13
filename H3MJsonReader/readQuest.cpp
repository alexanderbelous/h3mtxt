#include <h3mtxt/H3MJsonReader/readQuest.h>

#include <h3mtxt/Map/Utils/EnumSequence.h>

#include <array>

namespace h3m
{
  namespace
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
    Quest::Details readQuestDetailsVariant(const Json::Value& value, QuestType quest_type)
    {
      // Type of a pointer to a function that takes const Json::Value& and returns Quest::Details.
      using ReadQuestDetailsPtr = Quest::Details(*)(const Json::Value&);
      // Generate (at compile time) an array of function pointers for each instantiation of
      // readQuestDetailsAsVariant() ordered by QuestType.
      constexpr std::array<ReadQuestDetailsPtr, kNumQuestTypes> kQuestDetailsReaders =
        [] <QuestType... quest_types>
        (EnumSequence<QuestType, quest_types...> seq)
        consteval
        {
          return std::array<ReadQuestDetailsPtr, sizeof...(quest_types)>
          {
            &readQuestDetailsAsVariant<quest_types>...
          };
        }(MakeEnumSequence<QuestType, kNumQuestTypes>{});
      // Invoke a function from the generated array.
      return kQuestDetailsReaders.at(static_cast<std::size_t>(quest_type))(value);
    }
  }

  Quest JsonReader<Quest>::operator()(const Json::Value& value) const
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
      quest.details = readQuestDetailsVariant(*details_json, quest_type);
    }
    readField(quest.deadline, value, Fields::kDeadline);
    readField(quest.proposal, value, Fields::kProposal);
    readField(quest.progress, value, Fields::kProgress);
    readField(quest.completion, value, Fields::kCompletion);
    return quest;
  }
}