#include <h3mtxt/H3Reader/H3Reader.h>
#include <h3mtxt/H3Reader/Utils.h>
#include <h3mtxt/Map/Quest.h>
#include <h3mtxt/Map/Utils/EnumSequence.h>

#include <array>
#include <type_traits>

namespace h3m::H3Reader_NS
{
  namespace
  {
    template<QuestType T>
    QuestDetails<T> readQuestDetails(std::istream& stream)
    {
      static_assert(false, "Missing specialization for readQuestDetails<T>().");
    }

    template<>
    QuestDetails<QuestType::None> readQuestDetails<QuestType::None>(std::istream&)
    {
      return {};
    }

    template<>
    QuestDetails<QuestType::Level> readQuestDetails<QuestType::Level>(std::istream& stream)
    {
      QuestDetails<QuestType::Level> details;
      details.level = readInt<std::uint32_t>(stream);
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
      details.absod_id = readInt<std::uint32_t>(stream);
      return details;
    }

    template<>
    QuestDetails<QuestType::DefeatMonster> readQuestDetails<QuestType::DefeatMonster>(std::istream& stream)
    {
      QuestDetails<QuestType::DefeatMonster> details;
      details.absod_id = readInt<std::uint32_t>(stream);
      return details;
    }

    template<>
    QuestDetails<QuestType::Artifacts> readQuestDetails<QuestType::Artifacts>(std::istream& stream)
    {
      QuestDetails<QuestType::Artifacts> details;
      const std::uint8_t num_artifacts = readInt<std::uint8_t>(stream);
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
      const std::uint8_t num_creatures = readInt<std::uint8_t>(stream);
      details.creatures.reserve(num_creatures);
      for (std::uint8_t i = 0; i < num_creatures; ++i)
      {
        QuestDetails<QuestType::Creatures>::Creature creature;
        creature.type = readEnum<CreatureType>(stream);
        creature.count = readInt<std::uint16_t>(stream);
        details.creatures.push_back(std::move(creature));
      }
      return details;
    }

    template<>
    QuestDetails<QuestType::Resources> readQuestDetails<QuestType::Resources>(std::istream& stream)
    {
      QuestDetails<QuestType::Resources> details;
      details.resources = readResources(stream);
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
      // Type of a pointer to a function that takes std::istream& and returns Quest::Details.
      using ReadQuestDetailsPtr = Quest::Details(*)(std::istream& stream);
      // Generate (at compile time) an array of function pointers for each instantiation of
      // readQuestDetails() ordered by QuestType.
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
      return kQuestDetailsReaders.at(static_cast<std::size_t>(quest_type))(stream);
    }
  }

  Quest readQuest(std::istream& stream)
  {
    Quest quest;
    const QuestType quest_type = readEnum<QuestType>(stream);
    quest.details = readQuestDetailsVariant(stream, quest_type);
    if (quest_type != QuestType::None)
    {
      quest.deadline = readInt<std::uint32_t>(stream);
      quest.proposal = readString(stream);
      quest.progress = readString(stream);
      quest.completion = readString(stream);
    }
    return quest;
  }
}