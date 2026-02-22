#pragma once

#include <h3mtxt/SavedGame/SavedGameFwd.h>
#include <h3mtxt/Map/Constants/MapFormat.h>
#include <h3mtxt/Map/MapBasicInfo.h>
#include <h3mtxt/Map/Utils/ReservedData.h>

#include <cstdint>
#include <string>
#include <string_view>

namespace h3m
{
  // Represents a saved game for Heroes of Might and Magic 3 (.GM1, .GM2, ... files).
  struct SavedGame
  {
    // The first 5 bytes are always the file signature (aka magic numbers / magic bytes): "H3SVG".
    // TODO: apparently, HD Mod may sometimes use "HDSvG" instead.
    static constexpr std::string_view kFileSignature = "H3SVG";

    ReservedData<3> reserved1;
    std::uint32_t version_major;
    std::uint32_t version_minor;
    ReservedData<32> reserved2;
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
