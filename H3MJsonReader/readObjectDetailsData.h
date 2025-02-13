#pragma once

#include <h3mtxt/H3MJsonReader/JsonReader.h>
#include <h3mtxt/H3MJsonReader/readCreatureStack.h>
#include <h3mtxt/H3MJsonReader/readHeroArtifacts.h>
#include <h3mtxt/H3MJsonReader/readPlayersBitmask.h>
#include <h3mtxt/H3MJsonReader/readQuest.h>
#include <h3mtxt/H3MJsonReader/readResources.h>
#include <h3mtxt/H3MJsonReader/readSecondarySkillsBitmask.h>
#include <h3mtxt/H3MJsonReader/readSpellsBitmask.h>
#include <h3mtxt/H3MJsonReader/readTimedEventBase.h>
#include <h3mtxt/JsonCommon/FieldName.h>
#include <h3mtxt/Map/ObjectDetailsData.h>

namespace h3m
{
  namespace Detail_NS
  {
    void readEventBase(const Json::Value& value, EventBase& event);
  }

  template<>
  struct JsonReader<Guardians>
  {
    Guardians operator()(const Json::Value& value) const
    {
      using Fields = FieldNames<Guardians>;
      Guardians guardians;
      readField(guardians.message, value, Fields::kMessage);
      readField(guardians.creatures, value, Fields::kCreatures);
      readField(guardians.unknown, value, Fields::kUnknown);
      return guardians;
    }
  };

  template<>
  struct JsonReader<MessageAndTreasure>
  {
    MessageAndTreasure operator()(const Json::Value& value) const
    {
      using Fields = FieldNames<MessageAndTreasure>;
      MessageAndTreasure message_and_treasure;
      readField(message_and_treasure.message, value, Fields::kMessage);
      readField(message_and_treasure.resources, value, Fields::kResources);
      readField(message_and_treasure.artifact, value, Fields::kArtifact);
      return message_and_treasure;
    }
  };

  template<>
  struct JsonReader<ResourcesBitmask>
  {
    ResourcesBitmask operator()(const Json::Value& value) const
    {
      using Fields = FieldNames<ResourcesBitmask>;
      ResourcesBitmask bitmask;
      for (std::uint8_t i = 0; i < 8; ++i)
      {
        bitmask.set(static_cast<h3m::ResourceType>(i), readField<bool>(value, Fields::kNames[i]));
      }
      return bitmask;
    }
  };

  template<>
  struct JsonReader<TownBuildings>
  {
    TownBuildings operator()(const Json::Value& value) const
    {
      using Fields = FieldNames<TownBuildings>;
      TownBuildings town_buildings;
      readField(town_buildings.is_built, value, Fields::kIsBuilt);
      readField(town_buildings.is_disabled, value, Fields::kIsDisabled);
      return town_buildings;
    }
  };


  template<>
  struct JsonReader<TownEvent>
  {
    TownEvent operator()(const Json::Value& value) const
    {
      using Fields = FieldNames<TownEvent>;
      TownEvent event;
      ::h3m::H3MJsonReader_NS::readTimedEventBase(event, value);
      readField(event.buildings, value, Fields::kBuildings);
      readField(event.creatures, value, Fields::kCreatures);
      readField(event.unknown2, value, Fields::kUnknown2);
      return event;
    }
  };

  // TODO: remove.
  struct DefaultObjectDetailsDataReaderBase {};

  // TODO: remove once JsonReader is specialized for all ObjectDetailsData.
  template<MetaObjectType T>
  struct JsonReader<ObjectDetailsData<T>> : DefaultObjectDetailsDataReaderBase {};

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
      Detail_NS::readEventBase(value, details);
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
      Detail_NS::readEventBase(value, details);
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
      readField(details.creatures, value, Fields::kCreatures);
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
      readField(details.skills_availability, value, Fields::kSkillsAvailability);
      return details;
    }
  };
}
