#include <h3mtxt/H3SvgJsonWriter/H3SvgJsonWriter.h>

#include <h3mtxt/H3JsonWriter/H3JsonWriter.h>
#include <h3mtxt/H3JsonWriter/getEnumString.h>
#include <h3mtxt/H3JsonWriter/Utils.h>
#include <h3mtxt/H3SvgJsonWriter/getEnumString.h>
#include <h3mtxt/JsonCommon/FieldNamesSvg.h>
#include <h3mtxt/Medea/Medea.h>
#include <h3mtxt/SavedGame/QuestSvg.h>

namespace Medea_NS
{
  // TODO: it kinda sucks that it's declared here.
  template<>
  void JsonObjectWriter<h3m::QuestDetailsSvg<h3m::QuestType::Creatures>::Creature>::operator()(
    FieldsWriter& out, const h3m::QuestDetailsSvg<h3m::QuestType::Creatures>::Creature& creature) const
  {
    out.writeField("type", creature.type);
    if (std::string_view enum_str = h3m::getEnumString(creature.type); !enum_str.empty())
    {
      out.writeComment(enum_str, false);
    }
    out.writeField("count", creature.count);
  }

  // TODO: reuse the implementations for h3m::QuestDetails where applicable.

  void JsonObjectWriter<h3m::QuestDetailsSvg<h3m::QuestType::None>>::operator()(
    FieldsWriter&, const h3m::QuestDetailsSvg<h3m::QuestType::None>&) const
  {
  }

  void JsonObjectWriter<h3m::QuestDetailsSvg<h3m::QuestType::Level>>::operator()(
    FieldsWriter& out, const h3m::QuestDetailsSvg<h3m::QuestType::Level>& details) const
  {
    out.writeField("level", details.level);
  }

  void JsonObjectWriter<h3m::QuestDetailsSvg<h3m::QuestType::PrimarySkills>>::operator()(
    FieldsWriter& out, const h3m::QuestDetailsSvg<h3m::QuestType::PrimarySkills>& details) const
  {
    out.writeField("primary_skills", details.skills);
  }

  void JsonObjectWriter<h3m::QuestDetailsSvg<h3m::QuestType::DefeatHero>>::operator()(
    FieldsWriter& out, const h3m::QuestDetailsSvg<h3m::QuestType::DefeatHero>& details) const
  {
    out.writeField("hero", details.hero);
    if (std::string_view enum_str = h3m::getEnumString(details.hero); !enum_str.empty())
    {
      out.writeComment(enum_str, false);
    }
    out.writeField("unknown", details.unknown);
  }

  void JsonObjectWriter<h3m::QuestDetailsSvg<h3m::QuestType::DefeatMonster>>::operator()(
    FieldsWriter& out, const h3m::QuestDetailsSvg<h3m::QuestType::DefeatMonster>& details) const
  {
    out.writeField("x", details.x);
    out.writeField("y", details.y);
    out.writeField("z", details.z);
    out.writeField("creature_type", details.creature_type);
    if (std::string_view enum_str = h3m::getEnumString(details.creature_type); !enum_str.empty())
    {
      out.writeComment(enum_str, false);
    }
    out.writeField("unknown", details.unknown);
  }

  void JsonObjectWriter<h3m::QuestDetailsSvg<h3m::QuestType::Artifacts>>::operator()(
    FieldsWriter& out, const h3m::QuestDetailsSvg<h3m::QuestType::Artifacts>& details) const
  {
    out.writeField("artifacts", details.artifacts);
  }

  void JsonObjectWriter<h3m::QuestDetailsSvg<h3m::QuestType::Creatures>>::operator()(
    FieldsWriter& out, const h3m::QuestDetailsSvg<h3m::QuestType::Creatures>& details) const
  {
    out.writeField("creatures", details.creatures);
  }

  void JsonObjectWriter<h3m::QuestDetailsSvg<h3m::QuestType::Resources>>::operator()(
    FieldsWriter& out, const h3m::QuestDetailsSvg<h3m::QuestType::Resources>& details) const
  {
    out.writeField("resources", details.resources);
  }

  void JsonObjectWriter<h3m::QuestDetailsSvg<h3m::QuestType::BeHero>>::operator()(
    FieldsWriter& out, const h3m::QuestDetailsSvg<h3m::QuestType::BeHero>& details) const
  {
    out.writeField("hero", details.hero);
    if (std::string_view enum_str = h3m::getEnumString(details.hero); !enum_str.empty())
    {
      out.writeComment(enum_str, false);
    }
    out.writeField("unknown", details.unknown);
  }

  void JsonObjectWriter<h3m::QuestDetailsSvg<h3m::QuestType::BePlayer>>::operator()(
    FieldsWriter& out, const h3m::QuestDetailsSvg<h3m::QuestType::BePlayer>& details) const
  {
    out.writeField("player", details.player);
    if (std::string_view enum_str = h3m::getEnumString(details.player); !enum_str.empty())
    {
      out.writeComment(enum_str, false);
    }
  }

  void JsonObjectWriter<h3m::QuestSvg>::operator()(FieldsWriter& out, const h3m::QuestSvg& quest) const
  {
    using Fields = h3m::FieldNames<h3m::QuestSvg>;
    out.writeField(Fields::kType, quest.type());
    out.writeComment(h3m::getEnumString(quest.type()), false);
    if (quest.type() != h3m::QuestType::None)
    {
      std::visit([&out] <h3m::QuestType T> (const h3m::QuestDetailsSvg<T>& details)
                 {
                   out.writeField(Fields::kDetails, details);
                 },
                 quest.details);
      out.writeField(Fields::kUnknown, quest.unknown);
      out.writeField(Fields::kDeadline, quest.deadline);
      out.writeField(Fields::kProposal, quest.proposal);
      out.writeField(Fields::kProgress, quest.progress);
      out.writeField(Fields::kCompletion, quest.completion);
    }
  }
}