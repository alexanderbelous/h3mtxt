#include <h3mtxt/H3JsonReader/H3MJsonReader/H3MJsonReader.h>

#include <h3mtxt/H3JsonReader/H3JsonReaderBase/H3JsonReaderBase.h>
#include <h3mtxt/H3JsonReader/H3JsonReaderBase/VariantJsonReader.h>
#include <h3mtxt/JsonCommon/FieldNamesH3M.h>
#include <h3mtxt/Map/Reward.h>

namespace h3json
{
  using ::h3m::Reward;
  using ::h3m::RewardDetails;
  using ::h3m::RewardType;

  template<RewardType T>
  RewardDetails<T> JsonReader2<RewardDetails<T>>::operator()() const
  {
    using Fields = FieldNames<RewardDetails<T>>;
    RewardDetails<T> details;
    if constexpr (T == RewardType::None)
    {
      // No fields.
    }
    else if constexpr (T == RewardType::Experience)
    {
      readField(Fields::kExperience, details.experience);
    }
    else if constexpr (T == RewardType::SpellPoints)
    {
      readField(Fields::kSpellPoints, details.spell_points);
    }
    else if constexpr (T == RewardType::Morale)
    {
      readField(Fields::kMorale, details.morale);
    }
    else if constexpr (T == RewardType::Luck)
    {
      readField(Fields::kLuck, details.luck);
    }
    else if constexpr (T == RewardType::Resource)
    {
      readField(Fields::kResource, details.resource);
    }
    else if constexpr (T == RewardType::PrimarySkill)
    {
      readField(Fields::kType, details.type);
      readField(Fields::kValue, details.value);
    }
    else if constexpr (T == RewardType::SecondarySkill)
    {
      readField(Fields::kSecondarySkill, details.secondary_skill);
    }
    else if constexpr (T == RewardType::Artifact)
    {
      readField(Fields::kArtifact, details.artifact);
    }
    else if constexpr (T == RewardType::Spell)
    {
      readField(Fields::kSpell, details.spell);
    }
    else if constexpr (T == RewardType::Creatures)
    {
      readField(Fields::kCreatures, details.creatures);
    }
    else
    {
      static_assert(false, "Invalid RewardType.");
    }
    return details;
  }

  template<>
  Reward JsonReader2<Reward>::operator()() const
  {
    using Fields = FieldNames<Reward>;
    Reward reward;
    const RewardType reward_type = readField<RewardType>(Fields::kType);
    if (reward_type != RewardType::None)
    {
      reward.details = VariantJsonReader<Reward::Details>{}(getField(Fields::kDetails),
                                                            Reward::getAlternativeIdx(reward_type));
    }
    return reward;
  }
}
