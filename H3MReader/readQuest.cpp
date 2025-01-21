#include <h3mtxt/H3MReader/readQuest.h>

#include <h3mtxt/H3MReader/readCreatureStack.h>
#include <h3mtxt/H3MReader/readPrimarySkills.h>
#include <h3mtxt/H3MReader/readResources.h>
#include <h3mtxt/H3MReader/Utils.h>
#include <h3mtxt/Map/Quest.h>

#include <array>
#include <type_traits>

namespace h3m
{
  namespace
  {
    template<QuestType T>
    QuestDetails<T> readQuestDetails(std::istream& stream)
    {
      static_assert(false, "Missing specialization for readQuestDetails<T>().");
    }

    template<>
    QuestDetails<QuestType::None> readQuestDetails<QuestType::None>(std::istream& stream)
    {
      return {};
    }

    template<>
    QuestDetails<QuestType::Level> readQuestDetails<QuestType::Level>(std::istream& stream)
    {
      QuestDetails<QuestType::Level> details;
      details.level = readUint<std::uint32_t>(stream);
      return details;
    }

    template<>
    QuestDetails<QuestType::PrimarySkills> readQuestDetails<QuestType::PrimarySkills>(std::istream& stream)
    {
      QuestDetails<QuestType::PrimarySkills> details;
      details.skills = readPrimarySkills(stream);;
      return details;
    }

    template<>
    QuestDetails<QuestType::DefeatHero> readQuestDetails<QuestType::DefeatHero>(std::istream& stream)
    {
      QuestDetails<QuestType::DefeatHero> details;
      details.absod_id = readUint<std::uint32_t>(stream);
      return details;
    }

    template<>
    QuestDetails<QuestType::DefeatMonster> readQuestDetails<QuestType::DefeatMonster>(std::istream& stream)
    {
      QuestDetails<QuestType::DefeatMonster> details;
      details.absod_id = readUint<std::uint32_t>(stream);
      return details;
    }

    template<>
    QuestDetails<QuestType::Artifacts> readQuestDetails<QuestType::Artifacts>(std::istream& stream)
    {
      QuestDetails<QuestType::Artifacts> details;
      const std::uint8_t num_artifacts = readUint8(stream);
      details.artifacts.reserve(num_artifacts);
      for (std::uint8_t i = 0; i < num_artifacts; ++i)
      {
        details.artifacts.push_back(readEnum<ArtifactType>(stream));
      }
      return details;
    }

    template<>
    QuestDetails<QuestType::Creatures> readQuestDetails<QuestType::Creatures>(std::istream& stream)
    {
      QuestDetails<QuestType::Creatures> details;
      const std::uint8_t num_creatures = readUint8(stream);
      details.creatures.reserve(num_creatures);
      for (std::uint8_t i = 0; i < num_creatures; ++i)
      {
        details.creatures.push_back(readCreatureStack(stream));
      }
      return details;
    }

    template<>
    QuestDetails<QuestType::Resources> readQuestDetails<QuestType::Resources>(std::istream& stream)
    {
      QuestDetails<QuestType::Resources> details;
      details.resources = readResources<std::uint32_t>(stream);
      return details;
    }

    template<>
    QuestDetails<QuestType::BeHero> readQuestDetails<QuestType::BeHero>(std::istream& stream)
    {
      QuestDetails<QuestType::BeHero> details;
      details.hero = readEnum<HeroType>(stream);
      return details;
    }

    template<>
    QuestDetails<QuestType::BePlayer> readQuestDetails<QuestType::BePlayer>(std::istream& stream)
    {
      QuestDetails<QuestType::BePlayer> details;
      details.player = readEnum<PlayerColor>(stream);
      return details;
    }

    // Wrapper around readQuestDetails(), which returns the result as Quest::Details variant.
    template<QuestType T>
    Quest::Details readQuestDetailsAsVariant(std::istream& stream)
    {
      return readQuestDetails<T>(stream);
    }

    // Reads QuestDetails for the specified QuestType.
    // \param stream - input stream.
    // \param quest_type - type of the quest.
    // \return the deserialized data as Quest::Details.
    Quest::Details readQuestDetailsVariant(std::istream& stream, QuestType quest_type)
    {
      // The underlying integer type for QuestType.
      using QuestTypeIdx = std::underlying_type_t<QuestType>;

      // Type of a pointer to a function that takes std::istream& and returns Quest::Details.
      using ReadQuestDetailsPtr = Quest::Details(*)(std::istream& stream);

      // Generate (at compile time) an array of function pointers for each instantiation of
      // readQuestDetails() ordered by QuestType.
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
      return kQuestDetailsReaders.at(static_cast<QuestTypeIdx>(quest_type))(stream);
    }
  }

  Quest readQuest(std::istream& stream)
  {
    Quest quest;
    const QuestType quest_type = readEnum<QuestType>(stream);
    quest.details = readQuestDetailsVariant(stream, quest_type);
    if (quest_type != QuestType::None)
    {
      quest.deadline = readUint<std::uint32_t>(stream);
      quest.proposal = readString(stream);
      quest.progress = readString(stream);
      quest.completion = readString(stream);
    }
    return quest;
  }
}