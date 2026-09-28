#pragma once

#include <h3mtxt/SavedGame/SavedGameFwd.h>

#include <h3mtxt/SavedGame/CoordinatesPacked.h>

#include <array>
#include <cstdint>
#include <vector>

namespace h3svg
{
  // Stores the locations of all exits for an object that "teleports" a hero to another location
  // (e.g., One-Way Monoliths, Two-Way Monoliths, Whirlpools, Subterranean Gates).
  struct ObjectExits
  {
    constexpr bool operator==(const ObjectExits&) const noexcept = default;

    // The length is serialized as a 16-bit integer.
    // Padding bits in CoordinatesPacked may contain junk.
    std::vector<CoordinatesPacked> exits;
  };

  struct SubterraneanGates
  {
    constexpr bool operator==(const SubterraneanGates&) const noexcept = default;

    // All entrances/exits.
    ObjectExits gates;
    // Specifies the exit for each Subterranean Gate:
    // * If pairings[i] == -1, then gates.exits[i] is not paired up with any gate.
    // * Otherwise, the exit for gates.exits[i] is gates.exits[pairings[i]].
    // The number of elements should be equal to gates.exits.size(). However, H3SVG explicitly
    // stores this number as a 16-bit integer.
    std::vector<std::int32_t> pairings;
  };

  // Stores the information about all portals on the map (i.e. Monoliths, Whirlpools and Subterranean Gates).
  struct Portals
  {
    constexpr bool operator==(const Portals&) const noexcept = default;

    // The locations of Two-Way Monoliths for each valid object_subclass.
    std::array<ObjectExits, 8> monoliths_two_way;
    // The locations of One-Way Monolith Exits for each valid object_subclass.
    std::array<ObjectExits, 8> monoliths_one_way;
    // All actionable tiles of Whirlpools.
    ObjectExits whirlpools;
    // The locations of all Subterranean Gates and their pairings.
    SubterraneanGates subterranean_gates;
  };
}
