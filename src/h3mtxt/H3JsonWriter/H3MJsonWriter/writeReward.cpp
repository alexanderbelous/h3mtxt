#include <h3mtxt/H3JsonWriter/H3MJsonWriter/H3MJsonWriter.h>

#include <h3mtxt/H3JsonWriter/H3MJsonWriter/Utils.h>
#include <h3mtxt/JsonCommon/FieldNamesH3M.h>
#include <h3mtxt/Map/Reward.h>
#include <h3mtxt/Medea/Medea.h>

namespace Medea_NS
{
  void JsonObjectWriter<h3m::RewardDetails<h3m::RewardType::None>>::operator()(
    FieldsWriter&, const h3m::RewardDetails<h3m::RewardType::None>&) const
  {
  }

  void JsonObjectWriter<h3m::RewardDetails<h3m::RewardType::Experience>>::operator()(
    FieldsWriter& out, const h3m::RewardDetails<h3m::RewardType::Experience>& details) const
  {
    using Fields = h3json::FieldNames<h3m::RewardDetails<h3m::RewardType::Experience>>;
    out.writeField(Fields::kExperience, details.experience);
  }

  void JsonObjectWriter<h3m::RewardDetails<h3m::RewardType::SpellPoints>>::operator()(
    FieldsWriter& out, const h3m::RewardDetails<h3m::RewardType::SpellPoints>& details) const
  {
    using Fields = h3json::FieldNames<h3m::RewardDetails<h3m::RewardType::SpellPoints>>;
    out.writeField(Fields::kSpellPoints, details.spell_points);
  }

  void JsonObjectWriter<h3m::RewardDetails<h3m::RewardType::Morale>>::operator()(
    FieldsWriter& out, const h3m::RewardDetails<h3m::RewardType::Morale>& details) const
  {
    using Fields = h3json::FieldNames<h3m::RewardDetails<h3m::RewardType::Morale>>;
    out.writeField(Fields::kMorale, details.morale);
  }

  void JsonObjectWriter<h3m::RewardDetails<h3m::RewardType::Luck>>::operator()(
    FieldsWriter& out, const h3m::RewardDetails<h3m::RewardType::Luck>& details) const
  {
    using Fields = h3json::FieldNames<h3m::RewardDetails<h3m::RewardType::Luck>>;
    out.writeField(Fields::kLuck, details.luck);
  }

  void JsonObjectWriter<h3m::RewardDetails<h3m::RewardType::Resource>>::operator()(
    FieldsWriter& out, const h3m::RewardDetails<h3m::RewardType::Resource>& details) const
  {
    using Fields = h3json::FieldNames<h3m::RewardDetails<h3m::RewardType::Resource>>;
    out.writeField(Fields::kType, details.type);
    out.writeField(Fields::kAmount, details.amount);
  }

  void JsonObjectWriter<h3m::RewardDetails<h3m::RewardType::PrimarySkill>>::operator()(
    FieldsWriter& out, const h3m::RewardDetails<h3m::RewardType::PrimarySkill>& details) const
  {
    using Fields = h3json::FieldNames<h3m::RewardDetails<h3m::RewardType::PrimarySkill>>;
    out.writeField(Fields::kType, details.type);
    out.writeField(Fields::kValue, details.value);
  }

  void JsonObjectWriter<h3m::RewardDetails<h3m::RewardType::SecondarySkill>>::operator()(
    FieldsWriter& out, const h3m::RewardDetails<h3m::RewardType::SecondarySkill>& details) const
  {
    JsonObjectWriter<h3m::SecondarySkill>{}(out, details);
  }

  void JsonObjectWriter<h3m::RewardDetails<h3m::RewardType::Artifact>>::operator()(
    FieldsWriter& out, const h3m::RewardDetails<h3m::RewardType::Artifact>& details) const
  {
    using Fields = h3json::FieldNames<h3m::RewardDetails<h3m::RewardType::Artifact>>;
    out.writeField(Fields::kArtifact, details.artifact);
  }

  void JsonObjectWriter<h3m::RewardDetails<h3m::RewardType::Spell>>::operator()(
    FieldsWriter& out, const h3m::RewardDetails<h3m::RewardType::Spell>& details) const
  {
    using Fields = h3json::FieldNames<h3m::RewardDetails<h3m::RewardType::Spell>>;
    out.writeField(Fields::kSpell, details.spell);
  }

  void JsonObjectWriter<h3m::RewardDetails<h3m::RewardType::Creature>>::operator()(
    FieldsWriter& out, const h3m::RewardDetails<h3m::RewardType::Creature>& details) const
  {
    JsonObjectWriter<h3m::CreatureStack>{}(out, details);
  }

  void JsonObjectWriter<h3m::Reward>::operator()(FieldsWriter& out, const h3m::Reward& reward) const
  {
    using Fields = h3json::FieldNames<h3m::Reward>;
    out.writeField(Fields::kType, reward.type());
    if (reward.type() != h3m::RewardType::None)
    {
      std::visit([&out] <h3m::RewardType T> (const h3m::RewardDetails<T>& details)
                 { out.writeField(Fields::kDetails, details); },
                 reward.details);
    }
  }
}
