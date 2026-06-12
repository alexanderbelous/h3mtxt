#include <h3mtxt/H3JsonWriter/H3MJsonWriter/H3MJsonWriter.h>

#include <h3mtxt/H3JsonWriter/H3MJsonWriter/DateUtils.h>
#include <h3mtxt/H3JsonWriter/H3MJsonWriter/Utils.h>
#include <h3mtxt/JsonCommon/FieldNamesH3M.h>
#include <h3mtxt/Map/Quest.h>
#include <h3mtxt/Medea/Medea.h>

#include <type_traits>

namespace Medea_NS
{
  namespace
  {
    std::string makeDeadlineComment(std::uint32_t deadline)
    {
      constexpr std::uint32_t kDateMaxFeasible = static_cast<std::uint32_t>(h3json::Detail_NS::kDateMaxFeasible);
      if (deadline <= kDateMaxFeasible)
      {
        return h3json::Detail_NS::makeDateComment(static_cast<std::int32_t>(deadline));
      }
      return "None";
    }
  }

  template<>
  void JsonObjectWriter<h3m::QuestDetails<h3m::QuestType::None>>::operator()(
    FieldsWriter&, const h3m::QuestDetails<h3m::QuestType::None>&) const
  {
  }

  template<>
  void JsonObjectWriter<h3m::QuestDetails<h3m::QuestType::Level>>::operator()(
    FieldsWriter& out, const h3m::QuestDetails<h3m::QuestType::Level>& details) const
  {
    using Fields = h3json::FieldNames<std::remove_cvref_t<decltype(details)>>;
    out.writeField(Fields::kLevel, details.level);
  }

  template<>
  void JsonObjectWriter<h3m::QuestDetails<h3m::QuestType::PrimarySkills>>::operator()(
    FieldsWriter& out, const h3m::QuestDetails<h3m::QuestType::PrimarySkills>& details) const
  {
    using Fields = h3json::FieldNames<std::remove_cvref_t<decltype(details)>>;
    out.writeField(Fields::kSkills, details.skills);
  }

  template<>
  void JsonObjectWriter<h3m::QuestDetails<h3m::QuestType::DefeatHero>>::operator()(
    FieldsWriter& out, const h3m::QuestDetails<h3m::QuestType::DefeatHero>& details) const
  {
    using Fields = h3json::FieldNames<std::remove_cvref_t<decltype(details)>>;
    out.writeField(Fields::kAbsodId, details.absod_id);
  }

  template<>
  void JsonObjectWriter<h3m::QuestDetails<h3m::QuestType::DefeatMonster>>::operator()(
    FieldsWriter& out, const h3m::QuestDetails<h3m::QuestType::DefeatMonster>& details) const
  {
    using Fields = h3json::FieldNames<std::remove_cvref_t<decltype(details)>>;
    out.writeField(Fields::kAbsodId, details.absod_id);
  }

  template<>
  void JsonObjectWriter<h3m::QuestDetails<h3m::QuestType::Artifacts>>::operator()(
    FieldsWriter& out, const h3m::QuestDetails<h3m::QuestType::Artifacts>& details) const
  {
    using Fields = h3json::FieldNames<std::remove_cvref_t<decltype(details)>>;
    out.writeField(Fields::kArtifacts, details.artifacts);
  }

  template<>
  struct JsonObjectWriter<h3m::QuestDetails<h3m::QuestType::Creatures>::Creature>
  {
    void operator()(FieldsWriter& out, const h3m::QuestDetails<h3m::QuestType::Creatures>::Creature& creature) const
    {
      out.writeField("type", creature.type);
      out.writeField("count", creature.count);
    }
  };

  template<>
  void JsonObjectWriter<h3m::QuestDetails<h3m::QuestType::Creatures>>::operator()(
    FieldsWriter& out, const h3m::QuestDetails<h3m::QuestType::Creatures>& details) const
  {
    using Fields = h3json::FieldNames<std::remove_cvref_t<decltype(details)>>;
    out.writeField(Fields::kCreatures, details.creatures);
  }

  template<>
  void JsonObjectWriter<h3m::QuestDetails<h3m::QuestType::Resources>>::operator()(
    FieldsWriter& out, const h3m::QuestDetails<h3m::QuestType::Resources>& details) const
  {
    using Fields = h3json::FieldNames<std::remove_cvref_t<decltype(details)>>;
    out.writeField(Fields::kResources, details.resources);
  }

  template<>
  void JsonObjectWriter<h3m::QuestDetails<h3m::QuestType::BeHero>>::operator()(
    FieldsWriter& out, const h3m::QuestDetails<h3m::QuestType::BeHero>& details) const
  {
    using Fields = h3json::FieldNames<std::remove_cvref_t<decltype(details)>>;
    out.writeField(Fields::kHero, details.hero);
  }

  template<>
  void JsonObjectWriter<h3m::QuestDetails<h3m::QuestType::BePlayer>>::operator()(
    FieldsWriter& out, const h3m::QuestDetails<h3m::QuestType::BePlayer>& details) const
  {
    using Fields = h3json::FieldNames<std::remove_cvref_t<decltype(details)>>;
    out.writeField(Fields::kPlayer, details.player);
  }

  template<>
  void JsonObjectWriter<h3m::Quest>::operator()(FieldsWriter& out, const h3m::Quest& quest) const
  {
    using Fields = h3json::FieldNames<h3m::Quest>;
    out.writeField(Fields::kType, quest.type());
    if (quest.type() != h3m::QuestType::None)
    {
      std::visit([&out] <h3m::QuestType T> (const h3m::QuestDetails<T>& details)
                 { out.writeField(Fields::kDetails, details); },
                 quest.details);
      out.writeField(Fields::kDeadline, quest.deadline);
      out.writeComment(makeDeadlineComment(quest.deadline), false);
      out.writeField(Fields::kProposal, quest.proposal);
      out.writeField(Fields::kProgress, quest.progress);
      out.writeField(Fields::kCompletion, quest.completion);
    }
  }
}
