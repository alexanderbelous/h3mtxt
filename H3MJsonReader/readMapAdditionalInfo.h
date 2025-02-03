#pragma once

#include <h3mtxt/H3MJsonReader/JsonReader.h>
#include <h3mtxt/H3MJsonReader/readVictoryCondition.h>
#include <h3mtxt/Map/MapAdditionalInfo.h>

namespace h3m
{
  template<>
  struct JsonReader<MapAdditionalInfo>
  {
    MapAdditionalInfo operator()(const Json::Value& value) const
    {
      MapAdditionalInfo info;
      info.victory_condition = readField<VictoryCondition>(value, "victory_condition");
      // TODO: add the rest
      return info;
    }
  };
}