#include <h3mtxt/H3Writer/H3MWriter/H3MWriter.h>
#include <h3mtxt/Map/Quest.h>

namespace h3m
{
  template<>
  void H3MWriter::writeData(const QuestDetails<QuestType::None>&) const
  {
  }

  template<>
  void H3MWriter::writeData(const QuestDetails<QuestType::Level>& data) const
  {
    writeData(data.level);
  }

  template<>
  void H3MWriter::writeData(const QuestDetails<QuestType::PrimarySkills>& data) const
  {
    writeData(data.skills);
  }

  template<>
  void H3MWriter::writeData(const QuestDetails<QuestType::DefeatHero>& data) const
  {
    writeData(data.absod_id);
  }

  template<>
  void H3MWriter::writeData(const QuestDetails<QuestType::DefeatMonster>& data) const
  {
    writeData(data.absod_id);
  }

  template<>
  void H3MWriter::writeData(const QuestDetails<QuestType::Artifacts>& data) const
  {
    writeData(safeCastVectorSize<std::uint8_t>(data.artifacts.size()));
    writeSpan(std::span{ data.artifacts });
  }

  template<>
  void H3MWriter::writeData(const QuestDetails<QuestType::Creatures>& data) const
  {
    writeData(safeCastVectorSize<std::uint8_t>(data.creatures.size()));
    for (const QuestDetails<QuestType::Creatures>::Creature& creature : data.creatures)
    {
      writeData(creature.type);
      writeData(creature.count);
    }
  }

  template<>
  void H3MWriter::writeData(const QuestDetails<QuestType::Resources>& data) const
  {
    writeData(data.resources);
  }

  template<>
  void H3MWriter::writeData(const QuestDetails<QuestType::BeHero>& data) const
  {
    writeData(data.hero);
  }

  template<>
  void H3MWriter::writeData(const QuestDetails<QuestType::BePlayer>& data) const
  {
    writeData(data.player);
  }

  void H3MWriter::writeData(const Quest& quest) const
  {
    writeData(quest.type());
    std::visit([this] <QuestType T> (const QuestDetails<T>& value) { writeData(value); },
               quest.details);
    if (quest.type() != QuestType::None)
    {
      writeData(quest.deadline);
      writeData(quest.proposal);
      writeData(quest.progress);
      writeData(quest.completion);
    }
  }
}
