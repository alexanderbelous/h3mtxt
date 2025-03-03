#include <h3mtxt/H3JsonReader/Utils.h>
#include <h3mtxt/H3JsonReader/VariantJsonReader.h>
#include <h3mtxt/JsonCommon/FieldName.h>
#include <h3mtxt/Campaign/StartingBonus.h>

namespace h3m::H3JsonReader_NS
{
  template<>
  struct JsonReader<StartingBonusDetails<StartingBonusType::Spell>>
  {
    StartingBonusDetails<StartingBonusType::Spell> operator()(const Json::Value& value) const
    {
      StartingBonusDetails<StartingBonusType::Spell> details;
      readField(details.hero, value, "hero");
      readField(details.spell, value, "spell");
      return details;
    }
  };

  template<>
  struct JsonReader<StartingBonusDetails<StartingBonusType::Creature>>
  {
    StartingBonusDetails<StartingBonusType::Creature> operator()(const Json::Value& value) const
    {
      StartingBonusDetails<StartingBonusType::Creature> details;
      readField(details.hero, value, "hero");
      readField(details.creature_stack, value, "creature_stack");
      return details;
    }
  };

  template<>
  struct JsonReader<StartingBonusDetails<StartingBonusType::Building>>
  {
    StartingBonusDetails<StartingBonusType::Building> operator()(const Json::Value& value) const
    {
      StartingBonusDetails<StartingBonusType::Building> details;
      readField(details.building, value, "building");
      return details;
    }
  };

  template<>
  struct JsonReader<StartingBonusDetails<StartingBonusType::Artifact>>
  {
    StartingBonusDetails<StartingBonusType::Artifact> operator()(const Json::Value& value) const
    {
      StartingBonusDetails<StartingBonusType::Artifact> details;
      readField(details.hero, value, "hero");
      readField(details.artifact, value, "artifact");
      return details;
    }
  };

  template<>
  struct JsonReader<StartingBonusDetails<StartingBonusType::SpellScroll>>
  {
    StartingBonusDetails<StartingBonusType::SpellScroll> operator()(const Json::Value& value) const
    {
      StartingBonusDetails<StartingBonusType::SpellScroll> details;
      readField(details.hero, value, "hero");
      readField(details.spell, value, "spell");
      return details;
    }
  };

  template<>
  struct JsonReader<StartingBonusDetails<StartingBonusType::PrimarySkills>>
  {
    StartingBonusDetails<StartingBonusType::PrimarySkills> operator()(const Json::Value& value) const
    {
      StartingBonusDetails<StartingBonusType::PrimarySkills> details;
      readField(details.hero, value, "hero");
      readField(details.skills, value, "skills");
      return details;
    }
  };

  template<>
  struct JsonReader<StartingBonusDetails<StartingBonusType::SecondarySkill>>
  {
    StartingBonusDetails<StartingBonusType::SecondarySkill> operator()(const Json::Value& value) const
    {
      StartingBonusDetails<StartingBonusType::SecondarySkill> details;
      readField(details.hero, value, "hero");
      readField(details.skill, value, "skill");
      return details;
    }
  };

  template<>
  struct JsonReader<StartingBonusDetails<StartingBonusType::Resource>>
  {
    StartingBonusDetails<StartingBonusType::Resource> operator()(const Json::Value& value) const
    {
      StartingBonusDetails<StartingBonusType::Resource> details;
      readField(details.type, value, "type");
      readField(details.amount, value, "amount");
      return details;
    }
  };

  StartingBonus JsonReader<StartingBonus>::operator()(const Json::Value& value) const
  {
    using Fields = FieldNames<StartingBonus>;
    StartingBonus bonus;
    const StartingBonusType starting_bonus_type = readField<StartingBonusType>(value, Fields::kType);
    VariantJsonReader<StartingBonus::Details> variant_reader{};
    bonus.details = variant_reader(getJsonField(value, Fields::kDetails),
                                   StartingBonus::getAlternativeIdx(starting_bonus_type));
    return bonus;
  }
}
