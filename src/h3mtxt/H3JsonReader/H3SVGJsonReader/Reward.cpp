#include <h3mtxt/H3JsonReader/H3SVGJsonReader/H3SVGJsonReader.h>

#include <h3mtxt/H3JsonReader/H3JsonReaderBase/H3JsonReaderBase.h>
#include <h3mtxt/H3JsonReader/H3JsonReaderBase/VariantJsonReader.h>
#include <h3mtxt/JsonCommon/FieldNamesH3SVG.h>
#include <h3mtxt/SavedGame/Reward.h>

namespace h3json
{
  // This template is implicitly instantiated for all valid RewardTypes
  // in JsonReader<h3svg::Reward>::operator().
  template<h3svg::RewardType T>
  h3svg::RewardDetails<T>
  JsonReader<h3svg::RewardDetails<T>>::operator()(const Json::Value& value) const
  {
    using Fields = h3json::FieldNames<h3svg::RewardDetails<T>>;
    h3svg::RewardDetails<T> details;
    if constexpr (T == h3svg::RewardType::None)
    {
      readField(details.reserved, value, Fields::kReserved);
    }
    else if constexpr (T == h3svg::RewardType::Experience)
    {
      readField(details.experience, value, Fields::kExperience);
      readField(details.reserved, value, Fields::kReserved);
    }
    else if constexpr (T == h3svg::RewardType::SpellPoints)
    {
      readField(details.spell_points, value, Fields::kSpellPoints);
      readField(details.reserved, value, Fields::kReserved);
    }
    else if constexpr (T == h3svg::RewardType::Morale)
    {
      readField(details.morale, value, Fields::kMorale);
      readField(details.reserved, value, Fields::kReserved);
    }
    else if constexpr (T == h3svg::RewardType::Luck)
    {
      readField(details.luck, value, Fields::kLuck);
      readField(details.reserved, value, Fields::kReserved);
    }
    else if constexpr (T == h3svg::RewardType::Resource)
    {
      readField(details.resource, value, Fields::kResource);
    }
    else if constexpr (T == h3svg::RewardType::PrimarySkill)
    {
      readField(details.type, value, Fields::kType);
      readField(details.value, value, Fields::kValue);
    }
    else if constexpr (T == h3svg::RewardType::SecondarySkill)
    {
      readField(details.type, value, Fields::kType);
      readField(details.level, value, Fields::kLevel);
    }
    else if constexpr (T == h3svg::RewardType::Artifact)
    {
      readField(details.artifact, value, Fields::kArtifact);
      readField(details.reserved, value, Fields::kReserved);
    }
    else if constexpr (T == h3svg::RewardType::Spell)
    {
      readField(details.spell, value, Fields::kSpell);
      readField(details.reserved, value, Fields::kReserved);
    }
    else if constexpr (T == h3svg::RewardType::Creatures)
    {
      readField(details.creatures, value, Fields::kCreatures);
    }
    else
    {
      // Sanity check.
      // This shouldn't be reachable anyway because this template is only instantiated
      // for valid RewardTypes.
      static_assert(false, "Invalid RewardType.");
    }
    return details;
  }

  template<>
  h3svg::Reward JsonReader<h3svg::Reward>::operator()(const Json::Value& value) const
  {
    using Fields = h3json::FieldNames<h3svg::Reward>;
    const h3svg::RewardType reward_type = readField<h3svg::RewardType>(value, Fields::kType);
    return h3svg::Reward{
      .details = VariantJsonReader<h3svg::Reward::Details>{}(getJsonField(value, Fields::kDetails),
                                                             h3svg::Reward::getAlternativeIdx(reward_type))
    };
  }
}
