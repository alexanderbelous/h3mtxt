#include <h3mtxt/H3SvgReader/H3SvgReader.h>
#include <h3mtxt/Map/Utils/EnumSequence.h>
#include <h3mtxt/SavedGame/QuestSvg.h>

#include <array>

namespace h3svg
{
  namespace
  {
    using ::h3m::EnumSequence;
    using ::h3m::kNumQuestTypes;
    using ::h3m::MakeEnumSequence;

    template<QuestType T>
    QuestSvg::Details readQuestDetailsAsVariant(const H3SvgReader& reader)
    {
      return QuestSvg::Details{ reader.readQuestDetails<T>() };
    }

    QuestSvg::Details readQuestDetailsVariant(const H3SvgReader& reader, QuestType quest_type)
    {
      // Type of a pointer to a function that takes const H3SvgReader& and returns QuestSvg::Details.
      using ReadQuestDetailsPtr = QuestSvg::Details(*)(const H3SvgReader& reader);
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
  QuestDetailsSvg<QuestType::None> H3SvgReader::readQuestDetails() const
  {
    return {};
  }

  template<>
  QuestDetailsSvg<QuestType::Level> H3SvgReader::readQuestDetails() const
  {
    return QuestDetailsSvg<QuestType::Level> { .level = readInt<std::int16_t>() };
  }

  // TODO: reuse the implementations for h3m::QuestDetails where applicable.
  template<>
  QuestDetailsSvg<QuestType::PrimarySkills> H3SvgReader::readQuestDetails() const
  {
    return QuestDetailsSvg<QuestType::PrimarySkills> { readPrimarySkills() };
  }

  template<>
  QuestDetailsSvg<QuestType::DefeatHero> H3SvgReader::readQuestDetails() const
  {
    QuestDetailsSvg<QuestType::DefeatHero> details;
    details.hero = readEnum<HeroType>();
    readBytes(std::span<std::byte, 2>{ details.unknown });
    return details;
  }

  template<>
  QuestDetailsSvg<QuestType::DefeatMonster> H3SvgReader::readQuestDetails() const
  {
    QuestDetailsSvg<QuestType::DefeatMonster> details;
    details.x = readInt<std::uint16_t>();
    details.y = readInt<std::uint8_t>();
    details.z = readBool();
    details.creature_type = readEnum<CreatureType>();
    details.unknown = static_cast<std::byte>(readInt<std::uint8_t>());
    return details;
  }

  template<>
  QuestDetailsSvg<QuestType::Artifacts> H3SvgReader::readQuestDetails() const
  {
    QuestDetailsSvg<QuestType::Artifacts> details;
    const std::uint8_t num_artifacts = readInt<std::uint8_t>();
    details.artifacts.reserve(num_artifacts);
    for (std::uint8_t i = 0; i < num_artifacts; ++i)
    {
      details.artifacts.push_back(readEnum<ArtifactType>());
    }
    return details;
  }

  template<>
  QuestDetailsSvg<QuestType::Creatures> H3SvgReader::readQuestDetails() const
  {
    QuestDetailsSvg<QuestType::Creatures> details;
    const std::uint8_t num_creature_stacks = readInt<std::uint8_t>();
    details.creatures.reserve(num_creature_stacks);
    for (std::uint8_t i = 0; i < num_creature_stacks; ++i)
    {
      QuestDetailsSvg<QuestType::Creatures>::Creature creature_stack;
      creature_stack.type = readEnum<CreatureType>();
      creature_stack.count = readInt<std::int32_t>();
      details.creatures.push_back(creature_stack);
    }
    return details;
  }

  template<>
  QuestDetailsSvg<QuestType::Resources> H3SvgReader::readQuestDetails() const
  {
    return QuestDetailsSvg<QuestType::Resources> { readResources() };
  }

  template<>
  QuestDetailsSvg<QuestType::BeHero> H3SvgReader::readQuestDetails() const
  {
    QuestDetailsSvg<QuestType::BeHero> details;
    details.hero = readEnum<HeroType>();
    details.unknown = static_cast<std::byte>(readInt<std::uint8_t>());
    return details;
  }

  template<>
  QuestDetailsSvg<QuestType::BePlayer> H3SvgReader::readQuestDetails() const
  {
    return QuestDetailsSvg<QuestType::BePlayer> { readEnum<PlayerColor>() };
  }

  QuestSvg H3SvgReader::readQuest() const
  {
    QuestSvg quest;
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
