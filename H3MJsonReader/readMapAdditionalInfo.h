#pragma once

#include <h3mtxt/H3MJsonReader/JsonReader.h>
#include <h3mtxt/H3MJsonReader/readLossCondition.h>
#include <h3mtxt/H3MJsonReader/readVictoryCondition.h>
#include <h3mtxt/Map/MapAdditionalInfo.h>

namespace h3m
{

  template<>
  struct JsonReader<Rumor>
  {
    Rumor operator()(const Json::Value& value) const
    {
      Rumor rumor;
      rumor.name = readField<std::string>(value, "name");
      rumor.description = readField<std::string>(value, "description");
      return rumor;
    }
  };

  template<>
  struct JsonReader<MapAdditionalInfo>
  {
    MapAdditionalInfo operator()(const Json::Value& value) const
    {
      MapAdditionalInfo info;
      info.victory_condition = readField<VictoryCondition>(value, "victory_condition");
      info.loss_condition = readField<LossCondition>(value, "loss_condition");
      info.rumors = readField<std::vector<Rumor>>(value, "rumors");
      // TODO: add the rest
      return info;
    }
  };
}
