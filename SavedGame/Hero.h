#pragma once

#include <h3mtxt/SavedGame/SavedGameFwd.h>

#include <h3mtxt/Map/MapFwd.h>
#include <h3mtxt/SavedGame/Troops.h>

#include <array>
#include <cstdint>
#include <string>

namespace h3svg
{
  struct Hero
  {
    std::int16_t x {};
    std::int16_t y {};
    std::int16_t z {};
    Bool is_visible {};
    std::uint32_t coordinates_packed {};
    // ObjectClass of the object under the hero, or ObjectClass::NONE if there is none.
    ObjectClass object_class_under {};
    // TODO: figure out what this is.
    //   unknown1[0] seems to be Bool is_actionable_under; Events and Anchor points are not considered actionable.
    std::array<std::uint8_t, 7> unknown1 {};
    // Size is 32-bit.
    std::string biography;
    std::array<std::uint8_t, 113> unknown2 {};
    Troops army;
    // Fixed-size; only the characters before the first null terminator are significant.
    std::array<char, 13> name {};
    std::array<std::uint8_t, 886> unknown3 {};
  };
}