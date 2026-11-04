#include <h3mtxt/H3JsonWriter/H3MJsonWriter/H3MJsonWriter.h>

#include <h3mtxt/H3JsonWriter/H3MJsonWriter/Utils.h>
#include <h3mtxt/JsonCommon/FieldNamesH3M.h>
#include <h3mtxt/Map/Reward.h>
#include <h3mtxt/Medea/Medea.h>

using ::h3m::RewardDetails;
using ::h3m::RewardType;

namespace Medea_NS
{
  template<RewardType T>
  void JsonObjectWriter<RewardDetails<T>>::operator()(FieldsWriter& out, const RewardDetails<T>& details) const
  {
    using Fields = h3json::FieldNames<RewardDetails<T>>;
    if constexpr (T == RewardType::None)
    {
      // No fields.
    }
    else if constexpr (T == RewardType::Experience)
    {
      out.writeField(Fields::kExperience, details.experience);
    }
    else if constexpr (T == RewardType::SpellPoints)
    {
      out.writeField(Fields::kSpellPoints, details.spell_points);
    }
    else if constexpr (T == RewardType::Morale)
    {
      out.writeField(Fields::kMorale, details.morale);
    }
    else if constexpr (T == RewardType::Luck)
    {
      out.writeField(Fields::kLuck, details.luck);
    }
    else if constexpr (T == RewardType::Resource)
    {
      out.writeField(Fields::kResource, details.resource);
    }
    else if constexpr (T == RewardType::PrimarySkill)
    {
      out.writeField(Fields::kType, details.type);
      out.writeField(Fields::kValue, details.value);
    }
    else if constexpr (T == RewardType::SecondarySkill)
    {
      out.writeField(Fields::kSecondarySkill, details.secondary_skill);
    }
    else if constexpr (T == RewardType::Artifact)
    {
      out.writeField(Fields::kArtifact, details.artifact);
    }
    else if constexpr (T == RewardType::Spell)
    {
      out.writeField(Fields::kSpell, details.spell);
    }
    else if constexpr (T == RewardType::Creatures)
    {
      out.writeField(Fields::kCreatures, details.creatures);
    }
    else
    {
      static_assert(false, "Invalid RewardType.");
    }
  }

  template<>
  void JsonObjectWriter<h3m::Reward>::operator()(FieldsWriter& out, const h3m::Reward& reward) const
  {
    using Fields = h3json::FieldNames<h3m::Reward>;
    out.writeField(Fields::kType, reward.type());
    if (reward.type() != RewardType::None)
    {
      std::visit([&out] <RewardType T> (const RewardDetails<T>& details)
                 { out.writeField(Fields::kDetails, details); },
                 reward.details);
    }
  }
}
