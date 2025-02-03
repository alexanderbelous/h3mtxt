#pragma once

#include <h3mtxt/H3MJsonReader/JsonReader.h>
#include <h3mtxt/JsonCommon/FieldName.h>
#include <h3mtxt/Map/Constants/Constants.h>
#include <h3mtxt/Map/PlayersBitmask.h>

namespace h3m
{
  template<>
  struct JsonReader<PlayersBitmask>
  {
    PlayersBitmask operator()(const Json::Value& value) const
    {
      PlayersBitmask players_bitmask;
      for (std::uint8_t i = 0; i < kMaxPlayers; ++i)
      {
        const PlayerColor player = static_cast<PlayerColor>(i);
        const std::string_view field_name = getFieldNameForPlayersBitmask(player);
        players_bitmask.set(player, readField<bool>(value, field_name));
      }
      return players_bitmask;
    }
  };
}
