#include <h3mtxt/H3Reader/H3SVGReader/H3SVGReader.h>
#include <h3mtxt/Map/Utils/EnumSequence.h>
#include <h3mtxt/SavedGame/Quest.h>

#include <array>

namespace h3svg
{
  namespace
  {
    using ::h3m::EnumSequence;
    using ::h3m::kNumQuestTypes;
    using ::h3m::MakeEnumSequence;

    template<QuestType T>
    Quest::Details readQuestDetailsAsVariant(const H3SVGReader& reader)
    {
      return Quest::Details{ reader.readQuestDetails<T>() };
    }

    Quest::Details readQuestDetailsVariant(const H3SVGReader& reader, QuestType quest_type)
    {
      // Type of a pointer to a function that takes const H3SVGReader& and returns Quest::Details.
      using ReadQuestDetailsPtr = Quest::Details(*)(const H3SVGReader& reader);
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
  QuestDetails<QuestType::None> H3SVGReader::readQuestDetails() const
  {
    return {};
  }

  template<>
  QuestDetails<QuestType::Level> H3SVGReader::readQuestDetails() const
  {
    return QuestDetails<QuestType::Level> { .level = readInt<std::int16_t>() };
  }

  // TODO: reuse the implementations for h3m::QuestDetails where applicable.
  template<>
  QuestDetails<QuestType::PrimarySkills> H3SVGReader::readQuestDetails() const
  {
    return QuestDetails<QuestType::PrimarySkills> { readPrimarySkills() };
  }

  template<>
  QuestDetails<QuestType::DefeatHero> H3SVGReader::readQuestDetails() const
  {
    QuestDetails<QuestType::DefeatHero> details;
    details.hero = readEnum<HeroType>();
    readBytes(std::span<std::byte, 2>{ details.unknown });
    return details;
  }

  template<>
  QuestDetails<QuestType::DefeatMonster> H3SVGReader::readQuestDetails() const
  {
    QuestDetails<QuestType::DefeatMonster> details;
    details.x = readInt<std::uint16_t>();
    details.y = readInt<std::uint8_t>();
    details.z = readBool();
    details.creature_type = readEnum<CreatureType>();
    details.unknown = static_cast<std::byte>(readInt<std::uint8_t>());
    return details;
  }

  template<>
  QuestDetails<QuestType::Artifacts> H3SVGReader::readQuestDetails() const
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
  QuestDetails<QuestType::Creatures> H3SVGReader::readQuestDetails() const
  {
    QuestDetails<QuestType::Creatures> details;
    const std::uint8_t num_creature_stacks = readInt<std::uint8_t>();
    details.creatures.reserve(num_creature_stacks);
    for (std::uint8_t i = 0; i < num_creature_stacks; ++i)
    {
      QuestDetails<QuestType::Creatures>::Creature creature_stack;
      creature_stack.type = readEnum<CreatureType>();
      creature_stack.count = readInt<std::int32_t>();
      details.creatures.push_back(creature_stack);
    }
    return details;
  }

  template<>
  QuestDetails<QuestType::Resources> H3SVGReader::readQuestDetails() const
  {
    return QuestDetails<QuestType::Resources> { readResources() };
  }

  template<>
  QuestDetails<QuestType::BeHero> H3SVGReader::readQuestDetails() const
  {
    QuestDetails<QuestType::BeHero> details;
    details.hero = readEnum<HeroType>();
    details.unknown = static_cast<std::byte>(readInt<std::uint8_t>());
    return details;
  }

  template<>
  QuestDetails<QuestType::BePlayer> H3SVGReader::readQuestDetails() const
  {
    return QuestDetails<QuestType::BePlayer> { readEnum<PlayerColor>() };
  }

  Quest H3SVGReader::readQuest() const
  {
    Quest quest;
    const QuestType quest_type = readEnum<QuestType>();
    quest.details = readQuestDetailsVariant(*this, quest_type);
    if (quest_type != QuestType::None)
    {
      readBytes(std::span<std::byte, 2>{ quest.unknown });
      quest.deadline = readInt<std::uint32_t>();
      quest.proposal = readString32();
      quest.progress = readString32();
      quest.completion = readString32();
    }
    return quest;
  }
}
