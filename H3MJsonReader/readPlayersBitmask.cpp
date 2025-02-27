#include <h3mtxt/H3MJsonReader/Utils.h>
#include <h3mtxt/JsonCommon/FieldName.h>
#include <h3mtxt/Map/Constants/Constants.h>
#include <h3mtxt/Map/Utils/EnumBitmask.h>

namespace h3m
{
  PlayersBitmask JsonReader<PlayersBitmask>::operator()(const Json::Value& value) const
  {
    using Fields = FieldNames<PlayersBitmask>;
    PlayersBitmask players_bitmask;
    for (std::uint8_t i = 0; i < kMaxPlayers; ++i)
    {
      const PlayerColor player = static_cast<PlayerColor>(i);
      const std::string_view field_name = Fields::get(player);
      players_bitmask.set(player, readField<bool>(value, field_name));
    }
    return players_bitmask;
  }
}
