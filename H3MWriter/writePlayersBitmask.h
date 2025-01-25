#pragma once

#include <h3mtxt/H3MWriter/H3MWriter.h>
#include <h3mtxt/Map/PlayersBitmask.h>

namespace h3m
{
  template<>
  struct H3MWriter<PlayersBitmask>
  {
    void operator()(std::ostream& stream, const PlayersBitmask& players_bitmask) const
    {
      writeData(stream, players_bitmask.bitset);
    }
  };
}
