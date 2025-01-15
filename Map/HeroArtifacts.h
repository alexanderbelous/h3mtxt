#pragma once

#include <cstdint>
#include <vector>

namespace h3m
{
  // 0xFFFF implies "default" for any slot, whatever that means (empty?).
  struct HeroArtifacts
  {
    std::uint16_t headwear {};
    std::uint16_t shoulders {};
    std::uint16_t neck {};
    std::uint16_t right_hand {};
    std::uint16_t left_hand {};
    std::uint16_t torso {};
    std::uint16_t right_ring {};
    std::uint16_t left_ring {};
    std::uint16_t feet {};
    std::uint16_t misc1 {};
    std::uint16_t misc2 {};
    std::uint16_t misc3 {};
    std::uint16_t misc4 {};
    std::uint16_t device1 {};
    std::uint16_t device2 {};
    std::uint16_t device3 {};
    // Catapult's slot, not accessible via the Editor, always empty.
    std::uint16_t device4 {};
    std::uint16_t spellbook {};
    std::uint16_t misc5 {};
    std::vector<std::uint16_t> backpack;
  };
}
