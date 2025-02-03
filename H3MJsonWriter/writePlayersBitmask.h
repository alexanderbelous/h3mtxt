#pragma once

#include <h3mtxt/JsonCommon/FieldName.h>
#include <h3mtxt/Map/Constants/Constants.h>
#include <h3mtxt/Map/PlayersBitmask.h>
#include <h3mtxt/H3MJsonWriter/H3MJsonWriter.h>

namespace Util_NS
{
  template<>
  struct JsonObjectWriter<h3m::PlayersBitmask>
  {
    void operator()(FieldsWriter& out, const h3m::PlayersBitmask& players_bitmask) const
    {
      for (std::uint8_t i = 0; i < h3m::kMaxPlayers; ++i)
      {
        const h3m::PlayerColor player = static_cast<h3m::PlayerColor>(i);
        const std::string_view field_name = h3m::getFieldNameForPlayersBitmask(player);
        out.writeField(field_name, players_bitmask[player]);
      }
    }
  };
}
