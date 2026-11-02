#include <h3mtxt/H3JsonReader/H3CJsonReader/H3CJsonReader.h>

#include <h3mtxt/H3JsonReader/H3JsonReaderBase/H3JsonReaderBase.h>
#include <h3mtxt/H3JsonReader/H3JsonReaderBase/VariantJsonReader.h>
#include <h3mtxt/H3JsonReader/H3MJsonReader/H3MJsonReader.h>
#include <h3mtxt/JsonCommon/FieldNamesH3C.h>
#include <h3mtxt/JsonCommon/FieldNamesH3M.h>
#include <h3mtxt/Campaign/StartingBonus.h>

namespace h3json
{
  using ::h3m::StartingBonus;
  using ::h3m::StartingBonusDetails;
  using ::h3m::StartingBonusType;

  template<StartingBonusType T>
  StartingBonusDetails<T> JsonReader2<StartingBonusDetails<T>>::operator()() const
  {
    StartingBonusDetails<T> details;
    if constexpr (T == StartingBonusType::Spell)
    {
      readField("hero", details.hero);
      readField("spell", details.spell);
    }
    else if constexpr (T == StartingBonusType::Creature)
    {
      readField("hero", details.hero);
      readField("creature_stack", details.creature_stack);
    }
    else if constexpr (T == StartingBonusType::Building)
    {
      readField("building", details.building);
    }
    else if constexpr (T == StartingBonusType::Artifact)
    {
      readField("hero", details.hero);
      readField("artifact", details.artifact);
    }
    else if constexpr (T == StartingBonusType::SpellScroll)
    {
      readField("hero", details.hero);
      readField("spell", details.spell);
    }
    else if constexpr (T == StartingBonusType::PrimarySkills)
    {
      readField("hero", details.hero);
      readField("skills", details.skills);
    }
    else if constexpr (T == StartingBonusType::SecondarySkill)
    {
      readField("hero", details.hero);
      readField("skill", details.skill);
    }
    else if constexpr (T == StartingBonusType::Resource)
    {
      readField("resource", details.resource);
    }
    else
    {
      static_assert(false, "Invalid StartingBonusType.");
    }
    return details;
  }

  template<>
  StartingBonus JsonReader2<StartingBonus>::operator()() const
  {
    using Fields = FieldNames<StartingBonus>;
    const StartingBonusType starting_bonus_type = readField<StartingBonusType>(Fields::kType);
    return StartingBonus{
      .details = VariantJsonReader<StartingBonus::Details>{}(getField(Fields::kDetails),
                                                             StartingBonus::getAlternativeIdx(starting_bonus_type))
    };
  }
}
