#include <h3mtxt/H3Writer/H3SVGWriter/H3SVGWriter.h>

#include <h3mtxt/H3Writer/H3MWriter/H3MWriter.h>
#include <h3mtxt/SavedGame/Quest.h>

namespace h3svg
{
  template<QuestType T>
  void H3SVGWriter::writeData(const QuestDetails<T>& details) const
  {
    if constexpr (T == QuestType::Level)
    {
      writeData(details.level);
    }
    else if constexpr (T == QuestType::DefeatHero)
    {
      writeData(details.hero);
      writeData(details.completed_by);
    }
    else if constexpr (T == QuestType::DefeatMonster)
    {
      writeData(details.coordinates);
      writeData(details.creature_type);
      writeData(details.completed_by);
    }
    else if constexpr (T == QuestType::Creatures)
    {
      writeVector<std::uint8_t>(std::span{ details.creatures });
    }
    else if constexpr (T == QuestType::BeHero)
    {
      writeData(details.hero);
    }
    else
    {
      // Sanity checks.
      static_assert(std::is_base_of_v<h3m::QuestDetails<T>, QuestDetails<T>>,
                    "h3svg::QuestDetails<T> must be derived from h3m::QuestDetails<T>.");
      static_assert(sizeof(QuestDetails<T>) == sizeof(h3m::QuestDetails<T>),
                    "h3svg::QuestDetails<T> must have the same size as h3m::QuestDetails<T>.");
      // Reuse H3MWriter.
      h3m::H3MWriter{ stream_, format() }.writeData(details);
    }
  }

  void H3SVGWriter::writeData(const Quest& quest) const
  {
    writeData(quest.type());
    std::visit([this] <QuestType T> (const QuestDetails<T>& details)
               { writeData(details); },
               quest.details);
    if (quest.type() != QuestType::None)
    {
      writeData(quest.unknown);
      writeData(quest.deadline);
      writeString32(quest.proposal);
      writeString32(quest.progress);
      writeString32(quest.completion);
    }
  }
}
