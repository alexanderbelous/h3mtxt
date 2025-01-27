#pragma once

#include <h3mtxt/Map/Quest.h>
#include <h3mtxt/H3MTxtWriter/getEnumString.h>
#include <h3mtxt/H3MTxtWriter/H3MTxtWriter.h>
#include <h3mtxt/H3MTxtWriter/writeCreatureStack.h>
#include <h3mtxt/H3MTxtWriter/writePrimarySkills.h>
#include <h3mtxt/H3MTxtWriter/writeResources.h>

namespace Util_NS
{
  template<>
  struct StructWriter<h3m::QuestDetails<h3m::QuestType::None>>
  {
    void operator()(FieldsWriter&, const h3m::QuestDetails<h3m::QuestType::None>&) const
    {
    }
  };

  template<>
  struct StructWriter<h3m::QuestDetails<h3m::QuestType::Level>>
  {
    void operator()(FieldsWriter& out, const h3m::QuestDetails<h3m::QuestType::Level>& details) const
    {
      out.writeField("level", details.level);
    }
  };

  template<>
  struct StructWriter<h3m::QuestDetails<h3m::QuestType::PrimarySkills>>
  {
    void operator()(FieldsWriter& out, const h3m::QuestDetails<h3m::QuestType::PrimarySkills>& details) const
    {
      out.writeField("skills", details.skills);
    }
  };

  template<>
  struct StructWriter<h3m::QuestDetails<h3m::QuestType::DefeatHero>>
  {
    void operator()(FieldsWriter& out, const h3m::QuestDetails<h3m::QuestType::DefeatHero>& details) const
    {
      out.writeField("absod_id", details.absod_id);
    }
  };

  template<>
  struct StructWriter<h3m::QuestDetails<h3m::QuestType::DefeatMonster>>
  {
    void operator()(FieldsWriter& out, const h3m::QuestDetails<h3m::QuestType::DefeatMonster>& details) const
    {
      out.writeField("absod_id", details.absod_id);
    }
  };

  template<>
  struct StructWriter<h3m::QuestDetails<h3m::QuestType::Artifacts>>
  {
    void operator()(FieldsWriter& out, const h3m::QuestDetails<h3m::QuestType::Artifacts>& details) const
    {
      out.writeField("artifacts", details.artifacts);
    }
  };

  template<>
  struct StructWriter<h3m::QuestDetails<h3m::QuestType::Creatures>>
  {
    void operator()(FieldsWriter& out, const h3m::QuestDetails<h3m::QuestType::Creatures>& details) const
    {
      out.writeField("creatures", details.creatures);
    }
  };

  template<>
  struct StructWriter<h3m::QuestDetails<h3m::QuestType::Resources>>
  {
    void operator()(FieldsWriter& out, const h3m::QuestDetails<h3m::QuestType::Resources>& details) const
    {
      out.writeField("resources", details.resources);
    }
  };

  template<>
  struct StructWriter<h3m::QuestDetails<h3m::QuestType::BeHero>>
  {
    void operator()(FieldsWriter& out, const h3m::QuestDetails<h3m::QuestType::BeHero>& details) const
    {
      out.writeField("hero", details.hero);
    }
  };

  template<>
  struct StructWriter<h3m::QuestDetails<h3m::QuestType::BePlayer>>
  {
    void operator()(FieldsWriter& out, const h3m::QuestDetails<h3m::QuestType::BePlayer>& details) const
    {
      out.writeField("player", details.player);
    }
  };

  template<>
  struct StructWriter<h3m::Quest>
  {
    void operator()(FieldsWriter& out, const h3m::Quest& quest) const
    {
      const bool has_details = quest.type() != h3m::QuestType::None;
      out.writeComment(h3m::getEnumString(quest.type()));
      out.writeField("type", quest.type());
      if (has_details)
      {
        std::visit([&out](auto&& details) { out.writeField("details", std::forward<decltype(details)>(details)); },
                   quest.details);
      }
    }
  };
}