#include <h3mtxt/H3Reader/H3MReader/H3MReader.h>
#include <h3mtxt/Map/Utils/SwitchStatement.h>
#include <h3mtxt/Map/Quest.h>

namespace h3m
{
  namespace
  {
    // Function template that wraps H3MReader::readQuestDetails(), returning the result as Quest::Details variant.
    template<QuestType T>
    Quest::Details readQuestDetailsAsVariant(const H3MReader& reader)
    {
      return reader.readQuestDetails<T>();
    }

    // Convert the function template readQuestDetailsAsVariant<T>() into an alias template,
    // so that it can be passed as a template template parameter to generateSwitchStatement().
    template<QuestType T>
    using QuestDetailsReaderTemplateAlias = SwitchStatement_NS::StaticConstant<&readQuestDetailsAsVariant<T>>;
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
      details.creatures.push_back(readTypedQuantity<CreatureType, std::uint16_t>());
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
    // Generate a switch statement for all valid QuestType constants.
    // read_quest_details(N, reader) will trigger readQuestDetailsAsVariant<N>(reader).
    static constexpr auto read_quest_details =
      SwitchStatement_NS::generateSwitchStatement<QuestType, kNumQuestTypes, QuestDetailsReaderTemplateAlias>();

    Quest quest;
    const QuestType quest_type = readEnum<QuestType>();
    quest.details = read_quest_details(quest_type, *this);
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
