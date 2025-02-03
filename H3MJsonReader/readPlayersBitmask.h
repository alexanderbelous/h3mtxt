#pragma once

#include <h3mtxt/H3MJsonReader/JsonReader.h>
#include <h3mtxt/Map/PlayersBitmask.h>

namespace h3m
{
  template<>
  struct JsonReader<PlayersBitmask>
  {
    PlayersBitmask operator()(const Json::Value& value) const
    {
      PlayersBitmask players_bitmask;
      players_bitmask.set(h3m::PlayerColor::Red, readField<bool>(value, "red"));
      hero.type = readField<HeroType>(value, "type");
      hero.portrait = readField<HeroPortrait>(value, "portrait");
      hero.name = readField<std::string>(value, "name");
      // TODO: read as as object with 8 boolean fields.
      //hero.can_hire.bitset = readField<std::uint8_t>(value, "can_hire");
      return hero;
    }
  };
}
