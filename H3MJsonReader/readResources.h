#pragma once

#include <h3mtxt/H3MJsonReader/JsonReader.h>
#include <h3mtxt/JsonCommon/FieldName.h>
#include <h3mtxt/Map/Resources.h>

namespace h3m
{
  template<class T>
  struct JsonReader<Resources<T>>
  {
    Resources<T> operator()(const Json::Value& value) const
    {
      using Fields = FieldNames<Resources<T>>;
      Resources<T> resources;
      readField(resources[h3m::ResourceType::Wood], value, Fields::kWood);
      readField(resources[h3m::ResourceType::Mercury], value, Fields::kMercury);
      readField(resources[h3m::ResourceType::Ore], value, Fields::kOre);
      readField(resources[h3m::ResourceType::Sulfur], value, Fields::kSulfur);
      readField(resources[h3m::ResourceType::Crystal], value, Fields::kCrystal);
      readField(resources[h3m::ResourceType::Gems], value, Fields::kGems);
      readField(resources[h3m::ResourceType::Gold], value, Fields::kGold);
      return resources;
    }
  };
}
