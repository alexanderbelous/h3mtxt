#pragma once

#include <h3mtxt/H3MJsonReader/JsonReader.h>
#include <h3mtxt/H3MJsonReader/readSecondarySkillsBitmask.h>
#include <h3mtxt/JsonCommon/FieldName.h>
#include <h3mtxt/Map/ObjectDetailsData.h>

namespace h3m
{
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
