#include <h3mtxt/H3JsonWriter/H3SVGJsonWriter/H3SVGJsonWriter.h>

#include <h3mtxt/H3JsonWriter/H3MJsonWriter/Utils.h>
#include <h3mtxt/JsonCommon/FieldNamesH3SVG.h>
#include <h3mtxt/Medea/Medea.h>
#include <h3mtxt/SavedGame/Reward.h>

namespace Medea_NS
{
  template<h3svg::RewardType T>
  void JsonObjectWriter<h3svg::RewardDetails<T>>::operator()(FieldsWriter& out,
                                                             const h3svg::RewardDetails<T>& details) const
  {
    using Fields = h3json::FieldNames<h3svg::RewardDetails<T>>;

    if constexpr (T == h3svg::RewardType::None)
    {
      out.writeField(Fields::kReserved, details.reserved);
    }
    else if constexpr (T == h3svg::RewardType::Experience)
    {
      out.writeField(Fields::kExperience, details.experience);
      out.writeField(Fields::kReserved, details.reserved);
    }
    else if constexpr (T == h3svg::RewardType::SpellPoints)
    {
      out.writeField(Fields::kSpellPoints, details.spell_points);
      out.writeField(Fields::kReserved, details.reserved);
    }
    else if constexpr (T == h3svg::RewardType::Morale)
    {
      out.writeField(Fields::kMorale, details.morale);
      out.writeField(Fields::kReserved, details.reserved);
    }
    else if constexpr (T == h3svg::RewardType::Luck)
    {
      out.writeField(Fields::kLuck, details.luck);
      out.writeField(Fields::kReserved, details.reserved);
    }
    else if constexpr (T == h3svg::RewardType::Resource)
    {
      out.writeField(Fields::kResource, details.resource);
    }
    else if constexpr (T == h3svg::RewardType::PrimarySkill)
    {
      out.writeField(Fields::kType, details.type);
      out.writeField(Fields::kValue, details.value);
    }
    else if constexpr (T == h3svg::RewardType::SecondarySkill)
    {
      out.writeField(Fields::kType, details.type);
      out.writeField(Fields::kLevel, details.level);
    }
    else if constexpr (T == h3svg::RewardType::Artifact)
    {
      out.writeField(Fields::kArtifact, details.artifact);
      out.writeField(Fields::kReserved, details.reserved);
    }
    else if constexpr (T == h3svg::RewardType::Spell)
    {
      out.writeField(Fields::kSpell, details.spell);
      out.writeField(Fields::kReserved, details.reserved);
    }
    else if constexpr (T == h3svg::RewardType::Creatures)
    {
      out.writeField(Fields::kCreatures, details.creatures);
    }
    else
    {
      static_assert(false, "Invalid RewardType.");
    }
  }

  template<>
  void JsonObjectWriter<h3svg::Reward>::operator()(FieldsWriter& out, const h3svg::Reward& reward) const
  {
    using Fields = h3json::FieldNames<h3svg::Reward>;
    out.writeField(Fields::kType, reward.type());
    // Note that unlike h3m::Reward, "details" field is always written here for RewardType::None,
    // because h3svg::RewardDetails<h3svg::RewardType::None> is not an empty class.
    std::visit([&out] <h3svg::RewardType T> (const h3svg::RewardDetails<T>& details)
                {
                  out.writeField(Fields::kDetails, details);
                },
                reward.details);
  }
}
