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

  template<QuestType T>
  QuestDetails<T> H3SVGReader::readQuestDetails() const
  {
    if constexpr (std::is_base_of_v<h3m::QuestDetails<T>, QuestDetails<T>> &&
                  sizeof(QuestDetails<T>) == sizeof(h3m::QuestDetails<T>))
    {
      // Reuse H3MReader.
      return { h3m::H3MReader{stream_}.readQuestDetails<T>() };
    }
    else
    {
      QuestDetails<T> details;
      if constexpr (T == QuestType::Level)
      {
        details.level = readInt<std::int16_t>();
      }
      else if constexpr (T == QuestType::DefeatHero)
      {
        details.hero = readEnum<HeroType16>();
        details.completed_by = readEnumBitmask<PlayerColor, 1>();
      }
      else if constexpr (T == QuestType::DefeatMonster)
      {
        details.coordinates = readCoordinatesPacked();
        details.creature_type = readEnum<CreatureType>();
        details.completed_by = readEnum<PlayerColor>();
      }
      else if constexpr (T == QuestType::Creatures)
      {
        const std::uint8_t num_creature_stacks = readInt<std::uint8_t>();
        details.creatures.reserve(num_creature_stacks);
        for (std::uint8_t i = 0; i < num_creature_stacks; ++i)
        {
          details.creatures.push_back(readTypedQuantity<CreatureType, std::int32_t>());
        }
      }
      else if constexpr (T == QuestType::BeHero)
      {
        details.hero = readEnum<HeroType16>();
      }
      else
      {
        static_assert(false, "Invalid QuestType.");
      }
      return details;
    }
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
