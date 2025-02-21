#include <h3mtxt/H3Writer/H3Writer.h>
#include <h3mtxt/H3Writer/Utils.h>
#include <h3mtxt/Map/Quest.h>

namespace h3m
{
  template<>
  struct H3Writer<QuestDetails<QuestType::None>>
  {
    void operator()(std::ostream&, const QuestDetails<QuestType::None>&) const
    {
    }
  };

  template<>
  struct H3Writer<QuestDetails<QuestType::Level>>
  {
    void operator()(std::ostream& stream, const QuestDetails<QuestType::Level>& data) const
    {
      writeData(stream, data.level);
    }
  };

  template<>
  struct H3Writer<QuestDetails<QuestType::PrimarySkills>>
  {
    void operator()(std::ostream& stream, const QuestDetails<QuestType::PrimarySkills>& data) const
    {
      writeData(stream, data.skills);
    }
  };

  template<>
  struct H3Writer<QuestDetails<QuestType::DefeatHero>>
  {
    void operator()(std::ostream& stream, const QuestDetails<QuestType::DefeatHero>& data) const
    {
      writeData(stream, data.absod_id);
    }
  };

  template<>
  struct H3Writer<QuestDetails<QuestType::DefeatMonster>>
  {
    void operator()(std::ostream& stream, const QuestDetails<QuestType::DefeatMonster>& data) const
    {
      writeData(stream, data.absod_id);
    }
  };

  template<>
  struct H3Writer<QuestDetails<QuestType::Artifacts>>
  {
    void operator()(std::ostream& stream, const QuestDetails<QuestType::Artifacts>& data) const
    {
      writeVector<std::uint8_t>(stream, data.artifacts);
    }
  };

  template<>
  struct H3Writer<QuestDetails<QuestType::Creatures>>
  {
    void operator()(std::ostream& stream, const QuestDetails<QuestType::Creatures>& data) const
    {
      writeVector<std::uint8_t>(stream, data.creatures);
    }
  };

  template<>
  struct H3Writer<QuestDetails<QuestType::Resources>>
  {
    void operator()(std::ostream& stream, const QuestDetails<QuestType::Resources>& data) const
    {
      writeData(stream, data.resources);
    }
  };

  template<>
  struct H3Writer<QuestDetails<QuestType::BeHero>>
  {
    void operator()(std::ostream& stream, const QuestDetails<QuestType::BeHero>& data) const
    {
      writeData(stream, data.hero);
    }
  };

  template<>
  struct H3Writer<QuestDetails<QuestType::BePlayer>>
  {
    void operator()(std::ostream& stream, const QuestDetails<QuestType::BePlayer>& data) const
    {
      writeData(stream, data.player);
    }
  };

  void H3Writer<Quest>::operator()(std::ostream& stream, const Quest& quest) const
  {
    writeData(stream, quest.type());
    std::visit([&stream] <QuestType T> (const QuestDetails<T>& value) { writeData(stream, value); },
               quest.details);
    if (quest.type() != QuestType::None)
    {
      writeData(stream, quest.deadline);
      writeData(stream, quest.proposal);
      writeData(stream, quest.progress);
      writeData(stream, quest.completion);
    }
  }
}
