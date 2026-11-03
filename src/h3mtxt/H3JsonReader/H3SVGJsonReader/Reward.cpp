#include <h3mtxt/H3JsonReader/H3SVGJsonReader/H3SVGJsonReader.h>

#include <h3mtxt/H3JsonReader/H3JsonReaderBase/H3JsonReaderBase.h>
#include <h3mtxt/H3JsonReader/H3JsonReaderBase/VariantJsonReader.h>
#include <h3mtxt/JsonCommon/FieldNamesH3SVG.h>
#include <h3mtxt/SavedGame/Reward.h>

namespace h3json
{
  template<h3svg::RewardType T>
  h3svg::RewardDetails<T> JsonReader2<h3svg::RewardDetails<T>>::operator()() const
  {
    using Fields = h3json::FieldNames<h3svg::RewardDetails<T>>;
    h3svg::RewardDetails<T> details;
    if constexpr (T == h3svg::RewardType::None)
    {
      readField(Fields::kReserved, details.reserved);
    }
    else if constexpr (T == h3svg::RewardType::Experience)
    {
      readField(Fields::kExperience, details.experience);
      readField(Fields::kReserved, details.reserved);
    }
    else if constexpr (T == h3svg::RewardType::SpellPoints)
    {
      readField(Fields::kSpellPoints, details.spell_points);
      readField(Fields::kReserved, details.reserved);
    }
    else if constexpr (T == h3svg::RewardType::Morale)
    {
      readField(Fields::kMorale, details.morale);
      readField(Fields::kReserved, details.reserved);
    }
    else if constexpr (T == h3svg::RewardType::Luck)
    {
      readField(Fields::kLuck, details.luck);
      readField(Fields::kReserved, details.reserved);
    }
    else if constexpr (T == h3svg::RewardType::Resource)
    {
      readField(Fields::kResource, details.resource);
    }
    else if constexpr (T == h3svg::RewardType::PrimarySkill)
    {
      readField(Fields::kType, details.type);
      readField(Fields::kValue, details.value);
    }
    else if constexpr (T == h3svg::RewardType::SecondarySkill)
    {
      readField(Fields::kType, details.type);
      readField(Fields::kLevel, details.level);
    }
    else if constexpr (T == h3svg::RewardType::Artifact)
    {
      readField(Fields::kArtifact, details.artifact);
      readField(Fields::kReserved, details.reserved);
    }
    else if constexpr (T == h3svg::RewardType::Spell)
    {
      readField(Fields::kSpell, details.spell);
      readField(Fields::kReserved, details.reserved);
    }
    else if constexpr (T == h3svg::RewardType::Creatures)
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
  h3svg::Reward JsonReader2<h3svg::Reward>::operator()() const
  {
    using Fields = h3json::FieldNames<h3svg::Reward>;
    const h3svg::RewardType reward_type = readField<h3svg::RewardType>(Fields::kType);
    return h3svg::Reward{
      .details = VariantJsonReader<h3svg::Reward::Details>{}(getField(Fields::kDetails),
                                                             h3svg::Reward::getAlternativeIdx(reward_type))
    };
  }
}
