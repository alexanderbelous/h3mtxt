#pragma once

#include <h3mtxt/SavedGame/SavedGameFwd.h>

#include <iosfwd>

namespace h3svg
{
  // Writes a JSON representation of the given HoMM3 saved game into the given stream.
  // \param stream - output stream.
  // \param saved_game - input HoMM3 saved game.
  void writeH3SvgJson(std::ostream& stream, const SavedGame& saved_game);
}
