#pragma once

#include <h3mtxt/JsonCommon/FieldName.h>
#include <h3mtxt/Map/Quest.h>
#include <h3mtxt/H3MJsonWriter/getEnumString.h>
#include <h3mtxt/H3MJsonWriter/H3MJsonWriter.h>
#include <h3mtxt/H3MJsonWriter/writeCreatureStack.h>
#include <h3mtxt/H3MJsonWriter/writePrimarySkills.h>
#include <h3mtxt/H3MJsonWriter/writeResources.h>

namespace Medea_NS
{
  template<>
  struct JsonObjectWriter<h3m::QuestDetails<h3m::QuestType::None>>
  {
    void operator()(FieldsWriter&, const h3m::QuestDetails<h3m::QuestType::None>&) const
    {
    }
  };

  template<>
  struct JsonObjectWriter<h3m::QuestDetails<h3m::QuestType::Level>>
  {
    void operator()(FieldsWriter& out, const h3m::QuestDetails<h3m::QuestType::Level>& details) const
    {
      out.writeField("level", details.level);
    }
  };

  template<>
  struct JsonObjectWriter<h3m::QuestDetails<h3m::QuestType::PrimarySkills>>
  {
    void operator()(FieldsWriter& out, const h3m::QuestDetails<h3m::QuestType::PrimarySkills>& details) const
    {
      out.writeField("skills", details.skills);
    }
  };

  template<>
  struct JsonObjectWriter<h3m::QuestDetails<h3m::QuestType::DefeatHero>>
  {
    void operator()(FieldsWriter& out, const h3m::QuestDetails<h3m::QuestType::DefeatHero>& details) const
    {
      out.writeField("absod_id", details.absod_id);
    }
  };

  template<>
  struct JsonObjectWriter<h3m::QuestDetails<h3m::QuestType::DefeatMonster>>
  {
    void operator()(FieldsWriter& out, const h3m::QuestDetails<h3m::QuestType::DefeatMonster>& details) const
    {
      out.writeField("absod_id", details.absod_id);
    }
  };

  template<>
  struct JsonObjectWriter<h3m::QuestDetails<h3m::QuestType::Artifacts>>
  {
    void operator()(FieldsWriter& out, const h3m::QuestDetails<h3m::QuestType::Artifacts>& details) const
    {
      out.writeField("artifacts", details.artifacts);
    }
  };

  template<>
  struct JsonObjectWriter<h3m::QuestDetails<h3m::QuestType::Creatures>>
  {
    void operator()(FieldsWriter& out, const h3m::QuestDetails<h3m::QuestType::Creatures>& details) const
    {
      out.writeField("creatures", details.creatures);
    }
  };

  template<>
  struct JsonObjectWriter<h3m::QuestDetails<h3m::QuestType::Resources>>
  {
    void operator()(FieldsWriter& out, const h3m::QuestDetails<h3m::QuestType::Resources>& details) const
    {
      out.writeField("resources", details.resources);
    }
  };

  template<>
  struct JsonObjectWriter<h3m::QuestDetails<h3m::QuestType::BeHero>>
  {
    void operator()(FieldsWriter& out, const h3m::QuestDetails<h3m::QuestType::BeHero>& details) const
    {
      out.writeField("hero", details.hero);
      if (auto enum_str = h3m::getEnumString(details.hero); !enum_str.empty())
      {
        out.writeComment(enum_str, false);
      }
    }
  };

  template<>
  struct JsonObjectWriter<h3m::QuestDetails<h3m::QuestType::BePlayer>>
  {
    void operator()(FieldsWriter& out, const h3m::QuestDetails<h3m::QuestType::BePlayer>& details) const
    {
      out.writeField("player", details.player);
      if (auto enum_str = h3m::getEnumString(details.player); !enum_str.empty())
      {
        out.writeComment(enum_str, false);
      }
    }
  };

  template<>
  struct JsonObjectWriter<h3m::Quest>
  {
    void operator()(FieldsWriter& out, const h3m::Quest& quest) const
    {
      using Fields = h3m::FieldNames<h3m::Quest>;
      const bool has_details = quest.type() != h3m::QuestType::None;
      out.writeField(Fields::kType, quest.type());
      if (has_details)
      {
        out.writeComma();
      }
      out.writeComment(h3m::getEnumString(quest.type()), false);
      if (has_details)
      {
        std::visit([&out](auto&& details) { out.writeField(Fields::kDetails, std::forward<decltype(details)>(details)); },
                   quest.details);
        out.writeField(Fields::kDeadline, quest.deadline);
        out.writeField(Fields::kProposal, quest.proposal);
        out.writeField(Fields::kProgress, quest.progress);
        out.writeField(Fields::kCompletion, quest.completion);
      }
    }
  };
}