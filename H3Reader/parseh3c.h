#pragma once

#include <h3mtxt/Campaign/Campaign.h>

#include <iosfwd>

namespace h3m::H3Reader_NS
{
  // Reads a *.h3c campaign from the given stream.
  //
  // .h3c is trickier than .h3m. The file is organized like this:
  // + gzip-compressed header (h3c::Campaign without the maps).
  // + map_1 (either compressed or decompressed .h3m).
  // + map_2 (either compressed or decompressed .h3m).
  // + ...
  // + map_N (either compressed or decompressed .h3m)
  //
  // When all maps are gzip-compressed you can treat the whole .h3c file as a gzip-compressed file:
  // gzip file format allows multiple concatenated streams, in which case the result of decompression
  // is simply the concatenated decompressed streams. However, if at least one map is not gzip-compressed,
  // then you won't be able to read the .h3c file as a gzip-compressed file.
  //
  // Note that the Campaign Editor doesn't support "uncompressed" .h3c files:
  // i.e. if you unpack the .h3c file via 7-Zip or some other program (which will fail if at least
  // one map was stored uncompressed), you won't be able to open the new file with the Campaign Editor.
  // Moreover, even if you compress the unpacked file, the result will not be a valid .h3c file
  // (unless there are 0 underlying .h3m maps), because the above-mentioned "parts"
  // need to be compressed separately and then concatenated.
  // I could add support for reading unpacked .h3c files, but fuck it.
  //
  // \param stream - input stream.
  // \return the parsed campaign.
  Campaign parseh3c(std::istream& stream);
}
