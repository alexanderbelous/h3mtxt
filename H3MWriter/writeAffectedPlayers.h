#pragma once

#include <h3mtxt/H3MWriter/H3MWriter.h>
#include <h3mtxt/Map/AffectedPlayers.h>

namespace h3m
{
  template<>
  struct H3MWriter<AffectedPlayers>
  {
    void operator()(std::ostream& stream, const AffectedPlayers& affected_players) const
    {
      writeData(stream, affected_players.bitset);
    }
  };
}
