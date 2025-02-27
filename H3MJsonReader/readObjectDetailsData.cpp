#include <h3mtxt/H3MJsonReader/Utils.h>
#include <h3mtxt/JsonCommon/FieldName.h>
#include <h3mtxt/Map/Utils/EnumSequence.h>
#include <h3mtxt/Map/ObjectDetailsDataVariant.h>

#include <array>

namespace h3m
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

  ResourcesBitmask JsonReader<ResourcesBitmask>::operator()(const Json::Value& value) const
  {
    using Fields = FieldNames<ResourcesBitmask>;
    ResourcesBitmask bitmask;
    for (std::uint8_t i = 0; i < 8; ++i)
    {
      bitmask.set(static_cast<h3m::ResourceType>(i), readField<bool>(value, Fields::kNames[i]));
    }
    return bitmask;
  }

  TownsBuildingsBitmask JsonReader<TownsBuildingsBitmask>::operator()(const Json::Value& value) const
  {
    using Fields = FieldNames<TownsBuildingsBitmask>;
    TownsBuildingsBitmask bitmask;
    for (std::size_t i = 0; i < TownsBuildingsBitmask::kNumBits; ++i)
    {
      bitmask.bitset.set(i, readField<bool>(value, Fields::kNames[i]));
    }
    return bitmask;
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
    TownEvent event;
    ::h3m::H3MJsonReader_NS::readTimedEventBase(event, value);
    readField(event.buildings, value, Fields::kBuildings);
    readField(event.creatures, value, Fields::kCreatures);
    readField(event.unknown2, value, Fields::kUnknown2);
    return event;
  }

  template<>
  struct JsonReader<ObjectDetailsData<MetaObjectType::ABANDONED_MINE>>
  {
    using DetailsData = ObjectDetailsData<MetaObjectType::ABANDONED_MINE>;

    DetailsData operator()(const Json::Value& value) const
    {
      using Fields = FieldNames<DetailsData>;
      DetailsData details;
      readField(details.potential_resources, value, Fields::kPotentialResources);
      readField(details.unknown, value, Fields::kUnknown);
      return details;
    }
  };

  template<>
  struct JsonReader<ObjectDetailsData<MetaObjectType::ARTIFACT>>
  {
    using DetailsData = ObjectDetailsData<MetaObjectType::ARTIFACT>;

    DetailsData operator()(const Json::Value& value) const
    {
      using Fields = FieldNames<DetailsData>;
      DetailsData details;
      readField(details.guardians, value, Fields::kGuardians);
      return details;
    }
  };

  template<>
  struct JsonReader<ObjectDetailsData<MetaObjectType::EVENT>>
  {
    using DetailsData = ObjectDetailsData<MetaObjectType::EVENT>;

    DetailsData operator()(const Json::Value& value) const
    {
      using Fields = FieldNames<DetailsData>;
      DetailsData details;
      readEventBase(value, details);
      readField(details.affected_players, value, Fields::kAffectedPlayers);
      readField(details.applies_to_computer, value, Fields::kAppliesToComputer);
      readField(details.remove_after_first_visit, value, Fields::kRemoveAfterFirstVisit);
      readField(details.unknown2, value, Fields::kUnknown2);
      return details;
    }
  };

  template<>
  struct JsonReader<ObjectDetailsData<MetaObjectType::GARRISON>>
  {
    using DetailsData = ObjectDetailsData<MetaObjectType::GARRISON>;

    DetailsData operator()(const Json::Value& value) const
    {
      using Fields = FieldNames<DetailsData>;
      DetailsData details;
      readField(details.owner, value, Fields::kOwner);
      readField(details.creatures, value, Fields::kCreatures);
      readField(details.can_remove_units, value, Fields::kCanRemoveUnits);
      readField(details.unknown, value, Fields::kUnknown);
      return details;
    }
  };

  // ObjectDetailsData<MetaObjectType::GENERIC_NO_PROPERTIES> has no fields.
  template<>
  struct JsonReader<ObjectDetailsData<MetaObjectType::GENERIC_NO_PROPERTIES>>
  {
    ObjectDetailsData<MetaObjectType::GENERIC_NO_PROPERTIES> operator()(const Json::Value&) const
    {
      return {};
    }
  };

  template<>
  struct JsonReader<ObjectDetailsData<MetaObjectType::GRAIL>>
  {
    using DetailsData = ObjectDetailsData<MetaObjectType::GRAIL>;

    DetailsData operator()(const Json::Value& value) const
    {
      using Fields = FieldNames<DetailsData>;
      DetailsData details;
      readField(details.allowable_radius, value, Fields::kAllowableRadius);
      return details;
    }
  };

  template<>
  struct JsonReader<ObjectDetailsData<MetaObjectType::HERO>>
  {
    using DetailsData = ObjectDetailsData<MetaObjectType::HERO>;

    DetailsData operator()(const Json::Value& value) const
    {
      using Fields = FieldNames<DetailsData>;
      DetailsData details;
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
  struct JsonReader<ObjectDetailsData<MetaObjectType::MONSTER>>
  {
    using DetailsData = ObjectDetailsData<MetaObjectType::MONSTER>;

    DetailsData operator()(const Json::Value& value) const
    {
      using Fields = FieldNames<DetailsData>;
      DetailsData details;
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
  struct JsonReader<ObjectDetailsData<MetaObjectType::PANDORAS_BOX>>
  {
    using DetailsData = ObjectDetailsData<MetaObjectType::PANDORAS_BOX>;

    DetailsData operator()(const Json::Value& value) const
    {
      DetailsData details;
      readEventBase(value, details);
      return details;
    }
  };

  template<>
  struct JsonReader<ObjectDetailsData<MetaObjectType::PLACEHOLDER_HERO>>
  {
    using DetailsData = ObjectDetailsData<MetaObjectType::PLACEHOLDER_HERO>;

    DetailsData operator()(const Json::Value& value) const
    {
      using Fields = FieldNames<DetailsData>;
      constexpr h3m::HeroType kRandomHeroType {0xFF};

      DetailsData details;
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
  struct JsonReader<ObjectDetailsData<MetaObjectType::QUEST_GUARD>>
  {
    using DetailsData = ObjectDetailsData<MetaObjectType::QUEST_GUARD>;

    DetailsData operator()(const Json::Value& value) const
    {
      using Fields = FieldNames<DetailsData>;
      DetailsData details;
      readField(details.quest, value, Fields::kQuest);
      return details;
    }
  };

  template<>
  struct JsonReader<ObjectDetailsData<MetaObjectType::RANDOM_DWELLING>>
  {
    using DetailsData = ObjectDetailsData<MetaObjectType::RANDOM_DWELLING>;

    DetailsData operator()(const Json::Value& value) const
    {
      using Fields = FieldNames<DetailsData>;
      DetailsData details;
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
  struct JsonReader<ObjectDetailsData<MetaObjectType::RANDOM_DWELLING_PRESET_ALIGNMENT>>
  {
    using DetailsData = ObjectDetailsData<MetaObjectType::RANDOM_DWELLING_PRESET_ALIGNMENT>;

    DetailsData operator()(const Json::Value& value) const
    {
      using Fields = FieldNames<DetailsData>;
      DetailsData details;
      readField(details.owner, value, Fields::kOwner);
      readField(details.min_level, value, Fields::kMinLevel);
      readField(details.max_level, value, Fields::kMaxLevel);
      return details;
    }
  };

  template<>
  struct JsonReader<ObjectDetailsData<MetaObjectType::RANDOM_DWELLING_PRESET_LEVEL>>
  {
    using DetailsData = ObjectDetailsData<MetaObjectType::RANDOM_DWELLING_PRESET_LEVEL>;

    DetailsData operator()(const Json::Value& value) const
    {
      using Fields = FieldNames<DetailsData>;
      DetailsData details;
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
  struct JsonReader<ObjectDetailsData<MetaObjectType::RESOURCE>>
  {
    using DetailsData = ObjectDetailsData<MetaObjectType::RESOURCE>;

    DetailsData operator()(const Json::Value& value) const
    {
      using Fields = FieldNames<DetailsData>;
      DetailsData details;
      readField(details.guardians, value, Fields::kGuardians);
      readField(details.quantity, value, Fields::kQuantity);
      readField(details.unknown, value, Fields::kUnknown);
      return details;
    }
  };

  template<>
  struct JsonReader<ObjectDetailsData<MetaObjectType::SEERS_HUT>>
  {
    using DetailsData = ObjectDetailsData<MetaObjectType::SEERS_HUT>;

    DetailsData operator()(const Json::Value& value) const
    {
      using Fields = FieldNames<DetailsData>;
      DetailsData details;
      readField(details.quest, value, Fields::kQuest);
      readField(details.reward, value, Fields::kReward);
      readField(details.unknown, value, Fields::kUnknown);
      return details;
    }
  };

  template<>
  struct JsonReader<ObjectDetailsData<MetaObjectType::SCHOLAR>>
  {
    using DetailsData = ObjectDetailsData<MetaObjectType::SCHOLAR>;

    DetailsData operator()(const Json::Value& value) const
    {
      using Fields = FieldNames<DetailsData>;
      DetailsData details;
      readField(details.reward_type, value, Fields::kRewardType);
      readField(details.reward_value, value, Fields::kRewardValue);
      readField(details.unknown, value, Fields::kUnknown);
      return details;
    }
  };

  template<>
  struct JsonReader<ObjectDetailsData<MetaObjectType::SHRINE>>
  {
    using DetailsData = ObjectDetailsData<MetaObjectType::SHRINE>;

    DetailsData operator()(const Json::Value& value) const
    {
      using Fields = FieldNames<DetailsData>;
      DetailsData details;
      readField(details.spell, value, Fields::kSpell);
      readField(details.unknown, value, Fields::kUnknown);
      return details;
    }
  };

  template<>
  struct JsonReader<ObjectDetailsData<MetaObjectType::SIGN>>
  {
    using DetailsData = ObjectDetailsData<MetaObjectType::SIGN>;

    DetailsData operator()(const Json::Value& value) const
    {
      using Fields = FieldNames<DetailsData>;
      DetailsData details;
      readField(details.message, value, Fields::kMessage);
      readField(details.unknown, value, Fields::kUnknown);
      return details;
    }
  };

  template<>
  struct JsonReader<ObjectDetailsData<MetaObjectType::SPELL_SCROLL>>
  {
    using DetailsData = ObjectDetailsData<MetaObjectType::SPELL_SCROLL>;

    DetailsData operator()(const Json::Value& value) const
    {
      using Fields = FieldNames<DetailsData>;
      DetailsData details;
      readField(details.guardians, value, Fields::kGuardians);
      readField(details.spell, value, Fields::kSpell);
      readField(details.unknown, value, Fields::kUnknown);
      return details;
    }
  };

  template<>
  struct JsonReader<ObjectDetailsData<MetaObjectType::TOWN>>
  {
    using DetailsData = ObjectDetailsData<MetaObjectType::TOWN>;

    DetailsData operator()(const Json::Value& value) const
    {
      using Fields = FieldNames<DetailsData>;
      DetailsData details;
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
  struct JsonReader<ObjectDetailsData<MetaObjectType::TRIVIAL_OWNED_OBJECT>>
  {
    using DetailsData = ObjectDetailsData<MetaObjectType::TRIVIAL_OWNED_OBJECT>;

    DetailsData operator()(const Json::Value& value) const
    {
      using Fields = FieldNames<DetailsData>;
      DetailsData details;
      readField(details.owner, value, Fields::kOwner);
      return details;
    }
  };

  template<>
  struct JsonReader<ObjectDetailsData<MetaObjectType::WITCH_HUT>>
  {
    using DetailsData = ObjectDetailsData<MetaObjectType::WITCH_HUT>;

    DetailsData operator()(const Json::Value& value) const
    {
      using Fields = FieldNames<DetailsData>;
      DetailsData details;
      readField(details.potential_skills, value, Fields::kPotentialSkills);
      return details;
    }
  };

  namespace H3MJsonReader_NS
  {
    namespace
    {
      // Utility wrapper around fromJson<ObjectDetailsData<T>>(), which returns the result
      // as ObjectDetailsDataVariant.
      template<MetaObjectType T>
      ObjectDetailsDataVariant readObjectDetailsDataAsVariant(const Json::Value& value)
      {
        return fromJson<ObjectDetailsData<T>>(value);
      }
    }

    // Reads ObjectDetailsData for the specified MetaObjectType.
    // \param value - input JSON value.
    // \param meta_object_type - MetaObjectType of the object.
    // \return the deserialized data as ObjectDetailsDataVariant.
    ObjectDetailsDataVariant readObjectDetailsDataVariant(const Json::Value& value, MetaObjectType meta_object_type)
    {
      // Type of a pointer to a function that takes std::istream& and returns ObjectDetails::Data.
      using ReadObjectDetailsDataPtr = ObjectDetailsDataVariant(*)(const Json::Value&);
      // Generate (at compile time) an array of function pointers for each instantiation of
      // readObjectDetailsDataAsVariant() ordered by MetaObjectType.
      constexpr std::array<ReadObjectDetailsDataPtr, kNumMetaObjectTypes> kObjectDetailsDataReaders =
        [] <MetaObjectType... meta_object_types>
        (EnumSequence<MetaObjectType, meta_object_types...> seq)
        consteval
        {
          return std::array<ReadObjectDetailsDataPtr, sizeof...(meta_object_types)>
          { &readObjectDetailsDataAsVariant<meta_object_types>... };
        }(MakeEnumSequence<MetaObjectType, kNumMetaObjectTypes>{});
      // Invoke a function from the generated array.
      return kObjectDetailsDataReaders.at(static_cast<std::size_t>(meta_object_type))(value);
    }
  }
}
