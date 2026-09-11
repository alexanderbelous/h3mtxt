#include <h3mtxt/H3Writer/H3SVGWriter/H3SVGWriter.h>

#include <h3mtxt/H3Writer/H3MWriter/H3MWriter.h>
#include <h3mtxt/SavedGame/Quest.h>

namespace h3svg
{
  // The default implementation of H3SVGWriter::writeData(const QuestDetails<T>&)
  // reuses H3MWriter.
  template<QuestType T>
  void H3SVGWriter::writeData(const QuestDetails<T>& details) const
  {
    // Sanity checks.
    static_assert(std::is_base_of_v<h3m::QuestDetails<T>, QuestDetails<T>>,
                  "h3svg::QuestDetails<T> must be derived from h3m::QuestDetails<T>.");
    static_assert(sizeof(QuestDetails<T>) == sizeof(h3m::QuestDetails<T>),
                  "h3svg::QuestDetails<T> must have the same size as h3m::QuestDetails<T>.");
    h3m::H3MWriter{ stream_, format() }.writeData(details);
  }

  // Explicit instantiations of H3SVGWriter::writeData(const QuestDetails<T>&)
  // for QuestTypes that use the default template implementation.
  template
  void H3SVGWriter::writeData(const QuestDetails<QuestType::None>&) const;

  template
  void H3SVGWriter::writeData(const QuestDetails<QuestType::PrimarySkills>&) const;

  template
  void H3SVGWriter::writeData(const QuestDetails<QuestType::Artifacts>&) const;

  template
  void H3SVGWriter::writeData(const QuestDetails<QuestType::Resources>&) const;

  template
  void H3SVGWriter::writeData(const QuestDetails<QuestType::BePlayer>&) const;

  // Specializations of H3SVGWriter::writeData(const QuestDetails<T>&).
  template<>
  void H3SVGWriter::writeData(const QuestDetails<QuestType::Level>& details) const
  {
    writeData(details.level);
  }

  template<>
  void H3SVGWriter::writeData(const QuestDetails<QuestType::DefeatHero>& details) const
  {
    writeData(details.hero);
    writeData(details.unknown);
    writeData(details.completed_by);
  }

  template<>
  void H3SVGWriter::writeData(const QuestDetails<QuestType::DefeatMonster>& details) const
  {
    writeData(details.coordinates);
    writeData(details.creature_type);
    writeData(details.completed_by);
  }

  template<>
  void H3SVGWriter::writeData(const QuestDetails<QuestType::Creatures>& details) const
  {
    writeVector<std::uint8_t>(std::span{ details.creatures });
  }

  template<>
  void H3SVGWriter::writeData(const QuestDetails<QuestType::BeHero>& details) const
  {
    writeData(details.hero);
    writeData(details.unknown);
  }

  void H3SVGWriter::writeData(const Quest& quest) const
  {
    writeData(quest.type());
    std::visit([this] <QuestType T> (const QuestDetails<T>& details)
               { writeData(details); },
               quest.details);
  }
}
