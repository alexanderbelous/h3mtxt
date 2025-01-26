#pragma once

#include <h3mtxt/Map/Constants/Constants.h>
#include <h3mtxt/Map/PlayersBitmask.h>
#include <h3mtxt/H3MTxtWriter/H3MTxtWriter.h>

#include <iterator>
#include <string_view>

namespace Util_NS
{
  template<>
  struct StructWriter<h3m::PlayersBitmask>
  {
    void operator()(FieldsWriter& out, const h3m::PlayersBitmask& players_bitmask) const
    {
      // Name of the field for each PlayerColor.
      static constexpr std::string_view kFieldNames[] =
      {
        "red", "blue", "tan", "green", "orange", "purple", "teal", "pink"
      };
      static_assert(std::size(kFieldNames) == h3m::kMaxPlayers,
                    "The size of kFieldNames must be the same as the number of players");
      // TODO: specialize ValueWriter<bool>.
      for (std::uint8_t i = 0; i < h3m::kMaxPlayers; ++i)
      {
        out.writeField(kFieldNames[i], players_bitmask[static_cast<h3m::PlayerColor>(i)]);
      }
    }
  };
}
