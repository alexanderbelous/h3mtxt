#pragma once

#include <h3mtxt/SavedGame/SavedGameFwd.h>

#include <h3mtxt/Map/MapFwd.h>
#include <h3mtxt/SavedGame/Troops.h>

#include <array>
#include <cstdint>
#include <string>

namespace h3svg
{
  // Artifact equipped on the hero or stored in the backpack.
  struct HeroArtifact
  {
    // Type of the artifact, or 0xFFFFFFFF if there is none.
    ArtifactType32 type = static_cast<ArtifactType32>(-1);
    // Type of the spell for spell scrolls; meaningless if this isn't a spell scroll.
    // The value is usually 0xFFFFFFFF if this is not a spell scroll, but don't rely on that:
    //   * Empty slots in the backpack sometimes use 0.
    //   * War machines and SpellBook slots may use junk values like 1500, 3500, 8000, etc.
    SpellType32 spell_type = static_cast<SpellType32>(0xFFFFFFFF);
  };

  struct HeroArtifacts
  {
    // TODO: replace with EnumIndexedArray<ArtifactSlot, HeroArtifact, 19>.
    std::array<HeroArtifact, 19> equipped;
    std::array<HeroArtifact, 64> backpack;
  };

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
    // TODO: figure out what this is.
    // * bytes [31; 38] seem to be int32 move_points, int32 move_points2.
    //   Idk why they are duplicated.
    // * bytes [39; 42] are int32 experience.
    // * bytes [47; 48] are int16 spell_points
    // * bytes [49; 52] seem to be int32 experience_level.
    std::array<std::uint8_t, 113> unknown2 {};
    Troops army;
    // Fixed-size; only the characters before the first null terminator are significant.
    std::array<char, 13> name {};
    // TODO: figure out what this is.
    // * bytes [56; 59] are PrimarySkills (equipped artifacts are taken into account).
    std::array<std::uint8_t, 200> unknown3 {};
    HeroArtifacts artifacts;
    // TODO: figure out what this is.
    std::array<std::uint8_t, 22> unknown4 {};
  };
}