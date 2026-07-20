#pragma once

#include <h3mtxt/SavedGame/SavedGameFwd.h>

#include <iosfwd>

namespace h3svg
{
  // Writes H3SVG data into the given stream.
  // \param stream - output stream.
  // \param saved_game - saved game to write.
  // \param compress - if true, the function will write (gzip) compressed H3SVG data,
  //        otherwise uncompressed H3SVG data.
  void writeh3svg(std::ostream& stream, const SavedGame& saved_game, bool compress = true);
}
