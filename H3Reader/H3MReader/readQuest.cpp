#include <h3mtxt/H3Reader/H3MReader/H3MReader.h>
#include <h3mtxt/Map/Quest.h>
#include <h3mtxt/Map/Utils/EnumSequence.h>

#include <array>
#include <type_traits>

namespace h3m
{
  namespace
  {
    // Wrapper around H3MReader::readQuestDetails(), which returns the result as Quest::Details variant.
    template<QuestType T>
    Quest::Details readQuestDetailsAsVariant(const H3MReader& reader)
    {
      return reader.readQuestDetails<T>();
    }

    // Reads QuestDetails for the specified QuestType.
    // \param reader - input stream.
    // \param quest_type - type of the quest.
    // \return the deserialized data as Quest::Details.
    Quest::Details readQuestDetailsVariant(const H3MReader& reader, QuestType quest_type)
    {
      // Type of a pointer to a function that takes const H3MReader& and returns Quest::Details.
      using ReadQuestDetailsPtr = Quest::Details(*)(const H3MReader& reader);
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
      return kQuestDetailsReaders.at(static_cast<std::size_t>(quest_type))(reader);
    }
  }

  template<>
  QuestDetails<QuestType::None> H3MReader::readQuestDetails<QuestType::None>() const
  {
    return {};
  }

  template<>
  QuestDetails<QuestType::Level> H3MReader::readQuestDetails<QuestType::Level>() const
  {
    QuestDetails<QuestType::Level> details;
    details.level = readInt<std::int32_t>();
    return details;
  }

  template<>
  QuestDetails<QuestType::PrimarySkills> H3MReader::readQuestDetails<QuestType::PrimarySkills>() const
  {
    QuestDetails<QuestType::PrimarySkills> details;
    details.skills = readPrimarySkills();;
    return details;
  }

  template<>
  QuestDetails<QuestType::DefeatHero> H3MReader::readQuestDetails<QuestType::DefeatHero>() const
  {
    QuestDetails<QuestType::DefeatHero> details;
    details.absod_id = readInt<std::uint32_t>();
    return details;
  }

  template<>
  QuestDetails<QuestType::DefeatMonster> H3MReader::readQuestDetails<QuestType::DefeatMonster>() const
  {
    QuestDetails<QuestType::DefeatMonster> details;
    details.absod_id = readInt<std::uint32_t>();
    return details;
  }

  template<>
  QuestDetails<QuestType::Artifacts> H3MReader::readQuestDetails<QuestType::Artifacts>() const
  {
    QuestDetails<QuestType::Artifacts> details;
    const std::uint8_t num_artifacts = readInt<std::uint8_t>();
    details.artifacts.reserve(num_artifacts);
    for (std::uint8_t i = 0; i < num_artifacts; ++i)
    {
      details.artifacts.push_back(readEnum<ArtifactType>());
    }
    return details;
  }

  template<>
  QuestDetails<QuestType::Creatures> H3MReader::readQuestDetails<QuestType::Creatures>() const
  {
    QuestDetails<QuestType::Creatures> details;
    const std::uint8_t num_creatures = readInt<std::uint8_t>();
    details.creatures.reserve(num_creatures);
    for (std::uint8_t i = 0; i < num_creatures; ++i)
    {
      QuestDetails<QuestType::Creatures>::Creature creature;
      creature.type = readEnum<CreatureType>();
      creature.count = readInt<std::uint16_t>();
      details.creatures.push_back(std::move(creature));
    }
    return details;
  }

  template<>
  QuestDetails<QuestType::Resources> H3MReader::readQuestDetails<QuestType::Resources>() const
  {
    QuestDetails<QuestType::Resources> details;
    details.resources = readResources();
    return details;
  }

  template<>
  QuestDetails<QuestType::BeHero> H3MReader::readQuestDetails<QuestType::BeHero>() const
  {
    QuestDetails<QuestType::BeHero> details;
    details.hero = readEnum<HeroType>();
    return details;
  }

  template<>
  QuestDetails<QuestType::BePlayer> H3MReader::readQuestDetails<QuestType::BePlayer>() const
  {
    QuestDetails<QuestType::BePlayer> details;
    details.player = readEnum<PlayerColor>();
    return details;
  }

  Quest H3MReader::readQuest() const
  {
    Quest quest;
    const QuestType quest_type = readEnum<QuestType>();
    quest.details = readQuestDetailsVariant(*this, quest_type);
    if (quest_type != QuestType::None)
    {
      quest.deadline = readInt<std::uint32_t>();
      quest.proposal = readString32();
      quest.progress = readString32();
      quest.completion = readString32();
    }
    return quest;
  }
}
