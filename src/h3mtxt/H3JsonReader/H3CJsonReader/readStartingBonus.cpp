#include <h3mtxt/H3JsonReader/H3CJsonReader/H3CJsonReader.h>

#include <h3mtxt/H3JsonReader/H3JsonReaderBase/H3JsonReaderBase.h>
#include <h3mtxt/H3JsonReader/H3JsonReaderBase/VariantJsonReader.h>
#include <h3mtxt/JsonCommon/FieldNamesH3C.h>
#include <h3mtxt/JsonCommon/FieldNamesH3M.h>
#include <h3mtxt/Campaign/StartingBonus.h>

namespace h3json
{
  using ::h3m::StartingBonus;
  using ::h3m::StartingBonusDetails;
  using ::h3m::StartingBonusType;

  StartingBonusDetails<StartingBonusType::Spell>
  JsonReader<StartingBonusDetails<StartingBonusType::Spell>>::operator()(const Json::Value& value) const
  {
    StartingBonusDetails<StartingBonusType::Spell> details;
    readField(details.hero, value, "hero");
    readField(details.spell, value, "spell");
    return details;
  }

  StartingBonusDetails<StartingBonusType::Creature>
  JsonReader<StartingBonusDetails<StartingBonusType::Creature>>::operator()(const Json::Value& value) const
  {
    StartingBonusDetails<StartingBonusType::Creature> details;
    readField(details.hero, value, "hero");
    readField(details.creature_stack, value, "creature_stack");
    return details;
  }

  StartingBonusDetails<StartingBonusType::Building>
  JsonReader<StartingBonusDetails<StartingBonusType::Building>>::operator()(const Json::Value& value) const
  {
    StartingBonusDetails<StartingBonusType::Building> details;
    readField(details.building, value, "building");
    return details;
  }

  StartingBonusDetails<StartingBonusType::Artifact>
  JsonReader<StartingBonusDetails<StartingBonusType::Artifact>>::operator()(const Json::Value& value) const
  {
    StartingBonusDetails<StartingBonusType::Artifact> details;
    readField(details.hero, value, "hero");
    readField(details.artifact, value, "artifact");
    return details;
  }

  StartingBonusDetails<StartingBonusType::SpellScroll>
  JsonReader<StartingBonusDetails<StartingBonusType::SpellScroll>>::operator()(const Json::Value& value) const
  {
    StartingBonusDetails<StartingBonusType::SpellScroll> details;
    readField(details.hero, value, "hero");
    readField(details.spell, value, "spell");
    return details;
  }

  StartingBonusDetails<StartingBonusType::PrimarySkills>
  JsonReader<StartingBonusDetails<StartingBonusType::PrimarySkills>>::operator()(const Json::Value& value) const
  {
    StartingBonusDetails<StartingBonusType::PrimarySkills> details;
    readField(details.hero, value, "hero");
    readField(details.skills, value, "skills");
    return details;
  }

  StartingBonusDetails<StartingBonusType::SecondarySkill>
  JsonReader<StartingBonusDetails<StartingBonusType::SecondarySkill>>::operator()(const Json::Value& value) const
  {
    StartingBonusDetails<StartingBonusType::SecondarySkill> details;
    readField(details.hero, value, "hero");
    readField(details.skill, value, "skill");
    return details;
  }

  StartingBonusDetails<StartingBonusType::Resource>
  JsonReader<StartingBonusDetails<StartingBonusType::Resource>>::operator()(const Json::Value& value) const
  {
    StartingBonusDetails<StartingBonusType::Resource> details;
    readField(details.type, value, "type");
    readField(details.amount, value, "amount");
    return details;
  }

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
