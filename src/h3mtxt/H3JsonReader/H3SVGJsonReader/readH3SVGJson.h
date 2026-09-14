#pragma once

#include <h3mtxt/SavedGame/SavedGame.h>

#include <iosfwd>

namespace h3json
{
  // Reads a h3svg::SavedGame from the given JSON file.
  // \param stream - input stream containing the JSON data.
  // \return the parsed saved game.
  h3svg::SavedGame readH3SVGJson(std::istream& stream);
}
