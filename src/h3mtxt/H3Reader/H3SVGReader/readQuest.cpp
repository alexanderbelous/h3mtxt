#include <h3mtxt/H3Reader/H3SVGReader/H3SVGReader.h>

#include <h3mtxt/H3Reader/H3MReader/H3MReader.h>
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

  // The default implementation reuses H3MReader.
  template<QuestType T>
  QuestDetails<T> H3SVGReader::readQuestDetails() const
  {
    // Sanity checks.
    static_assert(std::is_base_of_v<h3m::QuestDetails<T>, QuestDetails<T>>,
                  "h3svg::QuestDetails<T> must be derived from h3m::QuestDetails<T>.");
    static_assert(sizeof(QuestDetails<T>) == sizeof(h3m::QuestDetails<T>),
                  "h3svg::QuestDetails<T> must have the same size as h3m::QuestDetails<T>.");
    return { h3m::H3MReader{stream_}.readQuestDetails<T>() };
  }

  template
  QuestDetails<QuestType::None> H3SVGReader::readQuestDetails() const;

  template
  QuestDetails<QuestType::PrimarySkills> H3SVGReader::readQuestDetails() const;

  template
  QuestDetails<QuestType::Artifacts> H3SVGReader::readQuestDetails() const;

  template
  QuestDetails<QuestType::Resources> H3SVGReader::readQuestDetails() const;

  template
  QuestDetails<QuestType::BePlayer> H3SVGReader::readQuestDetails() const;

  template<>
  QuestDetails<QuestType::Level> H3SVGReader::readQuestDetails() const
  {
    return QuestDetails<QuestType::Level> { .level = readInt<std::int16_t>() };
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
  QuestDetails<QuestType::BeHero> H3SVGReader::readQuestDetails() const
  {
    QuestDetails<QuestType::BeHero> details;
    details.hero = readEnum<HeroType>();
    details.unknown = readInt<std::uint8_t>();
    return details;
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
