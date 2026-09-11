#pragma once

#include <h3mtxt/Campaign/Campaign.h>
#include <h3mtxt/Map/Map.h>
#include <h3mtxt/SavedGame/SavedGame.h>

#include <iosfwd>
#include <variant>

namespace h3m
{
  // Reads a *.h3m map or a .h3c campaign from the given stream.
  // \param stream - input stream. The stream is expected to store
  //        either .h3c data or (possibly gzip-compressed) .h3m data.
  // \return the parsed map/campaign.
  [[deprecated("Use h3mtxt::parseh3(), h3m::parseh3m(), h3m::parseh3c() or h3svg::parseh3svg() instead")]]
  std::variant<Map, Campaign> parseh3(std::istream& stream);
}

namespace h3mtxt
{
  // Reads an H3M map, an H3C campaign or an H3SVG saved game from the given stream.
  // \param stream - input stream. The stream is expected to store an
  //        (possibly gzip-compressed) H3M map, an H3C campaign or an H3SVG
  //        saved game data.
  // \return the parsed map/campaign/saved game.
  std::variant<h3m::Map, h3m::Campaign, h3svg::SavedGame> parseh3(std::istream& stream);
}
