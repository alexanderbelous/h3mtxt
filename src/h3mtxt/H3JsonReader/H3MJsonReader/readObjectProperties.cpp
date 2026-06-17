#include <h3mtxt/H3JsonReader/H3MJsonReader/H3MJsonReader.h>

#include <h3mtxt/H3JsonReader/H3JsonReaderBase/H3JsonReaderBase.h>
#include <h3mtxt/H3JsonReader/H3JsonReaderBase/VariantJsonReader.h>
#include <h3mtxt/JsonCommon/FieldNamesH3M.h>
#include <h3mtxt/Map/Utils/SwitchStatement.h>
#include <h3mtxt/Map/ObjectPropertiesVariant.h>

namespace h3json
{
  using ::h3m::ObjectProperties;
  using ::h3m::ObjectPropertiesType;
  using ::h3m::ObjectPropertiesVariant;

  template<>
  h3m::EventBase JsonReader<h3m::EventBase>::operator()(const Json::Value& value) const
  {
    using Fields = FieldNames<h3m::EventBase>;
    h3m::EventBase event;
    readField(event.guardians, value, Fields::kGuardians);
    readField(event.experience, value, Fields::kExperience);
    readField(event.spell_points, value, Fields::kSpellPoints);
    readField(event.morale, value, Fields::kMorale);
    readField(event.luck, value, Fields::kLuck);
    readField(event.resources, value, Fields::kResources);
    readField(event.primary_skills, value, Fields::kPrimarySkills);
    readField(event.secondary_skills, value, Fields::kSecondarySkills);
    readField(event.artifacts, value, Fields::kArtifacts);
    readField(event.spells, value, Fields::kSpells);
    readField(event.creatures, value, Fields::kCreatures);
    readField(event.unknown, value, Fields::kUnknown);
    return event;
  }

  template<>
  h3m::Guardians JsonReader<h3m::Guardians>::operator()(const Json::Value& value) const
  {
    using Fields = FieldNames<h3m::Guardians>;
    h3m::Guardians guardians;
    readField(guardians.message, value, Fields::kMessage);
    readField(guardians.creatures, value, Fields::kCreatures);
    readField(guardians.unknown, value, Fields::kUnknown);
    return guardians;
  }

  template<>
  h3m::MessageAndTreasure JsonReader<h3m::MessageAndTreasure>::operator()(const Json::Value& value) const
  {
    using Fields = FieldNames<h3m::MessageAndTreasure>;
    h3m::MessageAndTreasure message_and_treasure;
    readField(message_and_treasure.message, value, Fields::kMessage);
    readField(message_and_treasure.resources, value, Fields::kResources);
    readField(message_and_treasure.artifact, value, Fields::kArtifact);
    return message_and_treasure;
  }

  template<>
  h3m::TownBuildings JsonReader<h3m::TownBuildings>::operator()(const Json::Value& value) const
  {
    using Fields = FieldNames<h3m::TownBuildings>;
    h3m::TownBuildings town_buildings;
    readField(town_buildings.is_built, value, Fields::kIsBuilt);
    readField(town_buildings.is_disabled, value, Fields::kIsDisabled);
    return town_buildings;
  }

  template<>
  h3m::TownEvent JsonReader<h3m::TownEvent>::operator()(const Json::Value& value) const
  {
    using Fields = FieldNames<h3m::TownEvent>;
    h3m::TownEvent event{ JsonReader<h3m::TimedEvent>{}(value) };
    readField(event.buildings, value, Fields::kBuildings);
    readField(event.creatures, value, Fields::kCreatures);
    readField(event.unknown2, value, Fields::kUnknown2);
    return event;
  }

  template<>
  ObjectProperties<ObjectPropertiesType::NONE>
  JsonReader<ObjectProperties<ObjectPropertiesType::NONE>>::operator()(const Json::Value&) const
  {
    // ObjectProperties<ObjectPropertiesType::NONE> has no fields.
    return {};
  }

  template<>
  ObjectProperties<ObjectPropertiesType::ABANDONED_MINE>
  JsonReader<ObjectProperties<ObjectPropertiesType::ABANDONED_MINE>>::operator()(const Json::Value& value) const
  {
    using Properties = ObjectProperties<ObjectPropertiesType::ABANDONED_MINE>;
    using Fields = FieldNames<Properties>;
    Properties properties;
    readField(properties.potential_resources, value, Fields::kPotentialResources);
    readField(properties.unknown, value, Fields::kUnknown);
    return properties;
  }

  template<>
  ObjectProperties<ObjectPropertiesType::ARTIFACT>
  JsonReader<ObjectProperties<ObjectPropertiesType::ARTIFACT>>::operator()(const Json::Value& value) const
  {
    using Properties = ObjectProperties<ObjectPropertiesType::ARTIFACT>;
    using Fields = FieldNames<Properties>;
    Properties properties;
    readField(properties.guardians, value, Fields::kGuardians);
    return properties;
  }

  template<>
  ObjectProperties<ObjectPropertiesType::EVENT>
  JsonReader<ObjectProperties<ObjectPropertiesType::EVENT>>::operator()(const Json::Value& value) const
  {
    using Properties = ObjectProperties<ObjectPropertiesType::EVENT>;
    using Fields = FieldNames<Properties>;
    Properties properties{ fromJson<h3m::EventBase>(value) };
    readField(properties.affected_players, value, Fields::kAffectedPlayers);
    readField(properties.applies_to_computer, value, Fields::kAppliesToComputer);
    readField(properties.cancel_after_first_visit, value, Fields::kCancelAfterFirstVisit);
    readField(properties.unknown2, value, Fields::kUnknown2);
    return properties;
  }

  template<>
  ObjectProperties<ObjectPropertiesType::GARRISON>
  JsonReader<ObjectProperties<ObjectPropertiesType::GARRISON>>::operator()(const Json::Value& value) const
  {
    using Properties = ObjectProperties<ObjectPropertiesType::GARRISON>;
    using Fields = FieldNames<Properties>;
    Properties properties;
    readField(properties.owner, value, Fields::kOwner);
    readField(properties.unknown, value, Fields::kUnknown);
    readField(properties.creatures, value, Fields::kCreatures);
    readField(properties.can_remove_units, value, Fields::kCanRemoveUnits);
    readField(properties.unknown2, value, Fields::kUnknown2);
    return properties;
  }

  template<>
  ObjectProperties<ObjectPropertiesType::GRAIL>
  JsonReader<ObjectProperties<ObjectPropertiesType::GRAIL>>::operator()(const Json::Value& value) const
  {
    using Properties = ObjectProperties<ObjectPropertiesType::GRAIL>;
    using Fields = FieldNames<Properties>;
    Properties properties;
    readField(properties.allowable_radius, value, Fields::kAllowableRadius);
    readField(properties.unknown, value, Fields::kUnknown);
    return properties;
  }

  template<>
  ObjectProperties<ObjectPropertiesType::HERO>
  JsonReader<ObjectProperties<ObjectPropertiesType::HERO>>::operator()(const Json::Value& value) const
  {
    using Properties = ObjectProperties<ObjectPropertiesType::HERO>;
    using Fields = FieldNames<Properties>;
    Properties properties;
    readField(properties.absod_id, value, Fields::kAbsodId);
    readField(properties.owner, value, Fields::kOwner);
    readField(properties.type, value, Fields::kType);
    readField(properties.name, value, Fields::kName);
    readField(properties.experience, value, Fields::kExperience);
    readField(properties.portrait, value, Fields::kPortrait);
    readField(properties.secondary_skills, value, Fields::kSecondarySkills);
    readField(properties.creatures, value, Fields::kCreatures);
    readField(properties.formation, value, Fields::kFormation);
    readField(properties.artifacts, value, Fields::kArtifacts);
    readField(properties.patrol_radius, value, Fields::kPatrolRadius);
    readField(properties.biography, value, Fields::kBiography);
    readField(properties.gender, value, Fields::kGender);
    readField(properties.spells, value, Fields::kSpells);
    readField(properties.primary_skills, value, Fields::kPrimarySkills);
    readField(properties.unknown, value, Fields::kUnknown);
    return properties;
  }

  template<>
  ObjectProperties<ObjectPropertiesType::HERO_PLACEHOLDER>
  JsonReader<ObjectProperties<ObjectPropertiesType::HERO_PLACEHOLDER>>::operator()(const Json::Value& value) const
  {
    using Properties = ObjectProperties<ObjectPropertiesType::HERO_PLACEHOLDER>;
    using Fields = FieldNames<Properties>;
    constexpr h3m::HeroType kRandomHeroType {0xFF};

    Properties properties;
    readField(properties.owner, value, Fields::kOwner);
    readField(properties.type, value, Fields::kType);
    if (properties.type == kRandomHeroType)
    {
      readField(properties.power_rating, value, Fields::kPowerRating);
    }
    return properties;
  }

  template<>
  ObjectProperties<ObjectPropertiesType::MONSTER>
  JsonReader<ObjectProperties<ObjectPropertiesType::MONSTER>>::operator()(const Json::Value& value) const
  {
    using Properties = ObjectProperties<ObjectPropertiesType::MONSTER>;
    using Fields = FieldNames<Properties>;
    Properties properties;
    readField(properties.absod_id, value, Fields::kAbsodId);
    readField(properties.quantity, value, Fields::kQuantity);
    readField(properties.disposition, value, Fields::kDisposition);
    readField(properties.message_and_treasure, value, Fields::kMessageAndTreasure);
    readField(properties.never_flees, value, Fields::kNeverFlees);
    readField(properties.does_not_grow, value, Fields::kDoesNotGrow);
    readField(properties.unknown, value, Fields::kUnknown);
    return properties;
  }

  template<>
  ObjectProperties<ObjectPropertiesType::PANDORAS_BOX>
  JsonReader<ObjectProperties<ObjectPropertiesType::PANDORAS_BOX>>::operator()(const Json::Value& value) const
  {
    return ObjectProperties<ObjectPropertiesType::PANDORAS_BOX>{ fromJson<h3m::EventBase>(value) };
  }

  template<>
  ObjectProperties<ObjectPropertiesType::QUEST_GUARD>
  JsonReader<ObjectProperties<ObjectPropertiesType::QUEST_GUARD>>::operator()(const Json::Value& value) const
  {
    using Properties = ObjectProperties<ObjectPropertiesType::QUEST_GUARD>;
    using Fields = FieldNames<Properties>;
    Properties properties;
    readField(properties.quest, value, Fields::kQuest);
    return properties;
  }

  template<>
  ObjectProperties<ObjectPropertiesType::RANDOM_DWELLING>
  JsonReader<ObjectProperties<ObjectPropertiesType::RANDOM_DWELLING>>::operator()(const Json::Value& value) const
  {
    using Properties = ObjectProperties<ObjectPropertiesType::RANDOM_DWELLING>;
    using Fields = FieldNames<Properties>;
    Properties properties;
    readField(properties.owner, value, Fields::kOwner);
    readField(properties.unknown, value, Fields::kUnknown);
    readField(properties.town_absod_id, value, Fields::kTownAbsodId);
    if (properties.town_absod_id == 0)
    {
      readField(properties.alignment, value, Fields::kAlignment);
    }
    readField(properties.min_level, value, Fields::kMinLevel);
    readField(properties.max_level, value, Fields::kMaxLevel);
    return properties;
  }

  template<>
  ObjectProperties<ObjectPropertiesType::RANDOM_DWELLING_PRESET_ALIGNMENT>
  JsonReader<ObjectProperties<ObjectPropertiesType::RANDOM_DWELLING_PRESET_ALIGNMENT>>::operator()(
    const Json::Value& value) const
  {
    using Properties = ObjectProperties<ObjectPropertiesType::RANDOM_DWELLING_PRESET_ALIGNMENT>;
    using Fields = FieldNames<Properties>;
    Properties properties;
    readField(properties.owner, value, Fields::kOwner);
    readField(properties.unknown, value, Fields::kUnknown);
    readField(properties.min_level, value, Fields::kMinLevel);
    readField(properties.max_level, value, Fields::kMaxLevel);
    return properties;
  }

  template<>
  ObjectProperties<ObjectPropertiesType::RANDOM_DWELLING_PRESET_LEVEL>
  JsonReader<ObjectProperties<ObjectPropertiesType::RANDOM_DWELLING_PRESET_LEVEL>>::operator()(
    const Json::Value& value) const
  {
    using Properties = ObjectProperties<ObjectPropertiesType::RANDOM_DWELLING_PRESET_LEVEL>;
    using Fields = FieldNames<Properties>;
    Properties properties;
    readField(properties.owner, value, Fields::kOwner);
    readField(properties.unknown, value, Fields::kUnknown);
    readField(properties.town_absod_id, value, Fields::kTownAbsodId);
    if (properties.town_absod_id == 0)
    {
      readField(properties.alignment, value, Fields::kAlignment);
    }
    return properties;
  }

  template<>
  ObjectProperties<ObjectPropertiesType::RESOURCE>
  JsonReader<ObjectProperties<ObjectPropertiesType::RESOURCE>>::operator()(const Json::Value& value) const
  {
    using Properties = ObjectProperties<ObjectPropertiesType::RESOURCE>;
    using Fields = FieldNames<Properties>;
    Properties properties;
    readField(properties.guardians, value, Fields::kGuardians);
    readField(properties.quantity, value, Fields::kQuantity);
    readField(properties.unknown, value, Fields::kUnknown);
    return properties;
  }

  template<>
  ObjectProperties<ObjectPropertiesType::SEERS_HUT>
  JsonReader<ObjectProperties<ObjectPropertiesType::SEERS_HUT>>::operator()(const Json::Value& value) const
  {
    using Properties = ObjectProperties<ObjectPropertiesType::SEERS_HUT>;
    using Fields = FieldNames<Properties>;
    Properties properties;
    readField(properties.quest, value, Fields::kQuest);
    readField(properties.reward, value, Fields::kReward);
    readField(properties.unknown, value, Fields::kUnknown);
    return properties;
  }

  template<>
  ObjectProperties<ObjectPropertiesType::SCHOLAR>
  JsonReader<ObjectProperties<ObjectPropertiesType::SCHOLAR>>::operator()(const Json::Value& value) const
  {
    using Properties = ObjectProperties<ObjectPropertiesType::SCHOLAR>;
    using Fields = FieldNames<Properties>;
    Properties properties;
    const h3m::ScholarRewardType reward_type = readField<h3m::ScholarRewardType>(value, Fields::kRewardType);
    properties.reward = VariantJsonReader<Properties::ScholarReward>{}(getJsonField(value, Fields::kRewardValue),
                                                                       Properties::getAlternativeIdx(reward_type));
    readField(properties.unknown, value, Fields::kUnknown);
    return properties;
  }

  template<>
  ObjectProperties<ObjectPropertiesType::SHRINE>
  JsonReader<ObjectProperties<ObjectPropertiesType::SHRINE>>::operator()(const Json::Value& value) const
  {
    using Properties = ObjectProperties<ObjectPropertiesType::SHRINE>;
    using Fields = FieldNames<Properties>;
    Properties properties;
    readField(properties.spell, value, Fields::kSpell);
    readField(properties.unknown, value, Fields::kUnknown);
    return properties;
  }

  template<>
  ObjectProperties<ObjectPropertiesType::SIGN>
  JsonReader<ObjectProperties<ObjectPropertiesType::SIGN>>::operator()(const Json::Value& value) const
  {
    using Properties = ObjectProperties<ObjectPropertiesType::SIGN>;
    using Fields = FieldNames<Properties>;
    Properties properties;
    readField(properties.message, value, Fields::kMessage);
    readField(properties.unknown, value, Fields::kUnknown);
    return properties;
  }

  template<>
  ObjectProperties<ObjectPropertiesType::SPELL_SCROLL>
  JsonReader<ObjectProperties<ObjectPropertiesType::SPELL_SCROLL>>::operator()(const Json::Value& value) const
  {
    using Properties = ObjectProperties<ObjectPropertiesType::SPELL_SCROLL>;
    using Fields = FieldNames<Properties>;
    Properties properties;
    readField(properties.guardians, value, Fields::kGuardians);
    readField(properties.spell, value, Fields::kSpell);
    readField(properties.unknown, value, Fields::kUnknown);
    return properties;
  }

  template<>
  ObjectProperties<ObjectPropertiesType::TOWN>
  JsonReader<ObjectProperties<ObjectPropertiesType::TOWN>>::operator()(const Json::Value& value) const
  {
    using Properties = ObjectProperties<ObjectPropertiesType::TOWN>;
    using Fields = FieldNames<Properties>;
    Properties properties;
    readField(properties.absod_id, value, Fields::kAbsodId);
    readField(properties.owner, value, Fields::kOwner);
    readField(properties.name, value, Fields::kName);
    readField(properties.garrison, value, Fields::kGarrison);
    readField(properties.formation, value, Fields::kFormation);
    readField(properties.buildings, value, Fields::kBuildings);
    if (!properties.buildings)
    {
      readField(properties.has_fort, value, Fields::kHasFort);
    }
    readField(properties.must_have_spell, value, Fields::kMustHaveSpell);
    readField(properties.may_not_have_spell, value, Fields::kMayNotHaveSpell);
    readField(properties.events, value, Fields::kEvents);
    readField(properties.alignment, value, Fields::kAlignment);
    readField(properties.unknown, value, Fields::kUnknown);
    return properties;
  }

  template<>
  ObjectProperties<ObjectPropertiesType::TRIVIAL_OWNED_OBJECT>
  JsonReader<ObjectProperties<ObjectPropertiesType::TRIVIAL_OWNED_OBJECT>>::operator()(const Json::Value& value) const
  {
    using Properties = ObjectProperties<ObjectPropertiesType::TRIVIAL_OWNED_OBJECT>;
    using Fields = FieldNames<Properties>;
    Properties properties;
    readField(properties.owner, value, Fields::kOwner);
    readField(properties.unknown, value, Fields::kUnknown);
    return properties;
  }

  template<>
  ObjectProperties<ObjectPropertiesType::WITCH_HUT>
  JsonReader<ObjectProperties<ObjectPropertiesType::WITCH_HUT>>::operator()(const Json::Value& value) const
  {
    using Properties = ObjectProperties<ObjectPropertiesType::WITCH_HUT>;
    using Fields = FieldNames<Properties>;
    Properties properties;
    readField(properties.potential_skills, value, Fields::kPotentialSkills);
    return properties;
  }

  namespace
  {
    // Wrapper around fromJson<ObjectProperties<T>>(), which returns the result as ObjectPropertiesVariant.
    template<ObjectPropertiesType T>
    ObjectPropertiesVariant readObjectPropertiesAsVariant(const Json::Value& value)
    {
      return fromJson<ObjectProperties<T>>(value);
    }

    // Convert the function template readObjectPropertiesAsVariant<T>() into an alias template,
    // so that it can be passed as a template template parameter to generateSwitchStatement().
    template<ObjectPropertiesType T>
    using ObjectPropertiesReaderTemplateAlias = SwitchStatement_NS::StaticConstant<&readObjectPropertiesAsVariant<T>>;
  }

  // Reads ObjectProperties for the specified ObjectPropertiesType.
  // \param value - input JSON value.
  // \param object_properties_type - ObjectPropertiesType of the object.
  // \return the deserialized data as ObjectPropertiesVariant.
  ObjectPropertiesVariant readObjectPropertiesVariant(const Json::Value& value, ObjectPropertiesType object_properties_type)
  {
    static constexpr auto switch_statement =
      SwitchStatement_NS::generateSwitchStatement<ObjectPropertiesType,
                                                  h3m::kNumObjectPropertiesTypes,
                                                  ObjectPropertiesReaderTemplateAlias>();
    return switch_statement(object_properties_type, value);
  }
}
