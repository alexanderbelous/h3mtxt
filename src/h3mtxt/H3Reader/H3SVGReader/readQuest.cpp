#include <h3mtxt/H3Reader/H3SVGReader/H3SVGReader.h>
#include <h3mtxt/Map/Utils/SwitchStatement.h>
#include <h3mtxt/SavedGame/Quest.h>

namespace h3svg
{
  namespace
  {
    using ::h3m::kNumQuestTypes;

    template<QuestType T>
    Quest::Details readQuestDetailsAsVariant(const H3SVGReader& reader)
    {
      return Quest::Details{ reader.readQuestDetails<T>() };
    }

    template<QuestType T>
    using QuestDetailsReaderTemplateAlias = SwitchStatement_NS::StaticConstant<&readQuestDetailsAsVariant<T>>;

    Quest::Details readQuestDetailsVariant(const H3SVGReader& reader, QuestType quest_type)
    {
      static constexpr auto switch_statement =
        SwitchStatement_NS::generateSwitchStatement<QuestType,
                                                    kNumQuestTypes,
                                                    QuestDetailsReaderTemplateAlias>();
      return switch_statement(quest_type, reader);
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
    details.unknown = readInt<std::uint8_t>();
    details.completed_by = readEnumBitmask<PlayerColor, 1>();
    return details;
  }

  template<>
  QuestDetails<QuestType::DefeatMonster> H3SVGReader::readQuestDetails() const
  {
    QuestDetails<QuestType::DefeatMonster> details;
    details.coordinates = readCoordinatesPacked();
    details.creature_type = readEnum<CreatureType>();
    details.completed_by = readEnum<PlayerColor>();
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
      details.creatures.push_back(readTypedQuantity<CreatureType, std::int32_t>());
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
    details.unknown = readInt<std::uint8_t>();
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
      quest.unknown = readByteArray<2>();
      quest.deadline = readInt<std::uint32_t>();
      quest.proposal = readString32();
      quest.progress = readString32();
      quest.completion = readString32();
    }
    return quest;
  }
}
