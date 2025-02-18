#pragma once

#include <h3mtxt/Map/Base.h>
#include <h3mtxt/Map/Constants/ObjectClass.h>
#include <h3mtxt/Map/Constants/ObjectGroup.h>
#include <h3mtxt/Map/Utils/ReservedData.h>

#include <array>
#include <cstdint>
#include <string>

namespace h3m
{
  struct ObjectAttributes
  {
    // Name of the *.def sprite to use.
    // If this is an empty string:
    // * The Editor will crash with the error "ResourceManager::GetSprite could not find the "sprite" resource ""."
    // * The game will also report an error, but the game will not crash; the object will be rendered invisible,
    //   occupying a single tile (the coordinates of the object).
    std::string def;
    std::array<std::uint8_t, 6> passability{};
    std::array<std::uint8_t, 6> actionability{};
    // TODO: replace with EnumBitmask.
    std::uint16_t allowed_landscapes {};
    // Bitfield.
    std::uint16_t landscape_group {};
    ObjectClass object_class {};
    // aka subclass.
    std::uint32_t object_number {};
    // "Group" for such objects (see ObjectGroup enum).
    // AFAIU, this doesn't matter for the game; apparently, it was meant to be used in the Map Editor
    // to choose which tab to show this object in, but the editor only does it for standard objects.
    // TODO: check if this has any impact on Kingdom Overview, View Air, View Earth.
    ObjectGroup object_group {};
    Bool is_ground {};
    // Should be 0s. Kept here for compatibility.
    ReservedData<16> unknown;
  };
}
