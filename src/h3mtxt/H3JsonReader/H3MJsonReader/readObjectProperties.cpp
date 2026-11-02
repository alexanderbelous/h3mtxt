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
  h3m::EventBase JsonReader2<h3m::EventBase>::operator()() const
  {
    using Fields = FieldNames<h3m::EventBase>;
    h3m::EventBase event;
    readField(Fields::kGuardians, event.guardians);
    readField(Fields::kExperience, event.experience);
    readField(Fields::kSpellPoints, event.spell_points);
    readField(Fields::kMorale, event.morale);
    readField(Fields::kLuck, event.luck);
    readField(Fields::kResources, event.resources);
    readField(Fields::kPrimarySkills, event.primary_skills);
    readField(Fields::kSecondarySkills, event.secondary_skills);
    readField(Fields::kArtifacts, event.artifacts);
    readField(Fields::kSpells, event.spells);
    readField(Fields::kCreatures, event.creatures);
    readField(Fields::kUnknown, event.unknown);
    return event;
  }

  template<>
  h3m::Guardians JsonReader2<h3m::Guardians>::operator()() const
  {
    using Fields = FieldNames<h3m::Guardians>;
    h3m::Guardians guardians;
    readField(Fields::kMessage, guardians.message);
    readField(Fields::kCreatures, guardians.creatures);
    readField(Fields::kUnknown, guardians.unknown);
    return guardians;
  }

  template<>
  h3m::MessageAndTreasure JsonReader2<h3m::MessageAndTreasure>::operator()() const
  {
    using Fields = FieldNames<h3m::MessageAndTreasure>;
    h3m::MessageAndTreasure message_and_treasure;
    readField(Fields::kMessage, message_and_treasure.message);
    readField(Fields::kResources, message_and_treasure.resources);
    readField(Fields::kArtifact, message_and_treasure.artifact);
    return message_and_treasure;
  }

  template<>
  h3m::TownBuildings JsonReader2<h3m::TownBuildings>::operator()() const
  {
    using Fields = FieldNames<h3m::TownBuildings>;
    h3m::TownBuildings town_buildings;
    readField(Fields::kIsBuilt, town_buildings.is_built);
    readField(Fields::kIsDisabled, town_buildings.is_disabled);
    return town_buildings;
  }

  template<>
  h3m::TownEvent JsonReader2<h3m::TownEvent>::operator()() const
  {
    using Fields = FieldNames<h3m::TownEvent>;
    h3m::TownEvent event{ fromJson<h3m::TimedEvent>(value()) };
    readField(Fields::kBuildings, event.buildings);
    readField(Fields::kCreatures, event.creatures);
    readField(Fields::kUnknown2, event.unknown2);
    return event;
  }

  template<>
  ObjectProperties<ObjectPropertiesType::NONE>
  JsonReader2<ObjectProperties<ObjectPropertiesType::NONE>>::operator()() const
  {
    // ObjectProperties<ObjectPropertiesType::NONE> has no fields.
    return {};
  }

  template<>
  ObjectProperties<ObjectPropertiesType::ABANDONED_MINE>
  JsonReader2<ObjectProperties<ObjectPropertiesType::ABANDONED_MINE>>::operator()() const
  {
    using Properties = ObjectProperties<ObjectPropertiesType::ABANDONED_MINE>;
    using Fields = FieldNames<Properties>;
    Properties properties;
    readField(Fields::kPotentialResources, properties.potential_resources);
    readField(Fields::kUnknown, properties.unknown);
    return properties;
  }

  template<>
  ObjectProperties<ObjectPropertiesType::ARTIFACT>
  JsonReader2<ObjectProperties<ObjectPropertiesType::ARTIFACT>>::operator()() const
  {
    using Properties = ObjectProperties<ObjectPropertiesType::ARTIFACT>;
    using Fields = FieldNames<Properties>;
    Properties properties;
    readField(Fields::kGuardians, properties.guardians);
    return properties;
  }

  template<>
  ObjectProperties<ObjectPropertiesType::EVENT>
  JsonReader2<ObjectProperties<ObjectPropertiesType::EVENT>>::operator()() const
  {
    using Properties = ObjectProperties<ObjectPropertiesType::EVENT>;
    using Fields = FieldNames<Properties>;
    Properties properties{ fromJson<h3m::EventBase>(value()) };
    readField(Fields::kAffectedPlayers, properties.affected_players);
    readField(Fields::kAppliesToComputer, properties.applies_to_computer);
    readField(Fields::kCancelAfterFirstVisit, properties.cancel_after_first_visit);
    readField(Fields::kUnknown2, properties.unknown2);
    return properties;
  }

  template<>
  ObjectProperties<ObjectPropertiesType::GARRISON>
  JsonReader2<ObjectProperties<ObjectPropertiesType::GARRISON>>::operator()() const
  {
    using Properties = ObjectProperties<ObjectPropertiesType::GARRISON>;
    using Fields = FieldNames<Properties>;
    Properties properties;
    readField(Fields::kOwner, properties.owner);
    readField(Fields::kUnknown, properties.unknown);
    readField(Fields::kCreatures, properties.creatures);
    readField(Fields::kCanRemoveUnits, properties.can_remove_units);
    readField(Fields::kUnknown2, properties.unknown2);
    return properties;
  }

  template<>
  ObjectProperties<ObjectPropertiesType::GRAIL>
  JsonReader2<ObjectProperties<ObjectPropertiesType::GRAIL>>::operator()() const
  {
    using Properties = ObjectProperties<ObjectPropertiesType::GRAIL>;
    using Fields = FieldNames<Properties>;
    Properties properties;
    readField(Fields::kAllowableRadius, properties.allowable_radius);
    readField(Fields::kUnknown, properties.unknown);
    return properties;
  }

  template<>
  ObjectProperties<ObjectPropertiesType::HERO>
  JsonReader2<ObjectProperties<ObjectPropertiesType::HERO>>::operator()() const
  {
    using Properties = ObjectProperties<ObjectPropertiesType::HERO>;
    using Fields = FieldNames<Properties>;
    Properties properties;
    readField(Fields::kAbsodId, properties.absod_id);
    readField(Fields::kOwner, properties.owner);
    readField(Fields::kType, properties.type);
    readField(Fields::kName, properties.name);
    readField(Fields::kExperience, properties.experience);
    readField(Fields::kPortrait, properties.portrait);
    readField(Fields::kSecondarySkills, properties.secondary_skills);
    readField(Fields::kCreatures, properties.creatures);
    readField(Fields::kFormation, properties.formation);
    readField(Fields::kArtifacts, properties.artifacts);
    readField(Fields::kPatrolRadius, properties.patrol_radius);
    readField(Fields::kBiography, properties.biography);
    readField(Fields::kGender, properties.gender);
    readField(Fields::kSpells, properties.spells);
    readField(Fields::kPrimarySkills, properties.primary_skills);
    readField(Fields::kUnknown, properties.unknown);
    return properties;
  }

  template<>
  ObjectProperties<ObjectPropertiesType::HERO_PLACEHOLDER>
  JsonReader2<ObjectProperties<ObjectPropertiesType::HERO_PLACEHOLDER>>::operator()() const
  {
    using Properties = ObjectProperties<ObjectPropertiesType::HERO_PLACEHOLDER>;
    using Fields = FieldNames<Properties>;
    constexpr h3m::HeroType kRandomHeroType {0xFF};

    Properties properties;
    readField(Fields::kOwner, properties.owner);
    readField(Fields::kType, properties.type);
    if (properties.type == kRandomHeroType)
    {
      readField(Fields::kPowerRating, properties.power_rating);
    }
    return properties;
  }

  template<>
  ObjectProperties<ObjectPropertiesType::MONSTER>
  JsonReader2<ObjectProperties<ObjectPropertiesType::MONSTER>>::operator()() const
  {
    using Properties = ObjectProperties<ObjectPropertiesType::MONSTER>;
    using Fields = FieldNames<Properties>;
    Properties properties;
    readField(Fields::kAbsodId, properties.absod_id);
    readField(Fields::kQuantity, properties.quantity);
    readField(Fields::kDisposition, properties.disposition);
    readField(Fields::kMessageAndTreasure, properties.message_and_treasure);
    readField(Fields::kNeverFlees, properties.never_flees);
    readField(Fields::kDoesNotGrow, properties.does_not_grow);
    readField(Fields::kUnknown, properties.unknown);
    return properties;
  }

  template<>
  ObjectProperties<ObjectPropertiesType::PANDORAS_BOX>
  JsonReader2<ObjectProperties<ObjectPropertiesType::PANDORAS_BOX>>::operator()() const
  {
    return ObjectProperties<ObjectPropertiesType::PANDORAS_BOX>{ fromJson<h3m::EventBase>(value()) };
  }

  template<>
  ObjectProperties<ObjectPropertiesType::QUEST_GUARD>
  JsonReader2<ObjectProperties<ObjectPropertiesType::QUEST_GUARD>>::operator()() const
  {
    using Properties = ObjectProperties<ObjectPropertiesType::QUEST_GUARD>;
    using Fields = FieldNames<Properties>;
    Properties properties;
    readField(Fields::kQuest, properties.quest);
    return properties;
  }

  template<>
  ObjectProperties<ObjectPropertiesType::RANDOM_DWELLING>
  JsonReader2<ObjectProperties<ObjectPropertiesType::RANDOM_DWELLING>>::operator()() const
  {
    using Properties = ObjectProperties<ObjectPropertiesType::RANDOM_DWELLING>;
    using Fields = FieldNames<Properties>;
    Properties properties;
    readField(Fields::kOwner, properties.owner);
    readField(Fields::kUnknown, properties.unknown);
    readField(Fields::kTownAbsodId, properties.town_absod_id);
    if (properties.town_absod_id == 0)
    {
      readField(Fields::kAlignment, properties.alignment);
    }
    readField(Fields::kMinLevel, properties.min_level);
    readField(Fields::kMaxLevel, properties.max_level);
    return properties;
  }

  template<>
  ObjectProperties<ObjectPropertiesType::RANDOM_DWELLING_PRESET_ALIGNMENT>
  JsonReader2<ObjectProperties<ObjectPropertiesType::RANDOM_DWELLING_PRESET_ALIGNMENT>>::operator()() const
  {
    using Properties = ObjectProperties<ObjectPropertiesType::RANDOM_DWELLING_PRESET_ALIGNMENT>;
    using Fields = FieldNames<Properties>;
    Properties properties;
    readField(Fields::kOwner, properties.owner);
    readField(Fields::kUnknown, properties.unknown);
    readField(Fields::kMinLevel, properties.min_level);
    readField(Fields::kMaxLevel, properties.max_level);
    return properties;
  }

  template<>
  ObjectProperties<ObjectPropertiesType::RANDOM_DWELLING_PRESET_LEVEL>
  JsonReader2<ObjectProperties<ObjectPropertiesType::RANDOM_DWELLING_PRESET_LEVEL>>::operator()() const
  {
    using Properties = ObjectProperties<ObjectPropertiesType::RANDOM_DWELLING_PRESET_LEVEL>;
    using Fields = FieldNames<Properties>;
    Properties properties;
    readField(Fields::kOwner, properties.owner);
    readField(Fields::kUnknown, properties.unknown);
    readField(Fields::kTownAbsodId, properties.town_absod_id);
    if (properties.town_absod_id == 0)
    {
      readField(Fields::kAlignment, properties.alignment);
    }
    return properties;
  }

  template<>
  ObjectProperties<ObjectPropertiesType::RESOURCE>
  JsonReader2<ObjectProperties<ObjectPropertiesType::RESOURCE>>::operator()() const
  {
    using Properties = ObjectProperties<ObjectPropertiesType::RESOURCE>;
    using Fields = FieldNames<Properties>;
    Properties properties;
    readField(Fields::kGuardians, properties.guardians);
    readField(Fields::kQuantity, properties.quantity);
    readField(Fields::kUnknown, properties.unknown);
    return properties;
  }

  template<>
  ObjectProperties<ObjectPropertiesType::SEERS_HUT>
  JsonReader2<ObjectProperties<ObjectPropertiesType::SEERS_HUT>>::operator()() const
  {
    using Properties = ObjectProperties<ObjectPropertiesType::SEERS_HUT>;
    using Fields = FieldNames<Properties>;
    Properties properties;
    readField(Fields::kQuest, properties.quest);
    readField(Fields::kReward, properties.reward);
    readField(Fields::kUnknown, properties.unknown);
    return properties;
  }

  template<>
  ObjectProperties<ObjectPropertiesType::SCHOLAR>
  JsonReader2<ObjectProperties<ObjectPropertiesType::SCHOLAR>>::operator()() const
  {
    using Properties = ObjectProperties<ObjectPropertiesType::SCHOLAR>;
    using Fields = FieldNames<Properties>;
    Properties properties;
    const h3m::ScholarRewardType reward_type = readField<h3m::ScholarRewardType>(Fields::kRewardType);
    properties.reward = VariantJsonReader<Properties::ScholarReward>{}(getField(Fields::kRewardValue),
                                                                       Properties::getAlternativeIdx(reward_type));
    readField(Fields::kUnknown, properties.unknown);
    return properties;
  }

  template<>
  ObjectProperties<ObjectPropertiesType::SHRINE>
  JsonReader2<ObjectProperties<ObjectPropertiesType::SHRINE>>::operator()() const
  {
    using Properties = ObjectProperties<ObjectPropertiesType::SHRINE>;
    using Fields = FieldNames<Properties>;
    Properties properties;
    readField(Fields::kSpell, properties.spell);
    readField(Fields::kUnknown, properties.unknown);
    return properties;
  }

  template<>
  ObjectProperties<ObjectPropertiesType::SIGN>
  JsonReader2<ObjectProperties<ObjectPropertiesType::SIGN>>::operator()() const
  {
    using Properties = ObjectProperties<ObjectPropertiesType::SIGN>;
    using Fields = FieldNames<Properties>;
    Properties properties;
    readField(Fields::kMessage, properties.message);
    readField(Fields::kUnknown, properties.unknown);
    return properties;
  }

  template<>
  ObjectProperties<ObjectPropertiesType::SPELL_SCROLL>
  JsonReader2<ObjectProperties<ObjectPropertiesType::SPELL_SCROLL>>::operator()() const
  {
    using Properties = ObjectProperties<ObjectPropertiesType::SPELL_SCROLL>;
    using Fields = FieldNames<Properties>;
    Properties properties;
    readField(Fields::kGuardians, properties.guardians);
    readField(Fields::kSpell, properties.spell);
    readField(Fields::kUnknown, properties.unknown);
    return properties;
  }

  template<>
  ObjectProperties<ObjectPropertiesType::TOWN>
  JsonReader2<ObjectProperties<ObjectPropertiesType::TOWN>>::operator()() const
  {
    using Properties = ObjectProperties<ObjectPropertiesType::TOWN>;
    using Fields = FieldNames<Properties>;
    Properties properties;
    readField(Fields::kAbsodId, properties.absod_id);
    readField(Fields::kOwner, properties.owner);
    readField(Fields::kName, properties.name);
    readField(Fields::kGarrison, properties.garrison);
    readField(Fields::kFormation, properties.formation);
    readField(Fields::kBuildings, properties.buildings);
    if (!properties.buildings)
    {
      readField(Fields::kHasFort, properties.has_fort);
    }
    readField(Fields::kMustHaveSpell, properties.must_have_spell);
    readField(Fields::kMayNotHaveSpell, properties.may_not_have_spell);
    readField(Fields::kEvents, properties.events);
    readField(Fields::kAlignment, properties.alignment);
    readField(Fields::kUnknown, properties.unknown);
    return properties;
  }

  template<>
  ObjectProperties<ObjectPropertiesType::TRIVIAL_OWNED_OBJECT>
  JsonReader2<ObjectProperties<ObjectPropertiesType::TRIVIAL_OWNED_OBJECT>>::operator()() const
  {
    using Properties = ObjectProperties<ObjectPropertiesType::TRIVIAL_OWNED_OBJECT>;
    using Fields = FieldNames<Properties>;
    Properties properties;
    readField(Fields::kOwner, properties.owner);
    readField(Fields::kUnknown, properties.unknown);
    return properties;
  }

  template<>
  ObjectProperties<ObjectPropertiesType::WITCH_HUT>
  JsonReader2<ObjectProperties<ObjectPropertiesType::WITCH_HUT>>::operator()() const
  {
    using Properties = ObjectProperties<ObjectPropertiesType::WITCH_HUT>;
    using Fields = FieldNames<Properties>;
    Properties properties;
    readField(Fields::kPotentialSkills, properties.potential_skills);
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
