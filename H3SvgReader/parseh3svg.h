#pragma once

#include <h3mtxt/SavedGame/SavedGame.h>

#include <iosfwd>

namespace h3m::H3SvgReader_NS
{
  // Reads a saved game for HoMM3 from the given stream.
  // \param stream - input stream. The stream is expected to store an either gzip-compressed
  //        or uncompressed saved game data for HoMM3 (i.e. .GM1, .GM2, ... file).
  // \return the parsed saved game.
  SavedGame parseh3svg(std::istream& stream);
}
