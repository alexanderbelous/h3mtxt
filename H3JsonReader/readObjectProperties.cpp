#include <h3mtxt/H3JsonReader/Utils.h>
#include <h3mtxt/JsonCommon/FieldName.h>
#include <h3mtxt/Map/Utils/EnumSequence.h>
#include <h3mtxt/Map/ObjectPropertiesVariant.h>

#include <array>

namespace h3m::H3JsonReader_NS
{
  namespace
  {
    void readEventBase(const Json::Value& value, EventBase& event)
    {
      using Fields = FieldNames<EventBase>;

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
    }
  }

  Guardians JsonReader<Guardians>::operator()(const Json::Value& value) const
  {
    using Fields = FieldNames<Guardians>;
    Guardians guardians;
    readField(guardians.message, value, Fields::kMessage);
    readField(guardians.creatures, value, Fields::kCreatures);
    readField(guardians.unknown, value, Fields::kUnknown);
    return guardians;
  }

  MessageAndTreasure JsonReader<MessageAndTreasure>::operator()(const Json::Value& value) const
  {
    using Fields = FieldNames<MessageAndTreasure>;
    MessageAndTreasure message_and_treasure;
    readField(message_and_treasure.message, value, Fields::kMessage);
    readField(message_and_treasure.resources, value, Fields::kResources);
    readField(message_and_treasure.artifact, value, Fields::kArtifact);
    return message_and_treasure;
  }

  TownBuildings JsonReader<TownBuildings>::operator()(const Json::Value& value) const
  {
    using Fields = FieldNames<TownBuildings>;
    TownBuildings town_buildings;
    readField(town_buildings.is_built, value, Fields::kIsBuilt);
    readField(town_buildings.is_disabled, value, Fields::kIsDisabled);
    return town_buildings;
  }

  TownEvent JsonReader<TownEvent>::operator()(const Json::Value& value) const
  {
    using Fields = FieldNames<TownEvent>;
    TownEvent event{ JsonReader<TimedEvent>{}(value) };
    readField(event.buildings, value, Fields::kBuildings);
    readField(event.creatures, value, Fields::kCreatures);
    readField(event.unknown2, value, Fields::kUnknown2);
    return event;
  }

  template<>
  struct JsonReader<ObjectProperties<ObjectPropertiesType::ABANDONED_MINE>>
  {
    using Details = ObjectProperties<ObjectPropertiesType::ABANDONED_MINE>;

    Details operator()(const Json::Value& value) const
    {
      using Fields = FieldNames<Details>;
      Details details;
      readField(details.potential_resources, value, Fields::kPotentialResources);
      readField(details.unknown, value, Fields::kUnknown);
      return details;
    }
  };

  template<>
  struct JsonReader<ObjectProperties<ObjectPropertiesType::ARTIFACT>>
  {
    using Details = ObjectProperties<ObjectPropertiesType::ARTIFACT>;

    Details operator()(const Json::Value& value) const
    {
      using Fields = FieldNames<Details>;
      Details details;
      readField(details.guardians, value, Fields::kGuardians);
      return details;
    }
  };

  template<>
  struct JsonReader<ObjectProperties<ObjectPropertiesType::EVENT>>
  {
    using Details = ObjectProperties<ObjectPropertiesType::EVENT>;

    Details operator()(const Json::Value& value) const
    {
      using Fields = FieldNames<Details>;
      Details details;
      readEventBase(value, details);
      readField(details.affected_players, value, Fields::kAffectedPlayers);
      readField(details.applies_to_computer, value, Fields::kAppliesToComputer);
      readField(details.remove_after_first_visit, value, Fields::kRemoveAfterFirstVisit);
      readField(details.unknown2, value, Fields::kUnknown2);
      return details;
    }
  };

  template<>
  struct JsonReader<ObjectProperties<ObjectPropertiesType::GARRISON>>
  {
    using Details = ObjectProperties<ObjectPropertiesType::GARRISON>;

    Details operator()(const Json::Value& value) const
    {
      using Fields = FieldNames<Details>;
      Details details;
      readField(details.owner, value, Fields::kOwner);
      readField(details.unknown, value, Fields::kUnknown);
      readField(details.creatures, value, Fields::kCreatures);
      readField(details.can_remove_units, value, Fields::kCanRemoveUnits);
      readField(details.unknown2, value, Fields::kUnknown2);
      return details;
    }
  };

  // ObjectProperties<ObjectPropertiesType::GENERIC_NO_PROPERTIES> has no fields.
  template<>
  struct JsonReader<ObjectProperties<ObjectPropertiesType::GENERIC_NO_PROPERTIES>>
  {
    ObjectProperties<ObjectPropertiesType::GENERIC_NO_PROPERTIES> operator()(const Json::Value&) const
    {
      return {};
    }
  };

  template<>
  struct JsonReader<ObjectProperties<ObjectPropertiesType::GRAIL>>
  {
    using Details = ObjectProperties<ObjectPropertiesType::GRAIL>;

    Details operator()(const Json::Value& value) const
    {
      using Fields = FieldNames<Details>;
      Details details;
      readField(details.allowable_radius, value, Fields::kAllowableRadius);
      readField(details.unknown, value, Fields::kUnknown);
      return details;
    }
  };

  template<>
  struct JsonReader<ObjectProperties<ObjectPropertiesType::HERO>>
  {
    using Details = ObjectProperties<ObjectPropertiesType::HERO>;

    Details operator()(const Json::Value& value) const
    {
      using Fields = FieldNames<Details>;
      Details details;
      readField(details.absod_id, value, Fields::kAbsodId);
      readField(details.owner, value, Fields::kOwner);
      readField(details.type, value, Fields::kType);
      readField(details.name, value, Fields::kName);
      readField(details.experience, value, Fields::kExperience);
      readField(details.portrait, value, Fields::kPortrait);
      readField(details.secondary_skills, value, Fields::kSecondarySkills);
      readField(details.creatures, value, Fields::kCreatures);
      readField(details.formation, value, Fields::kFormation);
      readField(details.artifacts, value, Fields::kArtifacts);
      readField(details.patrol_radius, value, Fields::kPatrolRadius);
      readField(details.biography, value, Fields::kBiography);
      readField(details.gender, value, Fields::kGender);
      readField(details.spells, value, Fields::kSpells);
      readField(details.primary_skills, value, Fields::kPrimarySkills);
      readField(details.unknown, value, Fields::kUnknown);
      return details;
    }
  };

  template<>
  struct JsonReader<ObjectProperties<ObjectPropertiesType::MONSTER>>
  {
    using Details = ObjectProperties<ObjectPropertiesType::MONSTER>;

    Details operator()(const Json::Value& value) const
    {
      using Fields = FieldNames<Details>;
      Details details;
      readField(details.absod_id, value, Fields::kAbsodId);
      readField(details.count, value, Fields::kCount);
      readField(details.disposition, value, Fields::kDisposition);
      readField(details.message_and_treasure, value, Fields::kMessageAndTreasure);
      readField(details.never_flees, value, Fields::kNeverFlees);
      readField(details.does_not_grow, value, Fields::kDoesNotGrow);
      readField(details.unknown, value, Fields::kUnknown);
      return details;
    }
  };

  template<>
  struct JsonReader<ObjectProperties<ObjectPropertiesType::PANDORAS_BOX>>
  {
    using Details = ObjectProperties<ObjectPropertiesType::PANDORAS_BOX>;

    Details operator()(const Json::Value& value) const
    {
      Details details;
      readEventBase(value, details);
      return details;
    }
  };

  template<>
  struct JsonReader<ObjectProperties<ObjectPropertiesType::PLACEHOLDER_HERO>>
  {
    using Details = ObjectProperties<ObjectPropertiesType::PLACEHOLDER_HERO>;

    Details operator()(const Json::Value& value) const
    {
      using Fields = FieldNames<Details>;
      constexpr h3m::HeroType kRandomHeroType {0xFF};

      Details details;
      readField(details.owner, value, Fields::kOwner);
      readField(details.type, value, Fields::kType);
      if (details.type == kRandomHeroType)
      {
        readField(details.power_rating, value, Fields::kPowerRating);
      }
      return details;
    }
  };

  template<>
  struct JsonReader<ObjectProperties<ObjectPropertiesType::QUEST_GUARD>>
  {
    using Details = ObjectProperties<ObjectPropertiesType::QUEST_GUARD>;

    Details operator()(const Json::Value& value) const
    {
      using Fields = FieldNames<Details>;
      Details details;
      readField(details.quest, value, Fields::kQuest);
      return details;
    }
  };

  template<>
  struct JsonReader<ObjectProperties<ObjectPropertiesType::RANDOM_DWELLING>>
  {
    using Details = ObjectProperties<ObjectPropertiesType::RANDOM_DWELLING>;

    Details operator()(const Json::Value& value) const
    {
      using Fields = FieldNames<Details>;
      Details details;
      readField(details.owner, value, Fields::kOwner);
      readField(details.town_absod_id, value, Fields::kTownAbsodId);
      if (details.town_absod_id == 0)
      {
        readField(details.alignment, value, Fields::kAlignment);
      }
      readField(details.min_level, value, Fields::kMinLevel);
      readField(details.max_level, value, Fields::kMaxLevel);
      return details;
    }
  };

  template<>
  struct JsonReader<ObjectProperties<ObjectPropertiesType::RANDOM_DWELLING_PRESET_ALIGNMENT>>
  {
    using Details = ObjectProperties<ObjectPropertiesType::RANDOM_DWELLING_PRESET_ALIGNMENT>;

    Details operator()(const Json::Value& value) const
    {
      using Fields = FieldNames<Details>;
      Details details;
      readField(details.owner, value, Fields::kOwner);
      readField(details.min_level, value, Fields::kMinLevel);
      readField(details.max_level, value, Fields::kMaxLevel);
      return details;
    }
  };

  template<>
  struct JsonReader<ObjectProperties<ObjectPropertiesType::RANDOM_DWELLING_PRESET_LEVEL>>
  {
    using Details = ObjectProperties<ObjectPropertiesType::RANDOM_DWELLING_PRESET_LEVEL>;

    Details operator()(const Json::Value& value) const
    {
      using Fields = FieldNames<Details>;
      Details details;
      readField(details.owner, value, Fields::kOwner);
      readField(details.town_absod_id, value, Fields::kTownAbsodId);
      if (details.town_absod_id == 0)
      {
        readField(details.alignment, value, Fields::kAlignment);
      }
      return details;
    }
  };

  template<>
  struct JsonReader<ObjectProperties<ObjectPropertiesType::RESOURCE>>
  {
    using Details = ObjectProperties<ObjectPropertiesType::RESOURCE>;

    Details operator()(const Json::Value& value) const
    {
      using Fields = FieldNames<Details>;
      Details details;
      readField(details.guardians, value, Fields::kGuardians);
      readField(details.quantity, value, Fields::kQuantity);
      readField(details.unknown, value, Fields::kUnknown);
      return details;
    }
  };

  template<>
  struct JsonReader<ObjectProperties<ObjectPropertiesType::SEERS_HUT>>
  {
    using Details = ObjectProperties<ObjectPropertiesType::SEERS_HUT>;

    Details operator()(const Json::Value& value) const
    {
      using Fields = FieldNames<Details>;
      Details details;
      readField(details.quest, value, Fields::kQuest);
      readField(details.reward, value, Fields::kReward);
      readField(details.unknown, value, Fields::kUnknown);
      return details;
    }
  };

  template<>
  struct JsonReader<ObjectProperties<ObjectPropertiesType::SCHOLAR>>
  {
    using Details = ObjectProperties<ObjectPropertiesType::SCHOLAR>;

    Details operator()(const Json::Value& value) const
    {
      using Fields = FieldNames<Details>;
      Details details;
      readField(details.reward_type, value, Fields::kRewardType);
      readField(details.reward_value, value, Fields::kRewardValue);
      readField(details.unknown, value, Fields::kUnknown);
      return details;
    }
  };

  template<>
  struct JsonReader<ObjectProperties<ObjectPropertiesType::SHRINE>>
  {
    using Details = ObjectProperties<ObjectPropertiesType::SHRINE>;

    Details operator()(const Json::Value& value) const
    {
      using Fields = FieldNames<Details>;
      Details details;
      readField(details.spell, value, Fields::kSpell);
      readField(details.unknown, value, Fields::kUnknown);
      return details;
    }
  };

  template<>
  struct JsonReader<ObjectProperties<ObjectPropertiesType::SIGN>>
  {
    using Details = ObjectProperties<ObjectPropertiesType::SIGN>;

    Details operator()(const Json::Value& value) const
    {
      using Fields = FieldNames<Details>;
      Details details;
      readField(details.message, value, Fields::kMessage);
      readField(details.unknown, value, Fields::kUnknown);
      return details;
    }
  };

  template<>
  struct JsonReader<ObjectProperties<ObjectPropertiesType::SPELL_SCROLL>>
  {
    using Details = ObjectProperties<ObjectPropertiesType::SPELL_SCROLL>;

    Details operator()(const Json::Value& value) const
    {
      using Fields = FieldNames<Details>;
      Details details;
      readField(details.guardians, value, Fields::kGuardians);
      readField(details.spell, value, Fields::kSpell);
      readField(details.unknown, value, Fields::kUnknown);
      return details;
    }
  };

  template<>
  struct JsonReader<ObjectProperties<ObjectPropertiesType::TOWN>>
  {
    using Details = ObjectProperties<ObjectPropertiesType::TOWN>;

    Details operator()(const Json::Value& value) const
    {
      using Fields = FieldNames<Details>;
      Details details;
      readField(details.absod_id, value, Fields::kAbsodId);
      readField(details.owner, value, Fields::kOwner);
      readField(details.name, value, Fields::kName);
      readField(details.garrison, value, Fields::kGarrison);
      readField(details.formation, value, Fields::kFormation);
      readField(details.buildings, value, Fields::kBuildings);
      if (!details.buildings)
      {
        readField(details.has_fort, value, Fields::kHasFort);
      }
      readField(details.must_have_spell, value, Fields::kMustHaveSpell);
      readField(details.may_not_have_spell, value, Fields::kMayNotHaveSpell);
      readField(details.events, value, Fields::kEvents);
      readField(details.alignment, value, Fields::kAlignment);
      readField(details.unknown, value, Fields::kUnknown);
      return details;
    }
  };

  template<>
  struct JsonReader<ObjectProperties<ObjectPropertiesType::TRIVIAL_OWNED_OBJECT>>
  {
    using Details = ObjectProperties<ObjectPropertiesType::TRIVIAL_OWNED_OBJECT>;

    Details operator()(const Json::Value& value) const
    {
      using Fields = FieldNames<Details>;
      Details details;
      readField(details.owner, value, Fields::kOwner);
      readField(details.unknown, value, Fields::kUnknown);
      return details;
    }
  };

  template<>
  struct JsonReader<ObjectProperties<ObjectPropertiesType::WITCH_HUT>>
  {
    using Details = ObjectProperties<ObjectPropertiesType::WITCH_HUT>;

    Details operator()(const Json::Value& value) const
    {
      using Fields = FieldNames<Details>;
      Details details;
      readField(details.potential_skills, value, Fields::kPotentialSkills);
      return details;
    }
  };

  namespace
  {
    // Utility wrapper around fromJson<ObjectProperties<T>>(), which returns the result
    // as ObjectPropertiesVariant.
    template<ObjectPropertiesType T>
    ObjectPropertiesVariant readObjectPropertiesAsVariant(const Json::Value& value)
    {
      return fromJson<ObjectProperties<T>>(value);
    }
  }

  // Reads ObjectProperties for the specified ObjectPropertiesType.
  // \param value - input JSON value.
  // \param object_properties_type - ObjectPropertiesType of the object.
  // \return the deserialized data as ObjectPropertiesVariant.
  ObjectPropertiesVariant readObjectPropertiesVariant(const Json::Value& value, ObjectPropertiesType object_properties_type)
  {
    // Type of a pointer to a function that takes std::istream& and returns ObjectPropertiesVariant.
    using ReadObjectPropertiesPtr = ObjectPropertiesVariant(*)(const Json::Value&);
    // Generate (at compile time) an array of function pointers for each instantiation of
    // readObjectPropertiesAsVariant() ordered by ObjectPropertiesType.
    constexpr std::array<ReadObjectPropertiesPtr, kNumObjectPropertiesTypes> kObjectPropertiesReaders =
      [] <ObjectPropertiesType... object_properties_types>
      (EnumSequence<ObjectPropertiesType, object_properties_types...> seq)
      consteval
      {
        return std::array<ReadObjectPropertiesPtr, sizeof...(object_properties_types)>
        { &readObjectPropertiesAsVariant<object_properties_types>... };
      }(MakeEnumSequence<ObjectPropertiesType, kNumObjectPropertiesTypes>{});
    // Invoke a function from the generated array.
    return kObjectPropertiesReaders.at(static_cast<std::size_t>(object_properties_type))(value);
  }
}
