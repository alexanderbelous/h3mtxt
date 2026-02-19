#pragma once

#include <h3mtxt/Map/Constants/MapFormat.h>
#include <h3mtxt/Map/MapBasicInfo.h>

#include <string>

namespace h3m
{
  // Represents a saved game for Heroes of Might and Magic 3 (.GM1 file).
  struct SavedGame
  {
    // The first 5 bytes are the file signature (aka magic numbers / magic bytes): "H3SVG".
    // TODO: check if these bytes can be modified: for example, maybe Heroes3.exe only checks
    // the first 3 bytes, or something. If they cannot be modified, then it doesn't make sense
    // to explicitly define this field at all.
    char file_signature[5] = { 'H', '3', 'S', 'V', 'G' };
    // Format of the map (same as Map::format).
    MapFormat format = MapFormat::ShadowOfDeath;
    // Basic information about the map (same as Map::basic_info).
    //
    // Note, however, that the strings MapBasicInfo::name and MapBasicInfo::description are serialized
    // differently from how it's done in .h3m: the length of a string is serialized as a 16-bit integer,
    // whereas in .h3m it is serialized as a 32-bit integer.
    MapBasicInfo basic_info;

    // TODO: reverse-engineer the rest.
  };
}
