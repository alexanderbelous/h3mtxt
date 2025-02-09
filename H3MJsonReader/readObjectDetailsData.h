#pragma once

#include <h3mtxt/H3MJsonReader/JsonReader.h>
#include <h3mtxt/H3MJsonReader/readCreatureStack.h>
#include <h3mtxt/H3MJsonReader/readSecondarySkillsBitmask.h>
#include <h3mtxt/JsonCommon/FieldName.h>
#include <h3mtxt/Map/ObjectDetailsData.h>

namespace h3m
{
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

  // TODO: remove.
  struct DefaultObjectDetailsDataReaderBase {};

  // TODO: remove once JsonReader is specialized for all ObjectDetailsData.
  template<MetaObjectType T>
  struct JsonReader<ObjectDetailsData<T>> : DefaultObjectDetailsDataReaderBase
  {
    ObjectDetailsData<T> operator()(const Json::Value&) const
    {
      throw std::runtime_error("NotImplemented.");
    }
  };

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

  // ObjectDetailsData<MetaObjectType::GENERIC_NO_PROPERTIES> has no fields.
  template<>
  struct JsonReader<ObjectDetailsData<MetaObjectType::GENERIC_NO_PROPERTIES>>
  {
    ObjectDetailsData<MetaObjectType::GENERIC_NO_PROPERTIES> operator()(const Json::Value& value) const
    {
      return {};
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
