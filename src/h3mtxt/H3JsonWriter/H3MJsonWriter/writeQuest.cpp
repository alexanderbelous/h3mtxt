#include <h3mtxt/H3JsonWriter/H3MJsonWriter/H3MJsonWriter.h>

#include <h3mtxt/H3JsonWriter/H3MJsonWriter/DateUtils.h>
#include <h3mtxt/H3JsonWriter/H3MJsonWriter/Utils.h>
#include <h3mtxt/JsonCommon/FieldNamesH3M.h>
#include <h3mtxt/Map/Quest.h>
#include <h3mtxt/Medea/Medea.h>

using ::h3m::QuestDetails;
using ::h3m::QuestType;

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

  template<QuestType T>
  void JsonObjectWriter<QuestDetails<T>>::operator()(FieldsWriter& out, const QuestDetails<T>& details) const
  {
    using Fields = h3json::FieldNames<QuestDetails<T>>;
    if constexpr (T == QuestType::None)
    {
      // No fields.
    }
    else if constexpr (T == QuestType::Level)
    {
      out.writeField(Fields::kLevel, details.level);
    }
    else if constexpr (T == QuestType::PrimarySkills)
    {
      out.writeField(Fields::kSkills, details.skills);
    }
    else if constexpr (T == QuestType::DefeatHero)
    {
      out.writeField(Fields::kAbsodId, details.absod_id);
    }
    else if constexpr (T == QuestType::DefeatMonster)
    {
      out.writeField(Fields::kAbsodId, details.absod_id);
    }
    else if constexpr (T == QuestType::Artifacts)
    {
      out.writeField(Fields::kArtifacts, details.artifacts);
    }
    else if constexpr (T == QuestType::Creatures)
    {
      out.writeField(Fields::kCreatures, details.creatures);
    }
    else if constexpr (T == QuestType::Resources)
    {
      out.writeField(Fields::kResources, details.resources);
    }
    else if constexpr (T == QuestType::BeHero)
    {
      out.writeField(Fields::kHero, details.hero);
    }
    else if constexpr (T == QuestType::BePlayer)
    {
      out.writeField(Fields::kPlayer, details.player);
    }
    else
    {
      static_assert(false, "Invalid QuestType.");
    }
  }

  template<>
  void JsonObjectWriter<h3m::Quest>::operator()(FieldsWriter& out, const h3m::Quest& quest) const
  {
    using Fields = h3json::FieldNames<h3m::Quest>;
    out.writeField(Fields::kType, quest.type());
    if (quest.type() != QuestType::None)
    {
      std::visit([&out] <QuestType T> (const QuestDetails<T>& details)
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
