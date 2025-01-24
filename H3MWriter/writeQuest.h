#pragma once

#include <h3mtxt/H3MWriter/H3MWriter.h>
#include <h3mtxt/H3MWriter/writeCreatureStack.h>
#include <h3mtxt/H3MWriter/writePrimarySkills.h>
#include <h3mtxt/H3MWriter/writeResources.h>
#include <h3mtxt/Map/Quest.h>

namespace h3m
{
  template<>
  struct H3MWriter<QuestDetails<QuestType::None>>
  {
    void operator()(std::ostream& stream, const QuestDetails<QuestType::None>& data) const
    {
    }
  };

  template<>
  struct H3MWriter<QuestDetails<QuestType::Level>>
  {
    void operator()(std::ostream& stream, const QuestDetails<QuestType::Level>& data) const
    {
      writeData(stream, data.level);
    }
  };

  template<>
  struct H3MWriter<QuestDetails<QuestType::PrimarySkills>>
  {
    void operator()(std::ostream& stream, const QuestDetails<QuestType::PrimarySkills>& data) const
    {
      writeData(stream, data.skills);
    }
  };

  template<>
  struct H3MWriter<QuestDetails<QuestType::DefeatHero>>
  {
    void operator()(std::ostream& stream, const QuestDetails<QuestType::DefeatHero>& data) const
    {
      writeData(stream, data.absod_id);
    }
  };

  template<>
  struct H3MWriter<QuestDetails<QuestType::DefeatMonster>>
  {
    void operator()(std::ostream& stream, const QuestDetails<QuestType::DefeatMonster>& data) const
    {
      writeData(stream, data.absod_id);
    }
  };

  template<>
  struct H3MWriter<QuestDetails<QuestType::Artifacts>>
  {
    void operator()(std::ostream& stream, const QuestDetails<QuestType::Artifacts>& data) const
    {
      writeVector<std::uint8_t>(stream, data.artifacts);
    }
  };

  template<>
  struct H3MWriter<QuestDetails<QuestType::Creatures>>
  {
    void operator()(std::ostream& stream, const QuestDetails<QuestType::Creatures>& data) const
    {
      writeVector<std::uint8_t>(stream, data.creatures);
    }
  };

  template<>
  struct H3MWriter<QuestDetails<QuestType::Resources>>
  {
    void operator()(std::ostream& stream, const QuestDetails<QuestType::Resources>& data) const
    {
      writeData(stream, data.resources);
    }
  };

  template<>
  struct H3MWriter<QuestDetails<QuestType::BeHero>>
  {
    void operator()(std::ostream& stream, const QuestDetails<QuestType::BeHero>& data) const
    {
      writeData(stream, data.hero);
    }
  };

  template<>
  struct H3MWriter<QuestDetails<QuestType::BePlayer>>
  {
    void operator()(std::ostream& stream, const QuestDetails<QuestType::BePlayer>& data) const
    {
      writeData(stream, data.player);
    }
  };

  template<>
  struct H3MWriter<Quest>
  {
    void operator()(std::ostream& stream, const Quest& quest) const
    {
      writeData(stream, quest.type());
      std::visit([&stream](auto&& value) { writeData(stream, std::forward<decltype(value)>(value)); },
                 quest.details);
      if (quest.type() != QuestType::None)
      {
        writeData(stream, quest.deadline);
        writeData(stream, quest.proposal);
        writeData(stream, quest.progress);
        writeData(stream, quest.completion);
      }
    }
  };
}
